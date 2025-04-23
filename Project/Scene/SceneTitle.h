#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>

class GraphManager;
class ModelManager;
class SoundManager;
class Chest;

class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& mgr);
	virtual~SceneTitle();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private:
	void DrawRanking();

	//�X�V�����o�֐��|�C���^
	void (SceneTitle::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	void (SceneTitle::* drawFunc_)();

	//�X�V�֐�
	void DefaultUpdate(Input& input);
	void RankingUpdate(Input& input);
	//�`��֐�
	void DefaultDraw();
	void RankingDraw();

private:
	std::shared_ptr<GraphManager> m_pGraphManager;	//�O���t�}�l�[�W���[�̃|�C���^
	std::shared_ptr<SoundManager> m_pSoundManager;	//�T�E���h�l�[�W���[�̃|�C���^
	std::shared_ptr<Chest> m_pChest;	//�`�F�X�g�̃|�C���^

	int m_cursolPosY;	//�J�[�\����Y���W
	float m_rad;		//�J�[�\����_�ł�����p�̃��W�A��

	int m_roomHandle;
	int m_chestHandle;

	std::vector<int> m_score;	//�X�R�A


};

