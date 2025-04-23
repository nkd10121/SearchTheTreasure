#pragma once
#include "DxLib.h"
#include <string>
#include <vector>
#include <map>
#include <array>

class DataLoader
{
public:
	/// <summary>
	/// �X�e�[�W�f�[�^
	/// </summary>
	struct stageData
	{
		std::vector<int> mapData;					//�}�b�v�̔z��
		VECTOR startPos = VGet(0.0f,0.0f,0.0f);		//�X�^�[�g���W
		VECTOR clearPos = VGet(0.0f, 0.0f, 0.0f);	//�N���A���W
		float chestDir = 0.0f;						//�`�F�X�g�̌���
	};

	/// <summary>
	/// �ǂݍ���csv�̕��я�
	/// NOTE:�ǂݍ��ޏ��𑝂₷���тɂ����ɒǉ�����K�v����
	/// </summary>
	enum eStageDataOrder : int
	{
		stageName,		//�X�e�[�W��
		mapDataPath,	//�}�b�v�f�[�^��������csv�̃p�X
		startPosX,		//�X�^�[�gX���W
		startPosZ,		//�X�^�[�gZ���W
		clearPosX,		//�N���AX���W
		clearPosZ,		//�N���AZ���W
		chestDir		//�`�F�X�g�̌���
	};

	/// <summary>
	/// �X�e�[�W�f�[�^�̃��[�h
	/// </summary>
	void StageLoad();

	/// <summary>
	/// �}�b�v�f�[�^��Ԃ�
	/// </summary>
	/// <returns>�}�b�v�f�[�^</returns>
	const std::map <std::string, stageData> GetStageData()const { return m_stageData; };

	/// <summary>
	/// �X�e�[�W���ꗗ��Ԃ�
	/// </summary>
	/// <returns>�X�e�[�W���ꗗ</returns>
	const std::vector<std::string> GetStageName()const { return m_stageName; };

private:

	/// <summary>
	/// �ЂƂɂ܂Ƃ߂�ꂽ�ǂݍ��񂾏����J���}��؂�ɂ킯��
	/// </summary>
	/// <param name="str">�ЂƂɂ܂Ƃ߂�ꂽ�ǂݍ��񂾏��</param>
	/// <param name="del">��؂�n�_�ƂȂ镶��</param>
	/// <returns></returns>
	std::vector<std::string> Split(std::string& str, char del);	

	/// <summary>
	/// �}�b�v�f�[�^��ǂݍ���
	/// </summary>
	/// <param name="inputData">�ǂݍ��܂ꂽ���Q</param>
	/// <param name="stageName">��������X�e�[�W��</param>
	void LoadMiniMapData(std::vector<std::string>& inputData, std::string stageName);

private:
	std::map <std::string, stageData> m_stageData;	//�}�b�v�f�[�^
	std::vector<std::string> m_stageName;			//�X�e�[�W���ꗗ
};

