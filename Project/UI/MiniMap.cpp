#include "MiniMap.h"
#include <cmath>

namespace
{
	constexpr int kMapPosXLeft = 1280 - 32 * 13;
	constexpr int kMapPosXRight = 1280;

	constexpr int kMapPosYTop = 0;
	constexpr int kMapPosYBottom= 320;

	constexpr int kCol = 13;
	constexpr int kRow = 10;
	
}

MiniMap::MiniMap():
	m_startPos		(VGet(0,0,0)),
	m_arrowPos		(VGet(0,0,0)),
	m_arrowPosLog	(VGet(0,0,0)),
	m_arrowAngle	(0.0f),
	m_direction		(0),
	m_nowCol		(0),
	m_nextCol		(0),
	m_isDelColPos	(true),
	m_isMove		(true),
	m_treasurePos	(VGet(0, 0, 0))
{
	m_arrowHandle = LoadGraph("data/graph/arrow.png");
}

MiniMap::~MiniMap()
{
}


void MiniMap::Update(VECTOR playerPos, float angle)
{
	m_arrowPosLog = m_arrowPos;

	m_arrowAngle = round((-angle - 3.14f / 2) * 100) / 100;

	Move(playerPos);
}

void MiniMap::Draw()
{
	//îwåiÇÃï`âÊ
	DrawGrid();
	//Ç®ïÛÇÃï`âÊ
	DrawTreasure();
	//ñÓàÛ(ÉvÉåÉCÉÑÅ[ÇÃà íu)ÇÃï`âÊ
	DrawRotaGraph(static_cast<int>(m_arrowPos.x), static_cast<int>(m_arrowPos.y), 0.5f, m_arrowAngle, m_arrowHandle, true);

#ifdef _DEBUG

	DrawFormatString(640, 0,0xff0000,"%f", m_arrowPos.x);
	DrawFormatString(640, 16,0xff0000,"%f", m_arrowPos.y);

	if (m_isMove)
	{
		DrawFormatString(640, 32,0xff0000,"ìÆÇØÇÈ");
	}
	else
	{
		DrawFormatString(640, 32, 0xff0000, "ìÆÇØÇ»Ç¢");
	}

	DrawFormatString(640, 48, 0xff0000, "colPosX:%d", m_colX);
	DrawFormatString(640, 64, 0xff0000, "colPosY:%d", m_colY);


	DrawFormatString(300, 0, 0xffffff, "%f", m_arrowAngle);

	m_direction = (static_cast<int>(m_arrowAngle * 100) / 157) % 4;
	DrawFormatString(300, 32, 0xff0000, "%d", m_direction);

	if (m_direction == 0)
	{
		DrawFormatString(300, 16, 0xff0000, "Å™");
	}
	else if (m_direction == 1 || m_direction == -3)
	{
		DrawFormatString(300, 16, 0xff0000, "Å®");
	}
	else if (m_direction == 2 || m_direction == -2)
	{
		DrawFormatString(300, 16, 0xff0000, "Å´");
	}
	else if (m_direction == 3 || m_direction == -1)
	{
		DrawFormatString(300, 16, 0xff0000, "Å©");
	}


#endif
}

void MiniMap::SetMiniMap(DataLoader::stageData inputData)
{
	//É~ÉjÉ}ÉbÉvè„ÇÃç¿ïWÇì¸ÇÍÇÈ
	m_colX = static_cast<int>(inputData.startPos.x);
	m_colY = static_cast<int>(inputData.startPos.z);

	//ñÓàÛÇÃç¿ïWÇì¸ÇÍÇÈ
	m_startPos.x = static_cast<float>(kMapPosXLeft + m_colX * 32 + 16);
	m_startPos.y = static_cast<float>(kMapPosYBottom - (9 - m_colY) * 32 - 14);

	m_arrowPos.x = m_startPos.x;
	m_arrowPos.y = m_startPos.y;

	m_treasurePos = inputData.clearPos;

	for (int i = 0; i < inputData.mapData.size(); i++)
	{
		int x = i % 15;
		int y = i /	15;

		if (y == 0 || y == 11)
		{
			continue;
		}

		if (x == 0 || x == 14)
		{
			continue;
		}

		x -= 1;
		y -= 1;

		if (inputData.mapData[i] != 0 && inputData.mapData[i] != 1)
		{
			inputData.mapData[i] = 1;
		}

		m_colArray[y][x] = inputData.mapData[i];
	}
}

