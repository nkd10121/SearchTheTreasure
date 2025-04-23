#include "ModelManager.h"
#include "DxLib.h"
#include <cassert>

void ModelManager::LoadModel(std::string name, std::string path)
{
	//もし以前に登録したパスと同じパスがあったら早期リターン
	for (const auto& data : m_modelDatas)
	{
		if (data.path == path)
		{
			return;
		}
	}

	//ここまで来たなら新しく登録する
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
	//指定された名前と同じ名前が登録されていればそのハンドルを返す
	for (auto& data : m_modelDatas)
	{
		if (data.name == name)
		{
			return data.handle;
		}
	}

	//登録されていなかったら-1を返す
	return -1;
}

const void ModelManager::SetTexture(std::string name, std::list<std::string> texPath)
{
	//もし指定された名前のモデルにテクスチャがすでに張られていたら早期リターン
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

	//名前からハンドルを取得する
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
