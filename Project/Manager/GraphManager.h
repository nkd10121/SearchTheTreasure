#pragma once
#include "DxLib.h"
#include <string>
#include <vector>

using namespace std;

struct Graph;

class GraphManager
{
public:
	GraphManager();
	virtual ~GraphManager();

	void Init() { };

	void Load(string name, string path);

	void Draw(int x, int y, float exRate, float angle, string name);
	void MyDrawRotaGraph(int x,int y,int cx,int cy, float exRateX, float exRateY, float angle,std::string name);

	int GetHandle(string name)const;

private:
	vector<Graph*> m_graph;
};

