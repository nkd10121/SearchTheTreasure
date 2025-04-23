#pragma once
#include <map>
#include <string>
#include <list>
#include "DxLib.h"

/// <summary>
/// 3D���f�����Ǘ�����N���X
/// </summary>
class ModelManager
{
public:
	void LoadModel(std::string name,std::string path);

	const int GetHandle(std::string name)const;
	const void SetTexture(std::string name, std::list<std::string> texPath);

private:
	struct ModelData
	{
		std::string name = "";
		std::string path = "";
		int handle = -1;
		bool isAddTexture = false;
	
	};

	//���O�A�p�X�A�n���h���A�e�N�X�`�������Ă��邩�ǂ������������z��
	std::list<ModelData> m_modelDatas;
};

