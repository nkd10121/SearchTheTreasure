#pragma once
#include "SceneBase.h"
#include <memory>

class ScoreManager;
class GraphManager;
class SoundManager;

class SceneResult : public SceneBase
{
public:
	SceneResult(SceneManager& mgr,int num);
	virtual~SceneResult();

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
	void DrawTreasureNum();

private:
	int m_treasureNum;	//お宝の数

	int m_cursolPosY;	//カーソルのY座標
	float m_rad;		//カーソルを点滅させる用のラジアン

	std::shared_ptr<ScoreManager> m_pScore;			//スコアを管理するクラスのポインタ
	std::shared_ptr<GraphManager> m_pGraphManager;	//グラフマネージャーのポインタ
	std::shared_ptr<SoundManager> m_pSoundManager;	//サウンドマネージャーのポインタ

	int m_roomHandle;
};

