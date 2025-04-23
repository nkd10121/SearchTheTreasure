#pragma once
#include "SceneBase.h"
#include <memory>

class ScoreManager;
class GraphManager;
class SoundManager;

class SceneResult : public SceneBase
{
public:
	SceneResult(SceneManager& mgr,int num);
	virtual~SceneResult();

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
	void DrawTreasureNum();

private:
	int m_treasureNum;	//����̐�

	int m_cursolPosY;	//�J�[�\����Y���W
	float m_rad;		//�J�[�\����_�ł�����p�̃��W�A��

	std::shared_ptr<ScoreManager> m_pScore;			//�X�R�A���Ǘ�����N���X�̃|�C���^
	std::shared_ptr<GraphManager> m_pGraphManager;	//�O���t�}�l�[�W���[�̃|�C���^
	std::shared_ptr<SoundManager> m_pSoundManager;	//�T�E���h�}�l�[�W���[�̃|�C���^

	int m_roomHandle;
};

