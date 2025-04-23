#include "GraphManager.h"
#include <cassert>

struct Graph
{
private:
	string GraphName = "";
	int GraphPath = 0;
public:
	void Set(std::string name, std::string path)
	{
		GraphName = name;
		GraphPath = LoadGraph(path.c_str());
		assert(GraphPath != -1);
	}
	std::string GetName()const
	{
		return GraphName;
	}

	int GetHandle()const
	{
		return GraphPath;
	}

	void Delete()
	{
		DeleteGraph(GraphPath);
	}
};



GraphManager::GraphManager()
{
	m_graph.resize(0);
}

GraphManager::~GraphManager()
{
	for (int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph[i])
		{
			m_graph[i]->Delete();
			delete m_graph[i];
			m_graph[i] = nullptr;
		}
	}
}

void GraphManager::Load(string name, string path)
{
	m_graph.resize(m_graph.size() + 1);

	for (int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph[i])
		{
			if (m_graph[i]->GetName() == name)
			{
				m_graph.pop_back();
				return;
			}
		}
		else if (!m_graph[i])
		{
			m_graph[i] = new Graph;
			m_graph[i]->Set(name, path);
		}
	}
}

void GraphManager::Draw(int x, int y, float exRate, float angle, string name)
{
	for (int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph[i])
		{
			if (m_graph[i]->GetName() == name)
			{
				DrawRotaGraph(x, y, exRate, angle, m_graph[i]->GetHandle(), true);
				return;
			}
		}
	}

	return;
}

void GraphManager::MyDrawRotaGraph(int x, int y, int cx, int cy, float exRateX, float exRateY, float angle, std::string name)
{
	for (int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph[i])
		{
			if (m_graph[i]->GetName() == name)
			{
				DrawRotaGraphFast3(x, y, cx,cy,exRateX,exRateY, angle, m_graph[i]->GetHandle(), true);
				return;
			}
		}
	}

	return;
}

int GraphManager::GetHandle(string name) const
{
	for (int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph[i])
		{
			if (m_graph[i]->GetName() == name)
			{
				return m_graph[i]->GetHandle();
			}
		}
	}

	//����name�ƈ�v���閼�O���Ȃ�������
	return -1;
}
