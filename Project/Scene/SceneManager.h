#pragma once
#include <list> 
#include <memory>
#include <windows.h>

class Input;
class SceneBase;
class DataLoader;
class ScoreManager;
class SoundManager;
class GraphManager;
class ModelManager;
class Stage;
class Chest;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	/// <summary>
	/// �����Ă���V�[����Update�֐����Ăяo��
	/// </summary>
	/// <param name="input">���̓N���X</param>
	void Update(Input& input);

	/// <summary>
	/// �����Ă���V�[����Draw�֐����Ăяo��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���s���̃V�[���������Ŏw�肵���V�[���ɐ؂�ւ���
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeScene(std::shared_ptr<SceneBase> nextScene);

	/// <summary>
	/// �O���t�}�l�[�W���[�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>�O���t�}�l�[�W���[�̃|�C���^</returns>
	const std::shared_ptr<GraphManager> GetGarphManager()const { return m_pGraphManager; };

	/// <summary>
	/// ���f���}�l�[�W���[�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>���f���}�l�[�W���[�̃|�C���^</returns>
	const std::shared_ptr<ModelManager> GetModelManager()const { return m_pModelManager; };	
	
	/// <summary>
	/// �T�E���h�}�l�[�W���[�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>�T�E���h�}�l�[�W���[�̃|�C���^</returns>
	const std::shared_ptr<SoundManager> GetSoundManager()const { return m_pSoundManager; };

	/// <summary>
	/// ���[�h�����f�[�^���Ǘ�����N���X�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>���[�h�����f�[�^�����N���X�̃|�C���^</returns>
	const std::shared_ptr<DataLoader> GetLoadData()const { return m_pStageData; };

	/// <summary>
	/// �X�R�A���Ǘ�����N���X�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>�X�R�A���Ǘ�����N���X�̃|�C���^</returns>
	const std::shared_ptr<ScoreManager> GetScoreData()const { return m_pScore; };

	/// <summary>
	/// �X�e�[�W�𐶐�����N���X�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>�X�e�[�W�𐶐�����N���X�̃|�C���^</returns>
	const std::shared_ptr<Stage> GetStage()const { return m_pStage; };

	/// <summary>
	/// �󔠂��Ǘ�����N���X�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>�󔠂��Ǘ�����N���X�̃|�C���^</returns>
	const std::shared_ptr<Chest> GetChest()const { return m_pChest; };

private:
	std::list<std::shared_ptr<SceneBase>> scenes;	//�V�[��

	std::shared_ptr<GraphManager> m_pGraphManager;	//�O���t�}�l�[�W���[
	std::shared_ptr<ModelManager> m_pModelManager;	//���f���}�l�[�W���[
	std::shared_ptr<SoundManager> m_pSoundManager;	//�T�E���h�}�l�[�W���[
	std::shared_ptr<DataLoader> m_pStageData;		//�f�[�^�}�l�[�W���[
	std::shared_ptr<ScoreManager> m_pScore;			//�X�R�A�}�l�[�W���[
	std::shared_ptr<Stage> m_pStage;					//�X�e�[�W
	std::shared_ptr<Chest> m_pChest;					//�`�F�X�g
};

