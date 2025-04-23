#include "Input.h"
#include <DxLib.h>

Input::Input()
{
	m_commandTable["OK"] = { KEY_INPUT_RETURN };

	m_commandTable["JUMP"] = { KEY_INPUT_SPACE };

	m_commandTable["UP"] = { KEY_INPUT_UP };

	m_commandTable["DOWN"] = { KEY_INPUT_DOWN };

	m_commandTable["RIGHT"] = { KEY_INPUT_RIGHT };

	m_commandTable["LEFT"] = { KEY_INPUT_LEFT };
}

void Input::Update()
{
	m_lastInputData = m_inputData;	//���O���͂��R�s�[���Ă���(�������u�Ԃ��擾����p)

	//�n�[�h�E�F�A���̓`�F�b�N
	char keystate[256];
	GetHitKeyStateAll(keystate);//���݂̃L�[�{�[�h���͂��擾

	//�o�^���ꂽ���ƃn�[�h�̏����Ƃ炵���킹�Ȃ���
	//inputData_�̓��e���X�V���Ă���
	for (const auto& cmd : m_commandTable)
	{
		auto& input = m_inputData[cmd.first];//�R�}���h�̖��O������̓f�[�^�����
		input = false;
		if (keystate[cmd.second])
		{
			input = true;
			break;
		}
	}
}

bool Input::IsTriggered(const char* command) const
{
	auto it = m_inputData.find(command);
	if (it == m_inputData.end())	//��񂪂Ȃ����false��Ԃ�
	{
		return false;
	}
	return (m_inputData.at(command) && !m_lastInputData.at(command));
}

bool Input::IsPushed(const char* command) const
{
	auto it = m_inputData.find(command);
	if (it == m_inputData.end())	//��񂪂Ȃ����false��Ԃ�
	{
		return false;
	}
	return (m_inputData.at(command) && m_lastInputData.at(command));
}