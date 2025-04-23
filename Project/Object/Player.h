#pragma once
#include "DxLib.h"

class Input;

class Player
{
public:
	Player();
	virtual ~Player() {};

	void Update(Input& input,bool isMove);

	/// <summary>
	/// プレイヤー(カメラ)の現在座標を返す
	/// </summary>
	/// <returns></returns>
	const VECTOR GetPos()const { return m_pos; }

	/// <summary>
	/// プレイヤーが向いている方向を返す
	/// </summary>
	/// <returns></returns>
	const float GetAngle()const { return m_cameraAngle; }

private:
	VECTOR m_pos;
	VECTOR m_moveVec;
	int m_moveFrame;

	VECTOR m_cameraTargetPos;
	float m_cameraAngle;
	int m_angleMoveFrame;

	bool m_isMove;

	//更新メンバ関数ポインタ
	void (Player::* updateFunc_)(Input& input);

	//更新関数
	void NormalUpdate(Input& input);
	void MoveUpdate(Input& input);
	void ViewpointToRight(Input& input);
	void ViewpointToLeft(Input& input);
};

