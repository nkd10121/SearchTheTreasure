#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>

class GraphManager;
class ModelManager;
class SoundManager;
class Chest;

class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& mgr);
	virtual~SceneTitle();

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
	void DrawRanking();

	//更新メンバ関数ポインタ
	void (SceneTitle::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	void (SceneTitle::* drawFunc_)();

	//更新関数
	void DefaultUpdate(Input& input);
	void RankingUpdate(Input& input);
	//描画関数
	void DefaultDraw();
	void RankingDraw();

private:
	std::shared_ptr<GraphManager> m_pGraphManager;	//グラフマネージャーのポインタ
	std::shared_ptr<SoundManager> m_pSoundManager;	//サウンドネージャーのポインタ
	std::shared_ptr<Chest> m_pChest;	//チェストのポインタ

	int m_cursolPosY;	//カーソルのY座標
	float m_rad;		//カーソルを点滅させる用のラジアン

	int m_roomHandle;
	int m_chestHandle;

	std::vector<int> m_score;	//スコア


};

