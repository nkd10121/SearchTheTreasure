#pragma once
#include <list> 
#include <memory>
#include <windows.h>

class Input;
class SceneBase;
class DataLoader;
class ScoreManager;
class SoundManager;
class GraphManager;
class ModelManager;
class Stage;
class Chest;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	/// <summary>
	/// 持っているシーンのUpdate関数を呼び出す
	/// </summary>
	/// <param name="input">入力クラス</param>
	void Update(Input& input);

	/// <summary>
	/// 持っているシーンのDraw関数を呼び出す
	/// </summary>
	void Draw();

	/// <summary>
	/// 実行中のシーンを引数で指定したシーンに切り替える
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeScene(std::shared_ptr<SceneBase> nextScene);

	/// <summary>
	/// グラフマネージャーのポインタを返す
	/// </summary>
	/// <returns>グラフマネージャーのポインタ</returns>
	const std::shared_ptr<GraphManager> GetGarphManager()const { return m_pGraphManager; };

	/// <summary>
	/// モデルマネージャーのポインタを返す
	/// </summary>
	/// <returns>モデルマネージャーのポインタ</returns>
	const std::shared_ptr<ModelManager> GetModelManager()const { return m_pModelManager; };	
	
	/// <summary>
	/// サウンドマネージャーのポインタを返す
	/// </summary>
	/// <returns>サウンドマネージャーのポインタ</returns>
	const std::shared_ptr<SoundManager> GetSoundManager()const { return m_pSoundManager; };

	/// <summary>
	/// ロードしたデータを管理するクラスのポインタを返す
	/// </summary>
	/// <returns>ロードしたデータを持つクラスのポインタ</returns>
	const std::shared_ptr<DataLoader> GetLoadData()const { return m_pStageData; };

	/// <summary>
	/// スコアを管理するクラスのポインタを返す
	/// </summary>
	/// <returns>スコアを管理するクラスのポインタ</returns>
	const std::shared_ptr<ScoreManager> GetScoreData()const { return m_pScore; };

	/// <summary>
	/// ステージを生成するクラスのポインタを返す
	/// </summary>
	/// <returns>ステージを生成するクラスのポインタ</returns>
	const std::shared_ptr<Stage> GetStage()const { return m_pStage; };

	/// <summary>
	/// 宝箱を管理するクラスのポインタを返す
	/// </summary>
	/// <returns>宝箱を管理するクラスのポインタ</returns>
	const std::shared_ptr<Chest> GetChest()const { return m_pChest; };

private:
	std::list<std::shared_ptr<SceneBase>> scenes;	//シーン

	std::shared_ptr<GraphManager> m_pGraphManager;	//グラフマネージャー
	std::shared_ptr<ModelManager> m_pModelManager;	//モデルマネージャー
	std::shared_ptr<SoundManager> m_pSoundManager;	//サウンドマネージャー
	std::shared_ptr<DataLoader> m_pStageData;		//データマネージャー
	std::shared_ptr<ScoreManager> m_pScore;			//スコアマネージャー
	std::shared_ptr<Stage> m_pStage;					//ステージ
	std::shared_ptr<Chest> m_pChest;					//チェスト
};

