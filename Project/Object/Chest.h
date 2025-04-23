#pragma once
#include "DxLib.h"
#include <memory>

class ModelManager;

class Chest
{
public:
	Chest(std::shared_ptr<ModelManager> modelMgr);
	virtual ~Chest() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	void Draw();

	/// <summary>
	/// チェストの描画座標を設定する
	/// </summary>
	/// <param name="pos">チェストを描画させたい座標</param>
	void SetPos(VECTOR pos);

	/// <summary>
	/// チェストの向きを設定する
	/// </summary>
	/// <param name="dir">チェストを向かせたい向き</param>
	void SetDir(float dir);

	const int GetModelHandle()const;

private:
	int m_handle;	//チェストのモデルハンドル
};

