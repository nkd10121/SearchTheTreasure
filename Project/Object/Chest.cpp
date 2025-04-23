#include "Chest.h"
#include "ModelManager.h"
#include <list>
#include <string>

namespace
{
	//�`�F�X�g�̃T�C�Y
	constexpr float kChestSize = 40.0f;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelMgr">���f���}�l�[�W���[</param>
Chest::Chest(std::shared_ptr<ModelManager> modelMgr)
{
	//���f���̃��[�h
	modelMgr->LoadModel("chest", "data/model/chest.mv1");
	//���f���}�l�[�W���[����n���h�������炤
	m_handle = modelMgr->GetHandle("chest");

	/*�e�N�X�`���̐ݒ�*/
	std::list<std::string> texPath;
	texPath.push_back("data/textures/dungeon_texture.png");
	modelMgr->SetTexture("chest", texPath);

	//���W�̏�����
	MV1SetPosition(m_handle, VGet(0.0f, 0.0f, 0.0f));
	//���̂܂܂��Ə������������߃T�C�Y�̕ύX
	MV1SetScale(m_handle,VGet(kChestSize, kChestSize, kChestSize));

}


/// <summary>
/// ���W�̐ݒ�
/// </summary>
/// <param name="pos">�ݒ肵�������W(�}�b�v�)</param>
void Chest::SetPos(VECTOR pos)
{
	pos.x = pos.x * -150.0f;
	pos.z = pos.z * 150.0f;

	pos.y -= 74;
	MV1SetPosition(m_handle, pos);
}

/// <summary>
/// �����̐ݒ�
/// </summary>
/// <param name="dir">�����������p�x</param>
void Chest::SetDir(float dir)
{
	MV1SetRotationXYZ(m_handle, VGet(0.0f, dir * DX_PI_F / 180.0f, 0.0f));
}

/// <summary>
/// �`�F�X�g�̃n���h�����擾
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
