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
	/// �v���C���[(�J����)�̌��ݍ��W��Ԃ�
	/// </summary>
	/// <returns></returns>
	const VECTOR GetPos()const { return m_pos; }

	/// <summary>
	/// �v���C���[�������Ă��������Ԃ�
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

	//�X�V�����o�֐��|�C���^
	void (Player::* updateFunc_)(Input& input);

	//�X�V�֐�
	void NormalUpdate(Input& input);
	void MoveUpdate(Input& input);
	void ViewpointToRight(Input& input);
	void ViewpointToLeft(Input& input);
};

