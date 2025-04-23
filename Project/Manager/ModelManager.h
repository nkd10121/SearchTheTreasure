#pragma once
#include <map>
#include <string>
#include <list>
#include "DxLib.h"

/// <summary>
/// 3Dモデルを管理するクラス
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

	//名前、パス、ハンドル、テクスチャをつけているかどうかを持った配列
	std::list<ModelData> m_modelDatas;
};

