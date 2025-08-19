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