void MiniMap::Move(VECTOR playerPos)
{
	m_direction = (static_cast<int>(m_arrowAngle * 100) / 157) % 4;
	SerDir();

	if (m_direction == Top)	//è„å¸Ç´
	{
		if (m_colArray[m_colY - 1][m_colX] == 1)
		{
			m_isMove = true;
		}
		else
		{
			m_isMove = false;
		}

	}
	else if (m_direction == Right)	//âEå¸Ç´
	{
		if (m_colArray[m_colY][m_colX + 1] == 1)
		{
			m_isMove = true;
		}
		else
		{
			m_isMove = false;
		}
	}
	else if (m_direction == Bottom)	//âEå¸Ç´
	{
		if (m_colArray[m_colY + 1][m_colX] == 1)
		{
			m_isMove = true;
		}
		else
		{
			m_isMove = false;
		}
	}
	else if (m_direction == Left)	//ç∂å¸Ç´
	{
		if (m_colArray[m_colY][m_colX - 1] == 1)
		{
			m_isMove = true;
		}
		else
		{
			m_isMove = false;
		}
	}

	//à⁄ìÆèàóù
	m_arrowPos.x = m_startPos.x - playerPos.x / 150 * 32;
	m_arrowPos.y = m_startPos.y + playerPos.z / 150 * 32;
	

	if (m_arrowPos.x == m_arrowPosLog.x && m_arrowPos.y == m_arrowPosLog.y)
	{
		m_isDelColPos = true;
	}

	if (m_isDelColPos)
	{
		if (m_direction == Top)
		{
			if (m_arrowPos.x != m_arrowPosLog.x || m_arrowPos.y != m_arrowPosLog.y)
			{
				m_colY -= 1;
				m_isDelColPos = false;
			}
		}
		else if (m_direction == Right)
		{
			if (m_arrowPos.x != m_arrowPosLog.x || m_arrowPos.y != m_arrowPosLog.y)
			{
				m_colX += 1;
				m_isDelColPos = false;
			}
		}
		else if (m_direction == Bottom)
		{
			if (m_arrowPos.x != m_arrowPosLog.x || m_arrowPos.y != m_arrowPosLog.y)
			{
				m_colY += 1;
				m_isDelColPos = false;
			}
		}
		else if (m_direction == Left)
		{
			if (m_arrowPos.x != m_arrowPosLog.x || m_arrowPos.y != m_arrowPosLog.y)
			{
				m_colX -= 1;
				m_isDelColPos = false;
			}
		}
	}
}

void MiniMap::SerDir()
{
	if (m_direction == 0)
	{
		m_direction = Top;
	}
	else if (m_direction == 1 || m_direction == -3)
	{
		m_direction = Right;
	}
	else if (m_direction == 2 || m_direction == -2)
	{
		m_direction = Bottom;
	}
	else if (m_direction == 3 || m_direction == -1)
	{
		m_direction = Left;
	}
}

void MiniMap::DrawTreasure()
{
	int x = static_cast<int>(kMapPosXLeft + m_treasurePos.x * 32 + 16);
	int y = static_cast<int>(m_treasurePos.z * 32 + 16);
	DrawCircle(x,y,8,0xffff00,true);
	DrawCircle(x,y,8,0x000000,false);
}

void MiniMap::DrawGrid()
{
	//îwåiÇÃîíçïÇÃï`âÊ
	for (int i = 0; i < kRow*kCol;i++)
	{
		int x = i % 13;
		int y = i / 13;

		if (m_colArray[y][x] == 1)
		{
			x = x * 32 + 16+ kMapPosXLeft;
			y = y * 32 + 16;
			DrawBox(x - 16, y - 16,x + 16,y + 16,0xffffff,true);
		}
		else
		{
			x = x * 32 + 16 + kMapPosXLeft;
			y = y * 32 + 16;
			DrawBox(x - 16, y - 16, x + 16, y + 16, 0x000000, true);
		}
	}

	//ècâ°ÇÃê¸Çï`âÊ
	for (int x = kMapPosXLeft; x <= kMapPosXRight; x += 32)
	{
		DrawLine(x, kMapPosYTop, x, kMapPosYBottom, 0x0000ff);
	}

	for (int y = kMapPosYTop; y <= kMapPosYBottom; y += 32)
	{
		DrawLine(kMapPosXLeft, y, kMapPosXRight, y, 0x0000ff);
	}
}
