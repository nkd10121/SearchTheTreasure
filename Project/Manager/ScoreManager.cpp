#include "ScoreManager.h"
#include <iostream>
#include <cassert>
#include <DxLib.h>

namespace
{
	struct Header
	{
		char id[4] = "inf";		//�Ō��\n�������Ă��邽�߂����4�������Ǝv���Ă���(4�o�C�g)
		float version = 1.0f;	//4�o�C�g
		size_t dataCount = 0;	//4�o�C�g
		//�󔒂�4�o�C�g�������Ă���(�p�f�B���O)
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
	m_score.push_front(score);	//�ǉ�����
	m_score.sort();				//�Ⴂ�̂��O�ɗ���悤�Ƀ\�[�g����
	m_score.reverse();			//���я����t�ɂ���
	m_score.pop_back();			//��ԒႢ�v�f���폜

	return;
}

void ScoreManager::Load()
{
	auto handle = FileRead_open(kPath.c_str());
	if (handle == 0)
	{
		return;
	}
	//�w�b�_�̓ǂݍ���
	Header header;
	FileRead_read(&header, sizeof(header), handle);

	//�f�[�^�̓ǂݍ���
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
	FILE* fp = nullptr;//�t�@�C���|�C���^
	auto err = fopen_s(&fp, kPath.c_str(), "wb");
	//�w�b�_�̏�������
	Header header;
	header.dataCount = m_score.size();
	fwrite(&header, sizeof(header), 1, fp);

	//�f�[�^�{�̂���������ł���
	for (const auto& info : m_score)
	{
		fwrite(&info, sizeof(info), 1, fp);
	}

	fclose(fp);
}
