#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "GraphManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "ModelManager.h"
#include "Chest.h"
#include "Input.h"

#include <list>

namespace
{
	enum UIname : int
	{
		start,
		ranking,
		quit
	};

	constexpr float kChestPosY = -75.0f;
	const VECTOR kChestPos = VGet(0.0f, kChestPosY,0.0f);
	const VECTOR kTargetPos = VGet(0.0f, kChestPosY + 18.0f,0.0f);

	constexpr int kUIPosX = 1100;				//X座標
	constexpr int kUIPosY[3] = {440,540,640};	//Y座標
	constexpr float kUIsize = 0.5f;				//サイズ

	constexpr int kCursolPosX = kUIPosX - 180;

	constexpr float kCameraDist = 80.0f;
	constexpr float kCameraHeight = kChestPosY + 36.0f;

	constexpr int kNumPosY[3] = { 320,480,620 };
}

SceneTitle::SceneTitle(SceneManager& mgr) :
	SceneBase	(mgr),
	m_rad		(0.0f)
{
	//カメラの設定
	SetCameraNearFar(0.1f, 800.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, kCameraHeight, kCameraDist), kTargetPos);
	ChangeLightTypePoint(VGet(0.0f, 4.0f, 0.0f), 500.0f, 0.8f, 0.0018f, 0.0f);

	//画像の読み込み
	m_pGraphManager = mgr.GetGarphManager();
	m_pGraphManager->Load("title", "data/graph/UI/title.png");
	m_pGraphManager->Load("start", "data/graph/UI/start.png");
	m_pGraphManager->Load("ranking", "data/graph/UI/ranking.png");
	m_pGraphManager->Load("quit", "data/graph/UI/quit.png");
	m_pGraphManager->Load("cursol", "data/graph/UI/cursol.png");


	m_cursolPosY = kUIPosY[start];

	m_pChest = std::make_shared<Chest>(mgr.GetModelManager());
	m_chestHandle = m_pChest->GetModelHandle();
	MV1SetPosition(m_chestHandle, kChestPos);
	MV1SetScale(m_chestHandle, VGet(20, 20, 20));

	auto& modelMgr = mgr.GetModelManager();
	modelMgr->LoadModel("room", "data/model/room.mv1");
	m_roomHandle = modelMgr->GetHandle("room");
	std::list<std::string>textureHandle;
	textureHandle.push_back("data/textures/Diffuse_01.png");
	textureHandle.push_back("data/textures/Normal_01.png");
	textureHandle.push_back("data/textures/Neon.png");

	MV1SetPosition(m_roomHandle,VGet(0.0f,0.0f,0.0f));
	MV1SetScale(m_roomHandle, VGet(0.5f, 0.5f, 0.5f));

	modelMgr->SetTexture("room",textureHandle);


	//画像の読み込み
	m_pGraphManager = mgr.GetGarphManager();
	m_pGraphManager->Load("first", "data/graph/UI/first.png");		//一位の画像
	m_pGraphManager->Load("second", "data/graph/UI/second.png");	//二位の画像
	m_pGraphManager->Load("third", "data/graph/UI/third.png");		//三位の画像

	//スコアマネージャーの取得
	auto& scoreManager = mgr.GetScoreData();
	//スコアの取得
	auto score = scoreManager->GetScore();
	m_score.resize(score.size());
	int idx = 0;
	for (auto& s : score)
	{
		m_score[idx] = s;
		idx++;
	}


	m_pSoundManager = mgr.GetSoundManager();
	m_pSoundManager->Load("titleBGM", "data/sound/BGM/ファンタジー6-幻-.mp3",true);
	m_pSoundManager->Load("cursolMoveSE", "data/sound/SE/選択5.mp3",false);
	m_pSoundManager->Load("cursolOKSE", "data/sound/SE/決定14.mp3",false);

	updateFunc_ = &SceneTitle::DefaultUpdate;
	drawFunc_ = &SceneTitle::DefaultDraw;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update(Input& input)
{
	m_pSoundManager->PlayBGM("titleBGM", true);


	m_rad += static_cast<float>(DX_PI / 60);

	(this->*updateFunc_)(input);

	VECTOR cameraPos;
	cameraPos.x = sinf(m_rad / 3) * kCameraDist;
	cameraPos.y = kCameraHeight;
	cameraPos.z = cosf(m_rad / 3) * kCameraDist;
	SetCameraPositionAndTarget_UpVecY(cameraPos, kTargetPos);

	if (input.IsTriggered("DOWN"))
	{
		if (m_cursolPosY == kUIPosY[ranking])
		{
			m_pSoundManager->PlaySE("cursolMoveSE");
			m_cursolPosY = kUIPosY[quit];
		}

		if (m_cursolPosY == kUIPosY[start])
		{
			m_pSoundManager->PlaySE("cursolMoveSE");
			m_cursolPosY = kUIPosY[ranking];
		}
	}

	if (input.IsTriggered("UP"))
	{
		if (m_cursolPosY == kUIPosY[ranking])
		{
			m_pSoundManager->PlaySE("cursolMoveSE");
			m_cursolPosY = kUIPosY[start];
		}

		if (m_cursolPosY == kUIPosY[quit])
		{
			m_pSoundManager->PlaySE("cursolMoveSE");
			m_cursolPosY = kUIPosY[ranking];
		}
	}

	if (input.IsTriggered("OK"))
	{
		if (m_cursolPosY == kUIPosY[start])
		{
			m_pSoundManager->PlaySE("cursolOKSE");

			m_pSoundManager->StopBGM("titleBGM");
			m_manager.ChangeScene(std::make_shared<SceneGame>(m_manager,0,600));
		}

		if (m_cursolPosY == kUIPosY[quit])
		{
			DxLib_End();		// DXライブラリ使用の終了処理
			return;				// ソフトの終了 
		}
	}
}

