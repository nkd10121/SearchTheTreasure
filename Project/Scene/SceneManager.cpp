#include "SceneBase.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GraphManager.h"
#include "ModelManager.h"
#include "DataLoader.h"
#include "Stage.h"

namespace
{
	//パスの前部分のストリング型
	const std::string kNumberPathFront = "data/graph/number/";
	//パスの後ろ部分のストリング型
	const std::string kNumberPathBack = ".png";
}

SceneManager::SceneManager()
{
	//グラフマネージャーの生成
	m_pGraphManager = std::make_shared<GraphManager>();

	//数字のGraphの読み込み
	for (int i = 0; i < 10; i++)
	{
		//iをストリング型にキャスト
		auto num = to_string(i);

		//上の3つを1つに合体させてパスを作成
		auto path = kNumberPathFront + num + kNumberPathBack;
		//出来上がったパスの画像をロードする
		m_pGraphManager->Load(num, path);
	}

	//データマネージャーの生成
	m_pStageData = std::make_shared<DataLoader>();
	//データのロード
	m_pStageData->StageLoad();
	//モデルマネージャーの生成
	m_pModelManager = std::make_shared<ModelManager>();
	//サウンドマネージャの生成
	m_pSoundManager = std::make_shared<SoundManager>();
	//スコアマネージャーの生成
	m_pScore = std::make_shared<ScoreManager>();
	//スコアのロード
	m_pScore->Load();
	//ステージの生成
	m_pStage = std::make_shared<Stage>();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(Input& input)
{
	//末尾のみ実行
	scenes.back()->Update(input);
}

void SceneManager::Draw()
{
	//先頭から順に描画
	//最後に積んだものが最後に描画される
	for (auto& scenes : scenes)
	{
		scenes->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<SceneBase> nextScene)
{
	if (scenes.empty())//リストが空っぽだったら入れ替えずに
	{
		scenes.push_back(nextScene);//末尾に追加
	}
	else
	{
		scenes.back() = nextScene;//既に一つ以上あれば末尾を
	}
}
