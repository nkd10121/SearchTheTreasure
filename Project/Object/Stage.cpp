#include "Stage.h"

namespace
{
	const enum ePartsName
	{
		corrider,	//通路
		end,		//終点
		turn,		//曲道
		separate,	//十字路
		tJunction,	//T字路
		Num
	};

	//モデルのサイズ
	constexpr int kModelSize = 150;
	constexpr int kModelHalfSize = kModelSize/2;

	//四分の一回転
	constexpr int kQuarterDegree = 90;
}


Stage::Stage():
	m_startX	(0),
	m_startY	(0)
{
	m_stagePartsHandle.resize(ePartsName::Num);

	m_stagePartsHandle[ePartsName::corrider] = MV1LoadModel("data/model/corridor.mv1");
	m_stagePartsHandle[ePartsName::end] = MV1LoadModel("data/model/end.mv1");
	m_stagePartsHandle[ePartsName::turn] = MV1LoadModel("data/model/turn.mv1");
	m_stagePartsHandle[ePartsName::separate] = MV1LoadModel("data/model/separate.mv1");
	m_stagePartsHandle[ePartsName::tJunction] = MV1LoadModel("data/model/tJunction.mv1");

	m_textureHandle[0] = LoadGraph("data/textures/Diffuse_01.png");
	m_textureHandle[1] = LoadGraph("data/textures/Normal_01.png");
	m_textureHandle[2] = LoadGraph("data/textures/Neon.png");
}

Stage::~Stage()
{
	for (int i = 0; i < m_stagePartsHandle.size(); i++)
	{
		MV1DeleteModel(m_stagePartsHandle[i]);
	}

	for (int i = 0; i < kTexNum; i++)
	{
		DeleteGraph(m_textureHandle[i]);
	}
}

void Stage::Init()
{

}

void Stage::Draw()
{
	for (auto& model : m_stage)
	{
		MV1DrawModel(model.handle);
	}
}

void Stage::SetMapData(float startX,float startY,std::vector<int> data)
{
	//念のため初期化
	m_stage.clear();

	//キャスト
	m_startX = static_cast<int>(startX);
	m_startY = static_cast<int>(startY);
	m_mapData = data;

	//二重配列に入れる
	for (int i = 0; i < m_mapData.size(); i++)
	{
		int x = i % 15;
		int y = i / 15;

		m_mapArray[y][x] = m_mapData[i];
	}

	CreateStage();

	return;
}

