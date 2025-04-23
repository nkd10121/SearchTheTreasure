#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Input.h"
#include "ScoreManager.h"
#include "GraphManager.h"
#include "ModelManager.h"

namespace
{
	enum eUIname:int
	{
		eRetry,
		eReturn,
		UINUM
	};

	constexpr int kUIPosX = 640;
	constexpr int kUIPosY[eUIname::UINUM] = {490,590};

	constexpr int kCursolPosX = kUIPosX - 180;

}

SceneResult::SceneResult(SceneManager& mgr, int num) :
	SceneBase		(mgr),
	m_treasureNum	(num),
	m_rad			(0.0f)
{
	//カメラの設定
	SetCameraNearFar(0.1f, 800.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f));
	ChangeLightTypePoint(VGet(0.0f, 4.0f, 0.0f), 500.0f, 0.8f, 0.0018f, 0.0f);

	m_pScore = mgr.GetScoreData();
	m_pScore->Input(num);
	m_pScore->Save();

	m_pGraphManager = mgr.GetGarphManager();
	m_pGraphManager->Load("retry", "data/graph/UI/retry.png");
	m_pGraphManager->Load("return", "data/graph/UI/return.png");

	m_pGraphManager->Load("quantity", "data/graph/UI/quantity.png");

	m_cursolPosY = kUIPosY[eRetry];

	std::shared_ptr<ModelManager> modelManager;
	modelManager = mgr.GetModelManager();
	m_roomHandle = modelManager->GetHandle("room");
	MV1SetPosition(m_roomHandle, VGet(0.0f, 0.0f, 0.0f));
	MV1SetScale(m_roomHandle, VGet(0.5f, 0.5f, 0.5f));

	m_pSoundManager = mgr.GetSoundManager();
	m_pSoundManager->Load("resultBGM","data/sound/BGM/ファンタジー8-悲しみ-.mp3",true);
}

SceneResult::~SceneResult()
{
}

void SceneResult::Update(Input& input)
{
	m_pSoundManager->PlayBGM("resultBGM",true);

	m_rad += static_cast<float>(DX_PI / 60);

	if (input.IsTriggered("DOWN"))
	{
		if (m_cursolPosY == kUIPosY[eUIname::eRetry])
		{
			m_pSoundManager->PlaySE("cursolMoveSE");
			m_cursolPosY = kUIPosY[eUIname::eReturn];
		}
	}

	if (input.IsTriggered("UP"))
	{
		if (m_cursolPosY == kUIPosY[eUIname::eReturn])
		{
			m_pSoundManager->PlaySE("cursolMoveSE");
			m_cursolPosY = kUIPosY[eUIname::eRetry];
		}
	}

	if (input.IsTriggered("OK"))
	{
		if (m_cursolPosY == kUIPosY[eUIname::eRetry])
		{
			m_pSoundManager->StopBGM("resultBGM");
			m_pSoundManager->PlaySE("cursolOKSE");
			m_manager.ChangeScene(std::make_shared<SceneGame>(m_manager,0,600));
		}
		if (m_cursolPosY == kUIPosY[eUIname::eReturn])
		{
			m_pSoundManager->StopBGM("resultBGM");
			m_pSoundManager->PlaySE("cursolOKSE");
			m_manager.ChangeScene(std::make_shared<SceneTitle>(m_manager));
		}
	}
}

void SceneResult::Draw()
{
	MV1DrawModel(m_roomHandle);

	DrawTreasureNum();

	float alpha = sinf(m_rad);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * abs(alpha)));
	m_pGraphManager->Draw(kCursolPosX, m_cursolPosY, 0.5f, 0.0f, "cursol");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	m_pGraphManager->Draw(kUIPosX, kUIPosY[eUIname::eRetry], 0.5f, 0.0f, "retry");
	m_pGraphManager->Draw(kUIPosX, kUIPosY[eUIname::eReturn], 0.5f, 0.0f, "return");

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Result");
	DrawFormatString(0, 16, 0xffffff, "お宝の数:%d",m_treasureNum);
#endif
}

void SceneResult::DrawTreasureNum()
{
	if (m_treasureNum < 10)
	{
		m_pGraphManager->Draw(640, 200, 1.0f, 0.0f, std::to_string(m_treasureNum));
		m_pGraphManager->Draw(740, 220, 0.6f, 0.0f, "quantity");
	}
	else if (m_treasureNum >= 10 && m_treasureNum < 100)
	{
		int tens = m_treasureNum / 10;
		int ones = m_treasureNum % 10;

		m_pGraphManager->Draw(600, 200, 1.0f, 0.0f, std::to_string(tens));
		m_pGraphManager->Draw(680, 200, 1.0f, 0.0f, std::to_string(ones));
		m_pGraphManager->Draw(760, 220, 0.6f, 0.0f, "quantity");

	}
	else if (m_treasureNum >= 100 && m_treasureNum < 1000)
	{
		int hundred = m_treasureNum / 100;
		int tens = (m_treasureNum - 100 * hundred) / 10;
		int ones = (m_treasureNum - 100 * hundred) % 10;

		m_pGraphManager->Draw(560, 200, 1.0f, 0.0f, std::to_string(hundred));
		m_pGraphManager->Draw(640, 200, 1.0f, 0.0f, std::to_string(tens));
		m_pGraphManager->Draw(720, 200, 1.0f, 0.0f, std::to_string(ones));
		m_pGraphManager->Draw(800, 220, 0.6f, 0.0f, "quantity");
	}
}
