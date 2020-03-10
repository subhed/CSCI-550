#include <climits>
#include <algorithm>
#include <queue>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

#ifndef TIMESTAMP_H
#define TIMESTAMP_H
class TimeStamp
{
public:
	TimeStamp() : d(0), f(0){};
	int d; //discovery time
	int f; //finish time
};

#endif

/********** Directed Graph ************/

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
	Graph();
	Graph(const Graph &ag);

	void printGraph();

	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);
	void printParents();
	void printDistance();

	//need to write these functions:
	void topSort(); //builds topOrder vector<int>
	void topSortVisit(int u, int &t);

	void SSCtopSort(); //builds topOrder vector<int>
	void SSCtopSortVisit(int u, int &t);

	void printTopOrder();

	void buildTranspose();

	void printTranspose();

	void SSCdfsVisit(int u, int &t, int id);
	void SSCdfs();

	int dfsTR();

	void buildSCC();
	void printSCC();
	void SCCbuildTranspose();

private:
	vector<vector<int>> Adj;  //adjacency lists of the graph
	vector<int> distance;	  //for BFS
	vector<int> parents;	  //for BFS and DFS
	vector<char> colors;	  //for DFS
	vector<TimeStamp> stamps; //for DFS
	vector<int> topOrder;
	int size; //total vertices in the graph
	vector<vector<int>> transpose;
	vector<vector<int>> SSCom;
	vector<int> sscID;
	vector<vector<int>> SCC;
};

#endif

void Graph::printTopOrder()
{

	for (int i = 0; i < size; i++)
	{
		cout << topOrder[i] << " ";
	}

	cout << endl;
}

void Graph::SSCtopSort()
{

	for (int i = 0; i < SCC.size(); i++)
	{
		parents[i] = i;
		colors[i] = 'W';
	}
	int t = 0;

	for (int i = 0; i < SCC.size(); i++)
	{
		if (colors[i] == 'W')
		{
			SSCtopSortVisit(i, t);
		} //if
	}	  //for

	int half = SCC.size() / 2;
	for (int i = 0; i < half; i++)
	{
		swap(topOrder[i], topOrder[size - i - 1]);
	}
}

void Graph::SSCtopSortVisit(int u, int &t)
{
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

	for (int i = 0; i < (int)SCC[u].size(); i++)
	{
		int v = SCC[u][i];
		if (colors[v] == 'W')
		{
			parents[v] = u;
			colors[v] = 'G';
			SSCtopSortVisit(v, t);
		}
	} //for
	colors[u] = 'B';
	stamps[u].f = t;
	topOrder.push_back(u);
	t++;
} //dfsVisit

void Graph::topSort()
{

	for (int i = 0; i < size; i++)
	{
		parents[i] = i;
		colors[i] = 'W';
	}
	int t = 0;

	for (int i = 0; i < size; i++)
	{
		if (colors[i] == 'W')
		{
			topSortVisit(i, t);
		} //if
	}	  //for

	int half = size / 2;
	for (int i = 0; i < half; i++)
	{
		swap(topOrder[i], topOrder[size - i - 1]);
	}
}

void Graph::topSortVisit(int u, int &t)
{
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

	for (int i = 0; i < (int)Adj[u].size(); i++)
	{
		int v = Adj[u][i];
		if (colors[v] == 'W')
		{
			parents[v] = u;
			colors[v] = 'G';
			topSortVisit(v, t);
		}
	} //for
	colors[u] = 'B';
	stamps[u].f = t;
	topOrder.push_back(u);
	t++;
} //dfsVisit

int Graph::dfsTR()
{

	for (int i = 0; i < size; i++)
	{
		parents[i] = i;
		colors[i] = 'W';
	}

	int t = 0;
	int id = 0;
	sscID.resize(size);

	for (int i = 0; i < size; i++)
	{
		if (colors[topOrder[i]] == 'W')
		{
			SSCdfsVisit(topOrder[i], t, id);

			id++;
		} //if
	}

	return id;
}

void Graph::SSCdfsVisit(int u, int &t, int id)
{
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	sscID[u] = id;
	for (int i = 0; i < (int)transpose[u].size(); i++)
	{
		int v = transpose[u][i];
		if (colors[v] == 'W')
		{
			parents[v] = u;
			colors[v] = 'G';
			SSCdfsVisit(v, t, id);
		}
	} //for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
} //dfsVisit

void Graph::printSCC()
{
	//format:
	//vertex: list of neighbors
	for (int u = 0; u < (int)SCC.size(); u++)
	{
		cout << u << ": ";
		for (int j = 0; j < (int)SCC[u].size(); j++)
		{
			int v = SCC[u][j]; //v is a neighbor
			cout << v << " ";
		}
		cout << endl;
	}
}

void Graph::buildSCC()
{
	topSort();
	buildTranspose();

	int id = dfsTR();
	SCC.resize(id);

	for (int u = 0; u < size; u++)
	{
		for (int j = 0; j < (int)Adj[u].size(); j++)
		{
			int v = Adj[u][j];
			if (sscID[u] != sscID[v])
			{
				SCC[sscID[u]].push_back(sscID[v]);
			}
		}
	}

	topOrder.clear();
	parents.clear();
	stamps.clear();
	colors.clear();
	distance.clear();
	transpose.clear();

	SSCtopSort();
	// printTopOrder();

	SCCbuildTranspose();

	distance.clear();
	distance.resize(SCC.size());

	// cout<<"BFS on : "<< topOrder[size-1]<<endl;

	bfs(topOrder[size - 1]);

	int flag = 0;
	for (unsigned i = 0; i < distance.size(); i++)
	{
		if (distance[i] == INT_MAX)
		{
			flag = 1;
		}
	}

	if (flag == 0)
	{
		int finalans = INT_MAX;
		for (unsigned i = 0; i < sscID.size(); i++)
		{
			if (sscID[i] == topOrder[size - 1])
			{
				if (i < finalans)
				{
					finalans = i;
				}
			}
		}

		cout << finalans << endl;
	}
	else
	{
		cout << "-1" << endl;
	}


}

void Graph::buildTranspose()
{

	transpose.resize(size);
	for (int u = 0; u < size; u++)
	{
		for (unsigned j = 0; j < (int)Adj[u].size(); j++)
		{
			int v = Adj[u][j];
			transpose[v].push_back(u);
		}
	}
}

void Graph::SCCbuildTranspose()
{
	transpose.clear();
	transpose.resize(SCC.size());

	for (int u = 0; u < SCC.size(); u++)
	{
		for (int j = 0; j < (int)SCC[u].size(); j++)
		{
			int v = SCC[u][j];
			transpose[v].push_back(u);
		}
	}
}

 
Graph::Graph()
{
	cin >> size;
	int m;
	cin >> m;
	int u, v;
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		Adj[u].push_back(v);
	} //for

	for (int i = 0; i < size; i++)
	{
		distance[i] = INT_MAX;
		parents[i] = i;
		colors[i] = 'W';
	}
} //default

void Graph::bfs(int s)
{
	for (int i = 0; i < transpose.size(); i++)
	{
		distance[i] = INT_MAX;
		parents[i] = i;
	} //for

	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while (!aq.empty())
	{
		int u = aq.front();
		aq.pop();

		for (int i = 0; i < (int)transpose[u].size(); i++)
		{
			int v = transpose[u][i];

			if (distance[v] == INT_MAX)
			{
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		} //for
	}	  //while

} //bfs



int main()
{

	Graph ag;

	ag.buildSCC();

	return 0;
}
