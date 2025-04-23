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
	m_lastInputData = m_inputData;	//直前入力をコピーしておく(押した瞬間を取得する用)

	//ハードウェア入力チェック
	char keystate[256];
	GetHitKeyStateAll(keystate);//現在のキーボード入力を取得

	//登録された情報とハードの情報を照らし合わせながら
	//inputData_の内容を更新していく
	for (const auto& cmd : m_commandTable)
	{
		auto& input = m_inputData[cmd.first];//コマンドの名前から入力データを作る
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
	if (it == m_inputData.end())	//情報がなければfalseを返す
	{
		return false;
	}
	return (m_inputData.at(command) && !m_lastInputData.at(command));
}

bool Input::IsPushed(const char* command) const
{
	auto it = m_inputData.find(command);
	if (it == m_inputData.end())	//情報がなければfalseを返す
	{
		return false;
	}
	return (m_inputData.at(command) && m_lastInputData.at(command));
}