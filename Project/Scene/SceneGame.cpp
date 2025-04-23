#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GraphManager.h"
#include "Input.h"
#include "Player.h"
#include "MiniMap.h"
#include "Chest.h"
#include "Stage.h"

namespace
{
	//1�b������̃t���[����
	constexpr int kFramePerSeconds = 60;

	//���N���A���邲�ƂɌ��炷�^�C�����~�b�g�̃t���[����
	constexpr int kDelTimeLimitFrame = 8;
	//�^�C�����~�b�g�̉���
	constexpr int kTimeLimitMin = 360;
	//�^�C�}�[��UI�̕`��Y���W
	constexpr int kTimerPosY = 680;

	//�^�C�}�[��UI��X���̊g�嗦�̍ő�
	constexpr float kTimerMagXMax = 28.0f;

	constexpr float kTimerMag = 0.08f;
}

SceneGame::SceneGame(SceneManager& mgr, int treasureNum, int limitFrame):
	SceneBase		(mgr),
	m_treasureNum	(treasureNum),
	m_frame			(0),
	m_timer			(0),
	m_clearPos		(VGet(0.0f,0.0f,0.0f))
{
	/*�f�[�^�̃��[�h*/
	std::shared_ptr<DataLoader> pData = mgr.GetLoadData();
	m_stageData = pData->GetStageData();	//�X�e�[�W�f�[�^�̎擾
	auto& stageName = pData->GetStageName();	//�X�e�[�W�̖��O���擾

	//�ǂ̃X�e�[�W���g�p���邩
	int stageNum = GetRand(static_cast<int>(m_stageData.size()) - 1);
	//stageNum = 0;
	m_useStageName = stageName[stageNum];

	//�N���A���W���v�Z���Ď擾
	m_clearPos = VSub(m_stageData[m_useStageName].clearPos, m_stageData[m_useStageName].startPos);
	m_clearPos.x *= -150.0f;
	m_clearPos.z *= 150.0f;

	//�v���C���[�̏�����
	m_pPlayer = std::make_shared<Player>();

	//�~�j�}�b�v�̏�����
	m_pMiniMap = std::make_shared<MiniMap>();
	m_pMiniMap->SetMiniMap(m_stageData[m_useStageName]);

	//�X�e�[�W�̍쐬
	m_pStage = mgr.GetStage();
	m_pStage->SetMapData(m_stageData[m_useStageName].startPos.x,
		m_stageData[m_useStageName].startPos.z,
		m_stageData[m_useStageName].mapData);

	//�^�C�}�[�̉摜�̃��[�h
	m_pGraphManager = mgr.GetGarphManager();
	m_pGraphManager->Load("timerBarStart", "data/graph/UI/timer/meter_bar_holder_left_edge_yellow.png");			//�O�g�̍��[
	m_pGraphManager->Load("timerBarMiddle", "data/graph/UI/timer/meter_bar_holder_center-repeating_yellow.png");	//�O�g�̐^��
	m_pGraphManager->Load("timerBarEnd", "data/graph/UI/timer/meter_bar_holder_right_edge_yellow.png");				//�O�g�̉E�[

	m_pGraphManager->Load("timerInBarMiddle", "data/graph/UI/timer/meter_bar_center-repeating_yellow.png");			//�����̕���

	m_pGraphManager->Load("timerIcon", "data/graph/UI/timer/timer.png");			//���v�̃A�C�R��

	//�󔠊֌W
	m_pChest = std::make_shared<Chest>(mgr.GetModelManager());
	m_pChest->SetPos(VSub(m_stageData[m_useStageName].clearPos, m_stageData[m_useStageName].startPos));
	m_pChest->SetDir(m_stageData[m_useStageName].chestDir);

	m_pSoundManager = mgr.GetSoundManager();
	m_pSoundManager->Load("GameBGM","data/sound/BGM/�t�@���^�W�[-�ٕ�-.mp3",true);

	//�^�C�����~�b�g�̐ݒ�
	m_timeLimit = limitFrame;
}

SceneGame::~SceneGame()
{
}

