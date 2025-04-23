#include "SceneBase.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GraphManager.h"
#include "ModelManager.h"
#include "DataLoader.h"
#include "Stage.h"

namespace
{
	//�p�X�̑O�����̃X�g�����O�^
	const std::string kNumberPathFront = "data/graph/number/";
	//�p�X�̌�땔���̃X�g�����O�^
	const std::string kNumberPathBack = ".png";
}

SceneManager::SceneManager()
{
	//�O���t�}�l�[�W���[�̐���
	m_pGraphManager = std::make_shared<GraphManager>();

	//������Graph�̓ǂݍ���
	for (int i = 0; i < 10; i++)
	{
		//i���X�g�����O�^�ɃL���X�g
		auto num = to_string(i);

		//���3��1�ɍ��̂����ăp�X���쐬
		auto path = kNumberPathFront + num + kNumberPathBack;
		//�o���オ�����p�X�̉摜�����[�h����
		m_pGraphManager->Load(num, path);
	}

	//�f�[�^�}�l�[�W���[�̐���
	m_pStageData = std::make_shared<DataLoader>();
	//�f�[�^�̃��[�h
	m_pStageData->StageLoad();
	//���f���}�l�[�W���[�̐���
	m_pModelManager = std::make_shared<ModelManager>();
	//�T�E���h�}�l�[�W���̐���
	m_pSoundManager = std::make_shared<SoundManager>();
	//�X�R�A�}�l�[�W���[�̐���
	m_pScore = std::make_shared<ScoreManager>();
	//�X�R�A�̃��[�h
	m_pScore->Load();
	//�X�e�[�W�̐���
	m_pStage = std::make_shared<Stage>();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(Input& input)
{
	//�����̂ݎ��s
	scenes.back()->Update(input);
}

void SceneManager::Draw()
{
	//�擪���珇�ɕ`��
	//�Ō�ɐς񂾂��̂��Ō�ɕ`�悳���
	for (auto& scenes : scenes)
	{
		scenes->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<SceneBase> nextScene)
{
	if (scenes.empty())//���X�g������ۂ����������ւ�����
	{
		scenes.push_back(nextScene);//�����ɒǉ�
	}
	else
	{
		scenes.back() = nextScene;//���Ɉ�ȏ゠��Ζ�����
	}
}
