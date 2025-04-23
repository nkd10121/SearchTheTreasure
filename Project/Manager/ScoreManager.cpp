#include "ScoreManager.h"
#include <iostream>
#include <cassert>
#include <DxLib.h>

namespace
{
	struct Header
	{
		char id[4] = "inf";		//最後に\nが入っているためこれで4文字だと思っていい(4バイト)
		float version = 1.0f;	//4バイト
		size_t dataCount = 0;	//4バイト
		//空白の4バイトが入っている(パディング)
	};

	const std::string kPath = "data/score/score.data";
	constexpr int kScoreNum = 3;
}

ScoreManager::ScoreManager()
{
	for (int i = 0;i < kScoreNum;i++)
	{
		m_score.push_back(0);
	}
}

ScoreManager::~ScoreManager()
{
	m_score.clear();
}

void ScoreManager::Input(int score)
{
	m_score.push_front(score);	//追加して
	m_score.sort();				//低いのが前に来るようにソートして
	m_score.reverse();			//並び順を逆にして
	m_score.pop_back();			//一番低い要素を削除

	return;
}

void ScoreManager::Load()
{
	auto handle = FileRead_open(kPath.c_str());
	if (handle == 0)
	{
		return;
	}
	//ヘッダの読み込み
	Header header;
	FileRead_read(&header, sizeof(header), handle);

	//データの読み込み
	for (int i = 0; i < header.dataCount; i++)
	{
		int score;
		FileRead_read(&score, sizeof(score), handle);

		m_score.push_back(score);
		m_score.pop_front();
	}

	FileRead_close(handle);
}

void ScoreManager::Save()
{
	FILE* fp = nullptr;//ファイルポインタ
	auto err = fopen_s(&fp, kPath.c_str(), "wb");
	//ヘッダの書き込み
	Header header;
	header.dataCount = m_score.size();
	fwrite(&header, sizeof(header), 1, fp);

	//データ本体を書き込んでいく
	for (const auto& info : m_score)
	{
		fwrite(&info, sizeof(info), 1, fp);
	}

	fclose(fp);
}
