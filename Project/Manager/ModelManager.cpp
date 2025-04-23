#include "ModelManager.h"
#include "DxLib.h"
#include <cassert>

void ModelManager::LoadModel(std::string name, std::string path)
{
	//�����ȑO�ɓo�^�����p�X�Ɠ����p�X���������瑁�����^�[��
	for (const auto& data : m_modelDatas)
	{
		if (data.path == path)
		{
			return;
		}
	}

	//�����܂ŗ����Ȃ�V�����o�^����
	int handle = MV1LoadModel(path.c_str());
	assert(handle != -1);

	ModelData inputData;
	inputData.name = name;
	inputData.handle = handle;
	inputData.path = path;
	inputData.isAddTexture = false;
	
	m_modelDatas.push_back(inputData);
}

const int ModelManager::GetHandle(const std::string name) const
{
	//�w�肳�ꂽ���O�Ɠ������O���o�^����Ă���΂��̃n���h����Ԃ�
	for (auto& data : m_modelDatas)
	{
		if (data.name == name)
		{
			return data.handle;
		}
	}

	//�o�^����Ă��Ȃ�������-1��Ԃ�
	return -1;
}

const void ModelManager::SetTexture(std::string name, std::list<std::string> texPath)
{
	//�����w�肳�ꂽ���O�̃��f���Ƀe�N�X�`�������łɒ����Ă����瑁�����^�[��
	for (auto& data : m_modelDatas)
	{
		if (data.name == name)
		{
			if (data.isAddTexture)
			{
				return;
			}

			data.isAddTexture = true;
		}
	}

	//���O����n���h�����擾����
	int handle = GetHandle(name);

	int index = 0;
	for (auto& texP : texPath)
	{
		int texH = LoadGraph(texP.c_str());
		MV1SetTextureGraphHandle(handle, index, texH, FALSE);
		index++;
	}


	return;
}