void SceneTitle::Draw()
{
	MV1DrawModel(m_roomHandle);
	
	MV1DrawModel(m_chestHandle);
	(this->*drawFunc_)();

	float alpha = sinf(m_rad);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * abs(alpha)));
	m_pGraphManager->Draw(kCursolPosX, m_cursolPosY, kUIsize, 0.0f, "cursol");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	m_pGraphManager->Draw(kUIPosX, kUIPosY[start], kUIsize, 0.0f, "start");
	m_pGraphManager->Draw(kUIPosX, kUIPosY[ranking], kUIsize, 0.0f, "ranking");
	m_pGraphManager->Draw(kUIPosX, kUIPosY[quit], kUIsize, 0.0f, "quit");

#ifdef _DEBUG
	DrawFormatString(0,0,0xffffff,"Title");
#endif
}

void SceneTitle::DrawRanking()
{
	//数を表示
	for (int i = 0; i < m_score.size(); i++)
	{
		//10個以下の時
		if (m_score[i] < 10)
		{
			auto name = std::to_string(m_score[i]);
			m_pGraphManager->Draw(740, kNumPosY[i], 1.0f, 0.0f, name);
		}
		else if (m_score[i] >= 10 && m_score[i] < 100)	//10個以上100個未満の時
		{
			int tens = m_score[i] / 10;
			int ones = m_score[i] % 10;

			m_pGraphManager->Draw(700, kNumPosY[i], 1.0f, 0.0f, to_string(tens));
			m_pGraphManager->Draw(780, kNumPosY[i], 1.0f, 0.0f, to_string(ones));
		}
		else if (m_score[i] >= 100 && m_score[i] < 1000)	//100個以上1000個未満の時
		{
			int hundred = m_score[i] / 100;
			int tens = (m_score[i] - 100 * hundred) / 10;
			int ones = (m_score[i] - 100 * hundred) % 10;

			m_pGraphManager->Draw(560, 200, 1.0f, 0.0f, std::to_string(hundred));
			m_pGraphManager->Draw(640, 200, 1.0f, 0.0f, std::to_string(tens));
			m_pGraphManager->Draw(720, 200, 1.0f, 0.0f, std::to_string(ones));
		}

	}
}

void SceneTitle::DefaultUpdate(Input& input)
{
	if ((m_cursolPosY == kUIPosY[UIname::ranking]) && input.IsTriggered("OK"))
	{
		m_pSoundManager->PlaySE("cursolOKSE");

		updateFunc_ = &SceneTitle::RankingUpdate;
		drawFunc_ = &SceneTitle::RankingDraw;
	}
}

void SceneTitle::RankingUpdate(Input& input)
{
	if (input.IsTriggered("OK") || input.IsTriggered("DOWN") || input.IsTriggered("UP"))
	{
		updateFunc_ = &SceneTitle::DefaultUpdate;
		drawFunc_ = &SceneTitle::DefaultDraw;
	}
}

void SceneTitle::DefaultDraw()
{
	m_pGraphManager->Draw(269,140,1.0f,0.0f,"title");
}

void SceneTitle::RankingDraw()
{
	/*枠の描画*/
	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	DrawBox(30, 30, 920 - 30, 720 - 30, 0x222222, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(30, 30, 920 - 30, 720 - 30, 0xffffff, false);

	//画像の描画
	m_pGraphManager->Draw(300, 80, 0.8f, 0.0f, "ranking");

	m_pGraphManager->Draw(320, kNumPosY[0], 1.0f, 0.0f, "first");
	m_pGraphManager->Draw(320, kNumPosY[1], 0.6f, 0.0f, "second");
	m_pGraphManager->Draw(320, kNumPosY[2], 0.6f, 0.0f, "third");

	DrawRanking();
}
