#include "Chest.h"
#include "ModelManager.h"
#include <list>
#include <string>

namespace
{
	//チェストのサイズ
	constexpr float kChestSize = 40.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelMgr">モデルマネージャー</param>
Chest::Chest(std::shared_ptr<ModelManager> modelMgr)
{
	//モデルのロード
	modelMgr->LoadModel("chest", "data/model/chest.mv1");
	//モデルマネージャーからハンドルをもらう
	m_handle = modelMgr->GetHandle("chest");

	/*テクスチャの設定*/
	std::list<std::string> texPath;
	texPath.push_back("data/textures/dungeon_texture.png");
	modelMgr->SetTexture("chest", texPath);

	//座標の初期化
	MV1SetPosition(m_handle, VGet(0.0f, 0.0f, 0.0f));
	//元のままだと小さすぎたためサイズの変更
	MV1SetScale(m_handle,VGet(kChestSize, kChestSize, kChestSize));

}


/// <summary>
/// 座標の設定
/// </summary>
/// <param name="pos">設定したい座標(マップ基準)</param>
void Chest::SetPos(VECTOR pos)
{
	pos.x = pos.x * -150.0f;
	pos.z = pos.z * 150.0f;

	pos.y -= 74;
	MV1SetPosition(m_handle, pos);
}

/// <summary>
/// 向きの設定
/// </summary>
/// <param name="dir">向かせたい角度</param>
void Chest::SetDir(float dir)
{
	MV1SetRotationXYZ(m_handle, VGet(0.0f, dir * DX_PI_F / 180.0f, 0.0f));
}

/// <summary>
/// チェストのハンドルを取得
/// </summary>
/// <returns></returns>
const int Chest::GetModelHandle() const
{
	return MV1DuplicateModel(m_handle);
}

void Chest::Draw()
{
	MV1DrawModel(m_handle);
}
