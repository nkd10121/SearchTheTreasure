#include "DataLoader.h"
#include <fstream>
#include <cassert>

void DataLoader::StageLoad()
{
	// 一時保存用string
	std::string strBuf;
	// カンマ分け一時保存用string
	std::vector<std::string> strConmaBuf;

	// ファイル読み込み
	std::ifstream ifs("data/csv/stageData.csv");
	if (!ifs)
	{
		assert(false);
		return;
	}

	//最初は対応表情報が入っているだけなので無視する
	std::getline(ifs, strBuf);
	//情報を読み切るまでループ
	while (std::getline(ifs, strBuf))
	{
		//取得した文字列をカンマ区切りの配列(情報群)にする
		strConmaBuf = Split(strBuf, ',');
		//配列からステージ名を取得する
		auto& name = strConmaBuf[eStageDataOrder::stageName];
		//マップデータを読み込む
		LoadMiniMapData(strConmaBuf, name);

		//プレイヤーの開始座標を取得する
		m_stageData[name].startPos.x = stof(strConmaBuf[eStageDataOrder::startPosX]);
		m_stageData[name].startPos.y = 0.0f;
		m_stageData[name].startPos.z = stof(strConmaBuf[eStageDataOrder::startPosZ]);

		//クリア座標を取得する
		m_stageData[name].clearPos.x = stof(strConmaBuf[eStageDataOrder::clearPosX]);
		m_stageData[name].clearPos.y = 0.0f;
		m_stageData[name].clearPos.z = stof(strConmaBuf[eStageDataOrder::clearPosZ]);

		//チェストの向きを取得する
		m_stageData[name].chestDir = stof(strConmaBuf[eStageDataOrder::chestDir]);
	}

	//ステージの名前を別で保管しておく
	for (auto& name : m_stageData)
	{
		m_stageName.push_back(name.first);
	}
}

std::vector<std::string> DataLoader::Split(std::string& str, char del)
{
	// 区切り開始位置
	int first = 0;
	// 区切り最終位置
	int last = static_cast<int>(str.find_first_of(del));

	//結果を入れておく配列
	std::vector<std::string> result;

	while (first < str.size())
	{
		// 区切ったものを結果に入れていく
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		// 位置更新
		first = last + 1;
		last = static_cast<int>(str.find_first_of(del, first));
		if (last == std::string::npos)
		{
			last = static_cast<int>(str.size());
		}
	}

	return result;
}

void DataLoader::LoadMiniMapData(std::vector<std::string>& inputData, std::string stageName)
{
	// 一時保存用string
	std::string strBuf;
	// カンマ分け一時保存用string
	std::vector<std::string> strConmaBuf;

	// ファイル読み込み
	std::ifstream ifs(inputData[eStageDataOrder::mapDataPath]);
	if (!ifs)
	{
		assert(false);
		return;
	}

	//情報を読み切るまでループ
	while (std::getline(ifs, strBuf))
	{
		//取得した文字列をカンマ区切りの配列(情報群)にする
		strConmaBuf = Split(strBuf, ',');

		for (int x = 0; x < strConmaBuf.size(); x++)
		{
			//配列の文字(string)を数字(int)にして
			int temp = std::stoi(strConmaBuf[x]);
			//マップデータに追加していく
			m_stageData[stageName].mapData.push_back(temp);
		}
	}
}