void SceneGame::Update(Input& input)
{
	m_pSoundManager->PlayBGM("GameBGM", true);

	//�t���[���̍X�V
	m_frame++;
	//�^�C�}�[�̍X�V
	m_timer = m_frame / kFramePerSeconds;

	//�v���C���[�̍X�V
	m_pPlayer->Update(input,m_pMiniMap->GetIsMove());

	//�~�j�}�b�v�̍X�V
	m_pMiniMap->Update(m_pPlayer->GetPos(),m_pPlayer->GetAngle());

	//�v���C���[�̍��W���擾
	auto& playerPos = m_pPlayer->GetPos();

	//auto clearPos = VSub(m_stageData[m_useStageName].clearPos, m_stageData[m_useStageName].startPos);
	//clearPos.x = clearPos.x * -150.0f;
	//clearPos.z = clearPos.z * 150.0f;

	//�v���C���[�̍��W�ƃN���A���W����v���Ă�����
	if (m_clearPos.x == playerPos.x && m_clearPos.z == playerPos.z)
	{
		//�^�C�����~�b�g��4�t���[���������炷
		m_timeLimit -= kDelTimeLimitFrame;
		//����6�b(360�t���[��)���Z���Ȃ�����6�b�ɂȂ�悤�ɕ␳
		if (m_timeLimit <= kTimeLimitMin)
		{
			m_timeLimit = kTimeLimitMin;
		}

		//�擾��������̐���1���₵��
		m_treasureNum++;
		//�V�����X�e�[�W�ɑJ�ڂ���
		m_manager.ChangeScene(std::make_shared<SceneGame>(m_manager, m_treasureNum, m_timeLimit));
		return;
	}

	//���Ԑ�����������
	if (m_frame == m_timeLimit)
	{
		m_pSoundManager->StopBGM("GameBGM");
		//���ʉ�ʂɑJ�ڂ���
		m_manager.ChangeScene(std::make_shared<SceneResult>(m_manager, m_treasureNum));
		return;
	}

#ifdef _DEBUG	//DEBUG
	//Enter�L�[����������
	if (input.IsTriggered("OK"))
	{
		m_timeLimit -= kDelTimeLimitFrame;
		if (m_timeLimit <= kTimeLimitMin)
		{
			m_timeLimit = kTimeLimitMin;
		}

		m_treasureNum++;
		m_manager.ChangeScene(std::make_shared<SceneGame>(m_manager, m_treasureNum,m_timeLimit));
		return;
	}
#endif
}

void SceneGame::Draw()
{
	//�X�e�[�W�̕`��
	m_pStage->Draw();

	//�~�j�}�b�v�̕`��
	m_pMiniMap->Draw();

	//����̕`��
	m_pChest->Draw();

	//�^�C�}�[�̕`��
	DrawTimer();

#ifdef _DEBUG	//DEBUG
	DrawFormatString(0,0,0xffffff,"Game");
	DrawFormatString(0,96,0x000000,"%d", m_timer);

	DrawFormatString(0,16,0xffffff,"%s,%d", m_useStageName.c_str(),m_treasureNum);

	auto& playerPos = m_pPlayer->GetPos();
	DrawFormatString(0, 32, 0xff0000, "X:%f", playerPos.x);
	DrawFormatString(0, 48, 0xff0000, "Z:%f", playerPos.z);
#endif
}

void SceneGame::DrawTimer()
{
	//���݂̃t���[����/�^�C�����~�b�g�̃t���[�����Ŋ������v�Z����
	auto rate = (static_cast<float>(m_frame) / static_cast<float>(m_timeLimit));
	//�^�C�}�[�̃O���t�̉������̊g�嗦���o��
	float magX = kTimerMagXMax - kTimerMagXMax * rate;

	//�^�C�}�[�̊O�g��`��
	m_pGraphManager->MyDrawRotaGraph(320, kTimerPosY,0,0, kTimerMag, kTimerMag, 0.0f, "timerBarStart");
	m_pGraphManager->MyDrawRotaGraph(640, kTimerPosY,110,0,2.8f, kTimerMag, 0.0f, "timerBarMiddle");
	m_pGraphManager->MyDrawRotaGraph(940, kTimerPosY,0,0, kTimerMag, kTimerMag, 0.0f, "timerBarEnd");
	
	//�^�C�}�[�̒��g��`��
	m_pGraphManager->MyDrawRotaGraph(330, kTimerPosY, 0, 0, magX, kTimerMag, 0.0f, "timerInBarMiddle");
	//�^�C�}�[�̃A�C�R����`��
	m_pGraphManager->MyDrawRotaGraph(302, 674, 0, 0, 0.14f, 0.14f, 0.0f, "timerIcon");


}
