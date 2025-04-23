#include "DataLoader.h"
#include <fstream>
#include <cassert>

void DataLoader::StageLoad()
{
	// �ꎞ�ۑ��pstring
	std::string strBuf;
	// �J���}�����ꎞ�ۑ��pstring
	std::vector<std::string> strConmaBuf;

	// �t�@�C���ǂݍ���
	std::ifstream ifs("data/csv/stageData.csv");
	if (!ifs)
	{
		assert(false);
		return;
	}

	//�ŏ��͑Ή��\��񂪓����Ă��邾���Ȃ̂Ŗ�������
	std::getline(ifs, strBuf);
	//����ǂݐ؂�܂Ń��[�v
	while (std::getline(ifs, strBuf))
	{
		//�擾������������J���}��؂�̔z��(���Q)�ɂ���
		strConmaBuf = Split(strBuf, ',');
		//�z�񂩂�X�e�[�W�����擾����
		auto& name = strConmaBuf[eStageDataOrder::stageName];
		//�}�b�v�f�[�^��ǂݍ���
		LoadMiniMapData(strConmaBuf, name);

		//�v���C���[�̊J�n���W���擾����
		m_stageData[name].startPos.x = stof(strConmaBuf[eStageDataOrder::startPosX]);
		m_stageData[name].startPos.y = 0.0f;
		m_stageData[name].startPos.z = stof(strConmaBuf[eStageDataOrder::startPosZ]);

		//�N���A���W���擾����
		m_stageData[name].clearPos.x = stof(strConmaBuf[eStageDataOrder::clearPosX]);
		m_stageData[name].clearPos.y = 0.0f;
		m_stageData[name].clearPos.z = stof(strConmaBuf[eStageDataOrder::clearPosZ]);

		//�`�F�X�g�̌������擾����
		m_stageData[name].chestDir = stof(strConmaBuf[eStageDataOrder::chestDir]);
	}

	//�X�e�[�W�̖��O��ʂŕۊǂ��Ă���
	for (auto& name : m_stageData)
	{
		m_stageName.push_back(name.first);
	}
}

std::vector<std::string> DataLoader::Split(std::string& str, char del)
{
	// ��؂�J�n�ʒu
	int first = 0;
	// ��؂�ŏI�ʒu
	int last = static_cast<int>(str.find_first_of(del));

	//���ʂ����Ă����z��
	std::vector<std::string> result;

	while (first < str.size())
	{
		// ��؂������̂����ʂɓ���Ă���
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		// �ʒu�X�V
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
	// �ꎞ�ۑ��pstring
	std::string strBuf;
	// �J���}�����ꎞ�ۑ��pstring
	std::vector<std::string> strConmaBuf;

	// �t�@�C���ǂݍ���
	std::ifstream ifs(inputData[eStageDataOrder::mapDataPath]);
	if (!ifs)
	{
		assert(false);
		return;
	}

	//����ǂݐ؂�܂Ń��[�v
	while (std::getline(ifs, strBuf))
	{
		//�擾������������J���}��؂�̔z��(���Q)�ɂ���
		strConmaBuf = Split(strBuf, ',');

		for (int x = 0; x < strConmaBuf.size(); x++)
		{
			//�z��̕���(string)�𐔎�(int)�ɂ���
			int temp = std::stoi(strConmaBuf[x]);
			//�}�b�v�f�[�^�ɒǉ����Ă���
			m_stageData[stageName].mapData.push_back(temp);
		}
	}
}
