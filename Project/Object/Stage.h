#pragma once
#include <vector>
#include <memory>
#include <DxLib.h>

class Stage
{
public:
	Stage();
	virtual ~Stage();

	void Init();

	void Draw();

	void SetMapData(float startX, float startY, std::vector<int> data);

private:
	void CreateStage();

	void CreateStageData(int handleNum,int idxX,int idxY,int angle, int offsetX = 0, int offsetY = 0);
private:
	//テクスチャの数
	static const int kTexNum = 3;
	//マップ配列の行数
	static const int kMapRowNum = 12;
	//マップ配列の列数
	static const int kMapColNum = 15;

	struct StageData
	{
		VECTOR pos;
		int handle;
	};

	std::vector<int> m_stagePartsHandle;
	int m_textureHandle[kTexNum];

	std::vector<StageData> m_stage;

	std::vector<int> m_mapData;
	int m_mapArray[kMapRowNum][kMapColNum];

	int m_startX;
	int m_startY;
};

