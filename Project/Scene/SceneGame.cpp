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
	//1秒あたりのフレーム数
	constexpr int kFramePerSeconds = 60;

	//一回クリアするごとに減らすタイムリミットのフレーム数
	constexpr int kDelTimeLimitFrame = 8;
	//タイムリミットの下限
	constexpr int kTimeLimitMin = 360;
	//タイマーのUIの描画Y座標
	constexpr int kTimerPosY = 680;

	//タイマーのUIのX軸の拡大率の最大
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
	/*データのロード*/
	std::shared_ptr<DataLoader> pData = mgr.GetLoadData();
	m_stageData = pData->GetStageData();	//ステージデータの取得
	auto& stageName = pData->GetStageName();	//ステージの名前を取得

	//どのステージを使用するか
	int stageNum = GetRand(static_cast<int>(m_stageData.size()) - 1);
	//stageNum = 0;
	m_useStageName = stageName[stageNum];

	//クリア座標を計算して取得
	m_clearPos = VSub(m_stageData[m_useStageName].clearPos, m_stageData[m_useStageName].startPos);
	m_clearPos.x *= -150.0f;
	m_clearPos.z *= 150.0f;

	//プレイヤーの初期化
	m_pPlayer = std::make_shared<Player>();

	//ミニマップの初期化
	m_pMiniMap = std::make_shared<MiniMap>();
	m_pMiniMap->SetMiniMap(m_stageData[m_useStageName]);

	//ステージの作成
	m_pStage = mgr.GetStage();
	m_pStage->SetMapData(m_stageData[m_useStageName].startPos.x,
		m_stageData[m_useStageName].startPos.z,
		m_stageData[m_useStageName].mapData);

	//タイマーの画像のロード
	m_pGraphManager = mgr.GetGarphManager();
	m_pGraphManager->Load("timerBarStart", "data/graph/UI/timer/meter_bar_holder_left_edge_yellow.png");			//外枠の左端
	m_pGraphManager->Load("timerBarMiddle", "data/graph/UI/timer/meter_bar_holder_center-repeating_yellow.png");	//外枠の真ん中
	m_pGraphManager->Load("timerBarEnd", "data/graph/UI/timer/meter_bar_holder_right_edge_yellow.png");				//外枠の右端

	m_pGraphManager->Load("timerInBarMiddle", "data/graph/UI/timer/meter_bar_center-repeating_yellow.png");			//内側の部分

	m_pGraphManager->Load("timerIcon", "data/graph/UI/timer/timer.png");			//時計のアイコン

	//宝箱関係
	m_pChest = std::make_shared<Chest>(mgr.GetModelManager());
	m_pChest->SetPos(VSub(m_stageData[m_useStageName].clearPos, m_stageData[m_useStageName].startPos));
	m_pChest->SetDir(m_stageData[m_useStageName].chestDir);

	m_pSoundManager = mgr.GetSoundManager();
	m_pSoundManager->Load("GameBGM","data/sound/BGM/ファンタジー-異変-.mp3",true);

	//タイムリミットの設定
	m_timeLimit = limitFrame;
}

SceneGame::~SceneGame()
{
}

void SceneGame::Update(Input& input)
{
	m_pSoundManager->PlayBGM("GameBGM", true);

	//フレームの更新
	m_frame++;
	//タイマーの更新
	m_timer = m_frame / kFramePerSeconds;

	//プレイヤーの更新
	m_pPlayer->Update(input,m_pMiniMap->GetIsMove());

	//ミニマップの更新
	m_pMiniMap->Update(m_pPlayer->GetPos(),m_pPlayer->GetAngle());

	//プレイヤーの座標を取得
	auto& playerPos = m_pPlayer->GetPos();

	//auto clearPos = VSub(m_stageData[m_useStageName].clearPos, m_stageData[m_useStageName].startPos);
	//clearPos.x = clearPos.x * -150.0f;
	//clearPos.z = clearPos.z * 150.0f;

	//プレイヤーの座標とクリア座標が一致していたら
	if (m_clearPos.x == playerPos.x && m_clearPos.z == playerPos.z)
	{
		//タイムリミットを4フレームだけ減らす
		m_timeLimit -= kDelTimeLimitFrame;
		//もし6秒(360フレーム)より短くなったら6秒になるように補正
		if (m_timeLimit <= kTimeLimitMin)
		{
			m_timeLimit = kTimeLimitMin;
		}

		//取得したお宝の数を1増やして
		m_treasureNum++;
		//新しいステージに遷移する
		m_manager.ChangeScene(std::make_shared<SceneGame>(m_manager, m_treasureNum, m_timeLimit));
		return;
	}

	//時間制限が来たら
	if (m_frame == m_timeLimit)
	{
		m_pSoundManager->StopBGM("GameBGM");
		//結果画面に遷移する
		m_manager.ChangeScene(std::make_shared<SceneResult>(m_manager, m_treasureNum));
		return;
	}

#ifdef _DEBUG	//DEBUG
	//Enterキーを押したら
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
	//ステージの描画
	m_pStage->Draw();

	//ミニマップの描画
	m_pMiniMap->Draw();

	//お宝の描画
	m_pChest->Draw();

	//タイマーの描画
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
	//現在のフレーム数/タイムリミットのフレーム数で割合を計算して
	auto rate = (static_cast<float>(m_frame) / static_cast<float>(m_timeLimit));
	//タイマーのグラフの横方向の拡大率を出す
	float magX = kTimerMagXMax - kTimerMagXMax * rate;

	//タイマーの外枠を描画
	m_pGraphManager->MyDrawRotaGraph(320, kTimerPosY,0,0, kTimerMag, kTimerMag, 0.0f, "timerBarStart");
	m_pGraphManager->MyDrawRotaGraph(640, kTimerPosY,110,0,2.8f, kTimerMag, 0.0f, "timerBarMiddle");
	m_pGraphManager->MyDrawRotaGraph(940, kTimerPosY,0,0, kTimerMag, kTimerMag, 0.0f, "timerBarEnd");
	
	//タイマーの中身を描画
	m_pGraphManager->MyDrawRotaGraph(330, kTimerPosY, 0, 0, magX, kTimerMag, 0.0f, "timerInBarMiddle");
	//タイマーのアイコンを描画
	m_pGraphManager->MyDrawRotaGraph(302, 674, 0, 0, 0.14f, 0.14f, 0.0f, "timerIcon");


}
