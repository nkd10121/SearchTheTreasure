#pragma once
#include "DxLib.h"


class Input;
class SceneManager;

/// <summary>
/// �V�[�����N���X
/// �����ȃV�[���̊�ɂȂ�N���X
/// </summary>
class SceneBase
{
public:
	/// <summary>
	/// ��������SceneManager�̎Q�Ƃ��󂯎���Ă���
	/// </summary>
	/// <param name="manager">SceneManager�̎Q��</param>
	SceneBase(SceneManager& manager);

	/// <summary>
	/// �V�[���̍X�V
	/// </summary>
	/// <param name="input"></param>
	virtual void Update(Input& input) = 0;

	/// <summary>
	/// �V�[���̕`��
	/// </summary>
	virtual void Draw() = 0;

protected:
	SceneManager& m_manager;	//�V�[���Ǘ��N���X�̎Q��

};