void Stage::CreateStage()
{
	for (int i = 0; i < m_mapData.size(); i++)
	{
		int x = i % 15;
		int y = i / 15;

		//上下左右方向の情報を持っておく
		int top = m_mapArray[y - 1][x];
		int topTwo = m_mapArray[y - 2][x];
		int right = m_mapArray[y][x + 1];
		int rightTwo = m_mapArray[y][x + 2];
		int bottom = m_mapArray[y + 1][x];
		int bottomTwo = m_mapArray[y + 2][x];
		int left = m_mapArray[y][x - 1];
		int leftTwo = m_mapArray[y][x - 2];

		//分岐点の処理
		if (m_mapArray[y][x] == 3)
		{
			//十字路の処理
			if (right == 1 && bottom == 1 && left == 1 && top == 1)
			{
				CreateStageData(ePartsName::separate, x, y, 0, 0, -kModelSize);
				continue;
			}

			//T字路の処理
			if (right == 1 && bottom == 1 && left == 1)
			{
				CreateStageData(ePartsName::tJunction, x, y, kQuarterDegree, 0, -kModelHalfSize);
				continue;
			}
			if (right == 1 && bottom == 1 && top == 1)
			{
				CreateStageData(ePartsName::tJunction, x, y, 0, -kModelHalfSize, -kModelSize);
				continue;
			}
			if (top == 1 && bottom == 1 && left == 1)
			{
				CreateStageData(ePartsName::tJunction, x, y, kQuarterDegree*2, kModelHalfSize, -kModelSize);
				continue;
			}
			if (right == 1 && top == 1 && left == 1)
			{
				CreateStageData(ePartsName::tJunction, x, y, kQuarterDegree*3, 0, -(kModelSize + kModelHalfSize));
				continue;
			}

			//曲がり道の処理
			if (right == 1 && bottom == 1)
			{
				CreateStageData(ePartsName::turn, x, y, 0, -kModelHalfSize, -kModelHalfSize);
				continue;
			}
			if (left == 1 && bottom == 1)
			{
				CreateStageData(ePartsName::turn, x, y, kQuarterDegree, kModelHalfSize, -kModelHalfSize);
				continue;
			}
			if (right == 1 && top == 1)
			{
				CreateStageData(ePartsName::turn, x, y, kQuarterDegree*3, -kModelHalfSize, -(kModelSize + kModelHalfSize));
				continue;
			}
			if (left == 1 && top == 1)
			{
				CreateStageData(ePartsName::turn, x, y, kQuarterDegree*2, kModelHalfSize, -(kModelSize + kModelHalfSize));
				continue;
			}
		}

		//通路の処理
		if (m_mapArray[y][x] == 1)
		{
			//上下方向に通路があるかを判定する
			bool isUpAndDown = top != 0 && bottom != 0;

			// 上下方向に道があるときの通路を生成
			if (isUpAndDown)
			{
				bool isCreate = top <= 2 && bottom <= 2;
				bool isCreateTwo = topTwo <= 2 && bottomTwo <= 2;
				if (isCreate && isCreateTwo)
				{
					CreateStageData(ePartsName::corrider, x, y, kQuarterDegree,0,-kModelSize);
					continue;
				}
			}
			else	//左右方向に道があるときの通路を生成
			{
				bool isCreate = right <= 2 && left <= 2;
				bool isCreateTwo = rightTwo <= 2 && leftTwo <= 2;
				if (isCreate && isCreateTwo)
				{
					CreateStageData(ePartsName::corrider, x, y, 0,0, -kModelSize);
					continue;
				}
			}
		}

		//終点部分の処理
		if (m_mapArray[y][x] == 2)
		{
			//どの方向に通路が存在するか判定する
			bool isTop = top != 0 && right == 0 && left == 0 && bottom == 0;
			bool isBottom = top == 0 && right == 0 && left == 0 && bottom != 0;
			bool isLeft = top == 0 && right == 0 && left != 0 && bottom == 0;
			bool isRight = top == 0 && right != 0 && left == 0 && bottom == 0;

			/*通路がある方向に対応した向きに設置する*/

			if (isTop)
			{
				CreateStageData(ePartsName::end, x, y, kQuarterDegree*3, 0, -kModelSize);
				continue;
			}

			if (isBottom)
			{
				CreateStageData(ePartsName::end, x, y, kQuarterDegree, 0, -kModelSize);
				continue;
			}
			
			if (isLeft)
			{
				CreateStageData(ePartsName::end, x, y, kQuarterDegree*2, 0, -kModelSize);
				continue;
			}

			if (isRight)
			{
				CreateStageData(ePartsName::end, x, y, 0, 0, -kModelSize);
				continue;
			}
		}
	}
}

/// <summary>
/// ステージデータの生成
/// </summary>
/// <param name="handleNum">モデルハンドル</param>
/// <param name="idxX">マップデータのX座標</param>
/// <param name="idxY">マップデータのY座標</param>
/// <param name="angle">回転(度数法)</param>
/// <param name="offsetX">X座標の調整</param>
/// <param name="offsetY">Y座標の調整</param>
void Stage::CreateStageData(int handleNum,int idxX,int idxY,int angle, int offsetX,int offsetY)
{
	StageData temp;
	//ハンドルの複製
	temp.handle = MV1DuplicateModel(m_stagePartsHandle[handleNum]);

	//サイズが大きいため設定
	MV1SetScale(temp.handle, VGet(0.5f, 0.5f, 0.5f));
	//テクスチャの設定
	for (int i = 0; i < 3; i++)
	{
		MV1SetTextureGraphHandle(temp.handle, i, m_textureHandle[i], FALSE);
	}
	
	//座標の設定
	VECTOR pos = VGet((m_startX - idxX + 1) * 150.0f + offsetX, 0.0f, (m_startY - idxY) * -150.0f + offsetY);
	MV1SetPosition(temp.handle, pos);
	MV1SetRotationXYZ(temp.handle, VGet(0.0f, angle * DX_PI_F / 180.0f, 0.0f));
	temp.pos = pos;

	
	m_stage.push_back(temp);
}
