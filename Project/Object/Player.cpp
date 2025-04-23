#include "Player.h"
#include "Input.h"

namespace
{
	constexpr float kCameraDist = 150.1f;

	constexpr float kMoveSpeed = 10.0f;
	constexpr float kMoveFrame = 150.0f / kMoveSpeed;

	constexpr float kAngleMoveFrame = 15.0f;
	constexpr float kAngleMoveSpeed = 3.14f / 2 / kAngleMoveFrame;
}

Player::Player():
	m_moveVec			(VGet(0,0,0)),
	m_moveFrame			(0),
	m_cameraTargetPos	(VGet(0, 0, 0)),
	m_angleMoveFrame	(0),
	m_isMove			(false)
{
	SetCameraNearFar(0.1f, 400.0f);

	m_cameraAngle = -3.14f / 2;
	m_pos = VGet(0, 0, -0);

	updateFunc_ = &Player::NormalUpdate;
}

void Player::Update(Input& input,bool isMove)
{
	m_isMove = isMove;
	m_moveVec = VGet(0, 0, 0);

	m_cameraTargetPos.x = m_pos.x + cosf(m_cameraAngle) * kCameraDist;
	m_cameraTargetPos.y = 0;
	m_cameraTargetPos.z = m_pos.z + sinf(m_cameraAngle) * kCameraDist;

	ChangeLightTypePoint(m_pos, 400.0f, 0.6f, 0.0008f, 0.0f);
	SetCameraPositionAndTarget_UpVecY(m_pos, m_cameraTargetPos);
	(this->*updateFunc_)(input);
}

void Player::NormalUpdate(Input& input)
{
	if (m_isMove)
	{
		if (input.IsPushed("UP"))
		{
			updateFunc_ = &Player::MoveUpdate;
		}
	}

	if (input.IsTriggered("RIGHT"))
	{
		updateFunc_ = &Player::ViewpointToRight;
	}
	if (input.IsTriggered("LEFT"))
	{
		updateFunc_ = &Player::ViewpointToLeft;
	}
}

void Player::MoveUpdate(Input& input)
{
	m_moveFrame++;

	m_moveVec = VSub(m_cameraTargetPos, m_pos);
	m_moveVec = VNorm(m_moveVec);
	m_moveVec = VScale(m_moveVec, kMoveSpeed);

	//è¨êîì_à»â∫ÇÃåÎç∑ÇâÒîÇ∑ÇÈÇΩÇﬂÇÃêÿÇËéÃÇƒ
	if (abs(m_moveVec.x) < kMoveSpeed - 0.01f)
	{
		m_moveVec.x = 0.0f;
	}
	if (abs(m_moveVec.y) < kMoveSpeed - 0.01f)
	{
		m_moveVec.y = 0.0f;
	}
	if (abs(m_moveVec.z) < kMoveSpeed - 0.01f)
	{
		m_moveVec.z = 0.0f;
	}

	//è¨êîì_à»â∫ÇÃåÎç∑ÇâÒîÇ∑ÇÈÇΩÇﬂÇ…éléÃå‹ì¸
	m_moveVec.x = static_cast<float>(round(m_moveVec.x * 100) / 100);
	m_moveVec.y = static_cast<float>(round(m_moveVec.y * 100) / 100);
	m_moveVec.z = static_cast<float>(round(m_moveVec.z * 100) / 100);

	m_pos = VAdd(m_pos, m_moveVec);

	if (m_moveFrame == kMoveFrame)
	{
		m_moveFrame = 0;
		updateFunc_ = &Player::NormalUpdate;
	}
}

void Player::ViewpointToRight(Input& input)
{
	m_angleMoveFrame++;
	m_cameraAngle -= kAngleMoveSpeed;

	if (m_angleMoveFrame == kAngleMoveFrame)
	{
		m_angleMoveFrame = 0;
		updateFunc_ = &Player::NormalUpdate;
	}
}

void Player::ViewpointToLeft(Input& input)
{
	m_angleMoveFrame++;

	m_cameraAngle += kAngleMoveSpeed;

	if (m_angleMoveFrame == kAngleMoveFrame)
	{
		m_angleMoveFrame = 0;
		updateFunc_ = &Player::NormalUpdate;
	}
}

