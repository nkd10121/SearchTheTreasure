#pragma once
#include "DxLib.h"
#include "DataLoader.h"

class MiniMap
{
public:
	MiniMap();
	~MiniMap();

	void Update(VECTOR playerPos,float angle);
	void Draw();

	void SetMiniMap(DataLoader::stageData inputData);

	const bool GetIsMove() { return m_isMove; }

private:
	void Move(VECTOR playerPos);

	void SerDir();

	void DrawTreasure();

	void DrawGrid();
private:
	enum Dir
	{
		Top,
		Right,
		Bottom,
		Left
	};

	int m_arrowHandle;

	VECTOR m_startPos;
	VECTOR m_arrowPos;
	VECTOR m_arrowPosLog;
	float m_arrowAngle;
	int m_direction;

	int m_nowCol;
	int m_nextCol;

	int m_colX;
	int m_colY;
	bool m_isDelColPos;

	bool m_isMove;

	int m_colArray[10][13];
	VECTOR m_treasurePos;
};

