#include "Stage.h"

namespace
{
	const enum ePartsName
	{
		corrider,	//�ʘH
		end,		//�I�_
		turn,		//�ȓ�
		separate,	//�\���H
		tJunction,	//T���H
		Num
	};

	//���f���̃T�C�Y
	constexpr int kModelSize = 150;
	constexpr int kModelHalfSize = kModelSize/2;

	//�l���̈��]
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
	//�O�̂��ߏ�����
	m_stage.clear();

	//�L���X�g
	m_startX = static_cast<int>(startX);
	m_startY = static_cast<int>(startY);
	m_mapData = data;

	//��d�z��ɓ����
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

		//�㉺���E�����̏��������Ă���
		int top = m_mapArray[y - 1][x];
		int topTwo = m_mapArray[y - 2][x];
		int right = m_mapArray[y][x + 1];
		int rightTwo = m_mapArray[y][x + 2];
		int bottom = m_mapArray[y + 1][x];
		int bottomTwo = m_mapArray[y + 2][x];
		int left = m_mapArray[y][x - 1];
		int leftTwo = m_mapArray[y][x - 2];

		//����_�̏���
		if (m_mapArray[y][x] == 3)
		{
			//�\���H�̏���
			if (right == 1 && bottom == 1 && left == 1 && top == 1)
			{
				CreateStageData(ePartsName::separate, x, y, 0, 0, -kModelSize);
				continue;
			}

			//T���H�̏���
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

			//�Ȃ��蓹�̏���
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

		//�ʘH�̏���
		if (m_mapArray[y][x] == 1)
		{
			//�㉺�����ɒʘH�����邩�𔻒肷��
			bool isUpAndDown = top != 0 && bottom != 0;

			// �㉺�����ɓ�������Ƃ��̒ʘH�𐶐�
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
			else	//���E�����ɓ�������Ƃ��̒ʘH�𐶐�
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

		//�I�_�����̏���
		if (m_mapArray[y][x] == 2)
		{
			//�ǂ̕����ɒʘH�����݂��邩���肷��
			bool isTop = top != 0 && right == 0 && left == 0 && bottom == 0;
			bool isBottom = top == 0 && right == 0 && left == 0 && bottom != 0;
			bool isLeft = top == 0 && right == 0 && left != 0 && bottom == 0;
			bool isRight = top == 0 && right != 0 && left == 0 && bottom == 0;

			/*�ʘH����������ɑΉ����������ɐݒu����*/

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
/// �X�e�[�W�f�[�^�̐���
/// </summary>
/// <param name="handleNum">���f���n���h��</param>
/// <param name="idxX">�}�b�v�f�[�^��X���W</param>
/// <param name="idxY">�}�b�v�f�[�^��Y���W</param>
/// <param name="angle">��](�x���@)</param>
/// <param name="offsetX">X���W�̒���</param>
/// <param name="offsetY">Y���W�̒���</param>
void Stage::CreateStageData(int handleNum,int idxX,int idxY,int angle, int offsetX,int offsetY)
{
	StageData temp;
	//�n���h���̕���
	temp.handle = MV1DuplicateModel(m_stagePartsHandle[handleNum]);

	//�T�C�Y���傫�����ߐݒ�
	MV1SetScale(temp.handle, VGet(0.5f, 0.5f, 0.5f));
	//�e�N�X�`���̐ݒ�
	for (int i = 0; i < 3; i++)
	{
		MV1SetTextureGraphHandle(temp.handle, i, m_textureHandle[i], FALSE);
	}
	
	//���W�̐ݒ�
	VECTOR pos = VGet((m_startX - idxX + 1) * 150.0f + offsetX, 0.0f, (m_startY - idxY) * -150.0f + offsetY);
	MV1SetPosition(temp.handle, pos);
	MV1SetRotationXYZ(temp.handle, VGet(0.0f, angle * DX_PI_F / 180.0f, 0.0f));
	temp.pos = pos;

	
	m_stage.push_back(temp);
}
