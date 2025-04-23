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
	/// �X�V����
	/// </summary>
	void Draw();

	/// <summary>
	/// �`�F�X�g�̕`����W��ݒ肷��
	/// </summary>
	/// <param name="pos">�`�F�X�g��`�悳���������W</param>
	void SetPos(VECTOR pos);

	/// <summary>
	/// �`�F�X�g�̌�����ݒ肷��
	/// </summary>
	/// <param name="dir">�`�F�X�g����������������</param>
	void SetDir(float dir);

	const int GetModelHandle()const;

private:
	int m_handle;	//�`�F�X�g�̃��f���n���h��
};

