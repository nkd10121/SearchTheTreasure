#pragma once
#include <vector>
#include <list>
#include <string>
#include <memory>

class ScoreManager
{
public:
	ScoreManager();
	virtual ~ScoreManager();

	void Input(int score);

	void Load();

	void Save();

	std::list<int> GetScore()const { return m_score; };
private:
	std::list<int> m_score;
};

