bool DeleteStageData(const String& stageName) {
	std::vector<String> stageNames;
	{
		Deserializer<BinaryReader> reader{ U"Stage/StageNames.bin" };
		if (reader) {
			reader(stageNames);
		}
		else {
			// 読み込み失敗
			return false;
		}
	}

	// フォルダの削除
	if (FileSystem::IsDirectory(U"Stage/" + stageName)) {
		FileSystem::Remove(U"Stage/" + stageName);
	}
	else {
		throw Error{ U"Stage/" + stageName + U" is not a directory or does not exist." };
	}

	// 削除前のサイズ
	const size_t beforeSize = stageNames.size();

	// 指定名を削除
	stageNames.erase(
		std::remove(stageNames.begin(), stageNames.end(), stageName),
		stageNames.end()
	);

	// 削除できたか判定
	if (stageNames.size() == beforeSize) {
		// 削除対象がなかった
		return false;
	}

	{
		if (Serializer<BinaryWriter> writer{ U"Stage/StageNames.bin" }) {
			writer(stageNames);
			return true;
		}
		else {
			throw Error{ U"Failed to save StageNames.bin" };
		}
	}
	return false;
}


// 壊れたUTF-8も「?」にして進めるデコーダ（最小実装）
static std::u32string DecodeUtf8Lossy(std::string_view s) {
	std::u32string out;
	out.reserve(s.size());

	const unsigned char* p = (const unsigned char*)s.data();
	const unsigned char* end = p + s.size();

	while (p < end) {
		unsigned char c = *p;

		// ASCII
		if (c < 0x80) {
			out.push_back((char32_t)c);
			++p;
			continue;
		}

		// 2-byte
		if ((c & 0xE0) == 0xC0) {
			if (p + 1 >= end) { out.push_back(U'?'); break; }
			unsigned char c1 = p[1];
			if ((c1 & 0xC0) != 0x80) { out.push_back(U'?'); ++p; continue; }
			char32_t cp = ((c & 0x1F) << 6) | (c1 & 0x3F);
			out.push_back(cp);
			p += 2;
			continue;
		}

		// 3-byte
		if ((c & 0xF0) == 0xE0) {
			if (p + 2 >= end) { out.push_back(U'?'); break; }
			unsigned char c1 = p[1], c2 = p[2];
			if ((c1 & 0xC0) != 0x80 || (c2 & 0xC0) != 0x80) { out.push_back(U'?'); ++p; continue; }
			char32_t cp = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
			out.push_back(cp);
			p += 3;
			continue;
		}

		// 4-byte
		if ((c & 0xF8) == 0xF0) {
			if (p + 3 >= end) { out.push_back(U'?'); break; }
			unsigned char c1 = p[1], c2 = p[2], c3 = p[3];
			if ((c1 & 0xC0) != 0x80 || (c2 & 0xC0) != 0x80 || (c3 & 0xC0) != 0x80) { out.push_back(U'?'); ++p; continue; }
			char32_t cp = ((c & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
			out.push_back(cp);
			p += 4;
			continue;
		}

		// それ以外（不正）
		out.push_back(U'?');
		++p;
	}

	return out;
}

static std::u32string NormalizeToAsciiU32(const std::u32string& in) {
	std::u32string out;
	out.reserve(in.size());

	auto push = [&](char32_t cp) { out.push_back(cp); };

	for (char32_t cp : in) {
		// そのまま通すASCII
		if (cp >= 0x20 && cp <= 0x7E) { // printable ASCII
			push(cp);
			continue;
		}
		if (cp == U'\n' || cp == U'\r' || cp == U'\t') { // 制御は必要最低限許可
			push(cp);
			continue;
		}

		// ---- よくある「Windowsで事故る」系をASCIIへ ----
		switch (cp) {
			// クォート
		case U'\u2018': // ‘
		case U'\u2019': // ’
		case U'\u2032': // ′
		case U'\uFF07': // ＇
			push(U'\''); break;

		case U'\u201C': // “
		case U'\u201D': // ”
		case U'\u2033': // ″
		case U'\uFF02': // ＂
			push(U'"'); break;

			// ダッシュ/マイナス
		case U'\u2010': // ‐
		case U'\u2011': // -
		case U'\u2012': // ‒
		case U'\u2013': // –
		case U'\u2014': // —
		case U'\u2212': // −
		case U'\uFF0D': // －
			push(U'-'); break;

			// 三点リーダ
		case U'\u2026': // …
			push(U'.'); push(U'.'); push(U'.'); break;

			// ノーブレークスペース / 全角スペースなどは普通のスペースへ
		case U'\u00A0': // NBSP
		case U'\u2000': case U'\u2001': case U'\u2002': case U'\u2003':
		case U'\u2004': case U'\u2005': case U'\u2006': case U'\u2007':
		case U'\u2008': case U'\u2009': case U'\u200A':
		case U'\u202F': // narrow NBSP
		case U'\u205F':
		case U'\u3000': // 全角スペース
			push(U' '); break;

			// それ以外は「落とす」か「?」にする（お好み）
		default:
			// push(U'?'); // 置換したいならこっち
			// 何も出力しない＝除去
			break;
		}
	}

	return out;
}

static std::string EncodeAsciiFromU32(const std::u32string& u32) {
	std::string out;
	out.reserve(u32.size());
	for (char32_t cp : u32) {
		// ここではASCIIだけ入る想定
		if (cp <= 0x7F) out.push_back((char)cp);
		else out.push_back('?');
	}
	return out;
}

std::string NormalizePromptToSafeAscii(std::string_view s) {
	auto u32 = DecodeUtf8Lossy(s);
	auto norm = NormalizeToAsciiU32(u32);
	return EncodeAsciiFromU32(norm);
}




