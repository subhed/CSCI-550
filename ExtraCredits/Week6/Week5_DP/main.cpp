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

	//functions:
	void topSort();
	void topSort_dfsVisit(int u, int &t);
	void buildTranspose();
	void printTranspose();
	void printTopOrder();
	void buildSCC();
	void printSCC();
	int calcSCC_dfs();
	void calcSCC_dfsVisit(int u, int &t, int &cc);

	//need to write this function
	int countPaths();

private:
	vector<vector<int> > Adj;  //adjacency lists of the graph
	vector<int> distance;	  //for BFS
	vector<int> parents;	  //for BFS and DFS
	vector<char> colors;	  //for DFS
	vector<TimeStamp> stamps; //for DFS
	int size;				  //total vertices in the graph
	vector<int> topOrder;
	vector<vector<int> > transpose;
	vector<int> sc_components;
	vector<vector<int> > SCC;
};

#endif

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
	for (int i = 0; i < size; i++)
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

		for (int i = 0; i < (int)Adj[u].size(); i++)
		{
			int v = Adj[u][i];
			if (distance[v] == INT_MAX)
			{
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		} //for
	}	  //while

} //bfs

void Graph::dfs()
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
			dfsVisit(i, t);
		} //if
	}	  //for

} //dfs

void Graph::dfsVisit(int u, int &t)
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
			dfsVisit(v, t);
		}
	} //for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
} //dfsVisit

void Graph::printGraph()
{

	//format:
	//vertex: list of neighbors
	for (int u = 0; u < size; u++)
	{
		cout << u << ": ";
		for (int j = 0; j < (int)Adj[u].size(); j++)
		{
			int v = Adj[u][j]; //v is a neighbor
			cout << v << " ";
		}
		cout << endl;
	}
}

void Graph::printParents()
{
	for (int i = 0; i < size; i++)
	{
		cout << parents[i] << " ";
	}
	cout << endl;
}

void Graph::printDistance()
{
	for (int i = 0; i < size; i++)
	{
		cout << distance[i] << " ";
	}
	cout << endl;
}

//Topological Sort
void Graph::topSort()
{
	if (topOrder.size() > 0)
	{
		topOrder.clear();
		topOrder.resize(0);
	}
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
			topSort_dfsVisit(i, t);
		} //if
	}	  //for

	//reverse the order
	int halfSize = size / 2;
	int last = size - 1;
	for (int i = 0; i < halfSize; i++)
	{
		swap(topOrder[i], topOrder[last - i]);
	}
} //dfs

void Graph::topSort_dfsVisit(int u, int &t)
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
			topSort_dfsVisit(v, t);
		}
	} //for
	colors[u] = 'B';
	stamps[u].f = t;
	topOrder.push_back(u);
	t++;
} //topSort_dfsVisit

void Graph::buildTranspose()
{
	transpose.resize(size);
	for (int i = 0; i < size; i++)
	{
		transpose[i].resize(0);
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (int)Adj[i].size(); j++)
		{
			int v = Adj[i][j];
			transpose[v].push_back(i);
		}
	}
} //buildTranspose

void Graph::printTranspose()
{
	//format:
	//vertex: list of neighbors
	for (int u = 0; u < size; u++)
	{
		cout << u << ": ";
		for (int j = 0; j < (int)transpose[u].size(); j++)
		{
			int v = transpose[u][j]; //v is a neighbor
			cout << v << " ";
		}
		cout << endl;
	}
} //printTranspose

void Graph::printTopOrder()
{
	for (int i = 0; i < (int)topOrder.size(); i++)
		cout << topOrder[i] << " ";
	cout << endl;
} //printTopOrder

void Graph::buildSCC()
{
	topSort(); //topOrder contains the order we need
	buildTranspose();

	sc_components.resize(size);
	int total = calcSCC_dfs();
	if (SCC.size() > 0)
	{
		SCC.clear();
	}
	SCC.resize(total);
	for (int i = 0; i < (int)Adj.size(); i++)
	{
		for (int j = 0; j < (int)Adj[i].size(); j++)
		{
			int v = Adj[i][j];
			int new_source = sc_components[i];
			int new_target = sc_components[v];

			if (new_source != new_target)
				SCC[new_source].push_back(new_target);
		}
	}

} //buildSCC

//Topological Sort
int Graph::calcSCC_dfs()
{

	for (int i = 0; i < size; i++)
	{
		parents[i] = i;
		colors[i] = 'W';
	}
	int t = 0;
	int cc = 0;
	for (int i = 0; i < size; i++)
	{
		int v = topOrder[i];
		if (colors[v] == 'W')
		{
			calcSCC_dfsVisit(v, t, cc);
			cc++;
		} //if
	}	  //for
	return cc;
} //dfs

void Graph::calcSCC_dfsVisit(int u, int &t, int &cc)
{
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	sc_components[u] = cc;
	for (int i = 0; i < (int)transpose[u].size(); i++)
	{
		int v = transpose[u][i];
		if (colors[v] == 'W')
		{
			parents[v] = u;
			colors[v] = 'G';
			calcSCC_dfsVisit(v, t, cc);
		}
	} //for
	colors[u] = 'B';
	stamps[u].f = t;

	t++;
} //topSort_dfsVisit

void Graph::printSCC()
{
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
/************* End of Directed Graph **************/

int Graph::countPaths()
{
	topSort();

	vector<int> C(size, 0);
	C[topOrder[0]] = 1;
	for (size_t i = 0; i < topOrder.size(); i++)
	{
		int cNode = topOrder[i];
		for (size_t j = 0; j < Adj[cNode].size(); j++)
		{
			int node = Adj[cNode][j];
			C[node] += C[cNode];
		}
	}

	for (size_t i = 0; i < C.size(); i++)
	{
		cout << i << " " << C[i] << endl;
	}

	return topOrder[0];
}

int main()
{

	Graph ag; //directed graph

	string command;
	while (cin >> command)
	{
		if (command == "bfs")
		{
			int s;
			cin >> s;
			cout << "Running BFS on " << s << endl;
			ag.bfs(s);
			cout << "Parents array: " << endl;
			ag.printParents();
			cout << "Distance array: " << endl;
			ag.printDistance();
		}
		else if (command == "dfs")
		{
			cout << "Running DFS" << endl;
			ag.dfs();
			cout << "Parents array: " << endl;
			ag.printParents();
		}
		else if (command == "printGraph")
		{
			cout << "Adjacency lists of the graph are:" << endl;
			ag.printGraph();
		}
		else if (command == "topSort")
		{
			cout << "Running topological sort." << endl;
			ag.topSort();
			cout << "Vertices in topological order:" << endl;
			ag.printTopOrder();
		}
		else if (command == "buildTranspose")
		{
			cout << "Building transpose." << endl;
			ag.buildTranspose();
			cout << "Transpose:" << endl;
			ag.printTranspose();
		}
		else if (command == "buildSCC")
		{
			cout << "Building SCC graph." << endl;
			ag.buildSCC();
			cout << "SCC graph:" << endl;
			ag.printSCC();
		}
		else if (command == "countPaths")
		{
			cout << "Total number of distinct paths from each vertex:" << endl;
			int s = ag.countPaths();
			cout << "The source of the graph is " << s << endl;
		}
		else
		{
			cerr << "ERROR: the command " << command << " is not found." << endl;
		}
	} //while
	return 0;
}
