#pragma once
#include "SceneBase.h"
#include "DataLoader.h"
#include <memory>

class Player;
class MiniMap;
class Chest;
class Stage;
class GraphManager;
class SoundManager;

class SceneGame : public SceneBase
{
public:
	SceneGame(SceneManager& mgr, int treasureNum,int limitFrame);
	virtual ~SceneGame();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private:
	/// <summary>
	/// タイマーの描画処理
	/// </summary>
	void DrawTimer();

private:
	int m_frame;	//ゲームシーンに遷移してからのフレーム数
	int m_timer;	//フレーム数から秒に変換した値

	VECTOR m_clearPos;

	int m_timeLimit;

	int m_treasureNum;	//取得したお宝の総数

	std::shared_ptr<Player> m_pPlayer;		//プレイヤー
	std::shared_ptr<MiniMap> m_pMiniMap;	//ミニマップ
	std::shared_ptr<Stage> m_pStage;		//ステージ
	std::shared_ptr<Chest> m_pChest;		//チェスト
	std::shared_ptr<GraphManager> m_pGraphManager;		//グラフマネージャー
	std::shared_ptr<SoundManager> m_pSoundManager;		//サウンドマネージャー

	std::map <std::string, DataLoader::stageData> m_stageData;	//ステージデータ
	std::string m_useStageName;			//使用するステージ名
};

