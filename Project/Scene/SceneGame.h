#pragma once
#include "SceneBase.h"
#include "DataLoader.h"
#include <memory>

class Player;
class MiniMap;
class Chest;
class Stage;
class GraphManager;
class SoundManager;

class SceneGame : public SceneBase
{
public:
	SceneGame(SceneManager& mgr, int treasureNum,int limitFrame);
	virtual ~SceneGame();

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
	/// <summary>
	/// �^�C�}�[�̕`�揈��
	/// </summary>
	void DrawTimer();

private:
	int m_frame;	//�Q�[���V�[���ɑJ�ڂ��Ă���̃t���[����
	int m_timer;	//�t���[��������b�ɕϊ������l

	VECTOR m_clearPos;

	int m_timeLimit;

	int m_treasureNum;	//�擾��������̑���

	std::shared_ptr<Player> m_pPlayer;		//�v���C���[
	std::shared_ptr<MiniMap> m_pMiniMap;	//�~�j�}�b�v
	std::shared_ptr<Stage> m_pStage;		//�X�e�[�W
	std::shared_ptr<Chest> m_pChest;		//�`�F�X�g
	std::shared_ptr<GraphManager> m_pGraphManager;		//�O���t�}�l�[�W���[
	std::shared_ptr<SoundManager> m_pSoundManager;		//�T�E���h�}�l�[�W���[

	std::map <std::string, DataLoader::stageData> m_stageData;	//�X�e�[�W�f�[�^
	std::string m_useStageName;			//�g�p����X�e�[�W��
};

