#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
#include <stack> 

using namespace std;

#ifndef TIMESTAMP_H
#define TIMESTAMP_H
class TimeStamp{
public:
	TimeStamp(): d(0), f(0){};
	int d; //discovery time
	int f; //finish time

};

#endif

/********** Directed Graph ************/

#ifndef GRAPH_H
#define GRAPH_H

class Graph{
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
	bool reachable(int u, int v);
	bool isCycle();

private:
	vector< vector<int> > Adj; //adjacency lists of the graph 
	vector< int > distance; //for BFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS
    int size;//total vertices in the graph

	unsigned cycleC;

	friend class Ugraph;
};

#endif

Graph::Graph(){
	cin >> size;
	
	int u, v;
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

	for(int i = 0; i < size; i++){
		cin >> u >> v;
		Adj[u].push_back(v);
	}//for

	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
		colors[i] = 'W';
	}
}//default

void Graph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();
        
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i];
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	
}//bfs

void Graph::dfs(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			dfsVisit(i, t);
		}//if
	}//for

}//dfs


void Graph::dfsVisit(int u, int &t){
	

	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i];
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisit(v, t);
			}
			if(colors[v]=='G'){
				cycleC++;
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	



void Graph::printGraph(){

        //format: 
        //vertex: list of neighbors
        for(int u = 0; u < size; u++){
            cout << u << ": ";
            for(int j = 0; j < (int)Adj[u].size(); j++){
                int v = Adj[u][j]; //v is a neighbor
                cout << v << " ";
            }
            cout << endl;
        }
}

void Graph::printParents(){
	for(int i = 0; i < size; i++){
		cout << parents[i] << " " ;
	}
	cout << endl;
}

void Graph::printDistance(){
	for(int i = 0; i < size; i++){
		cout << distance[i] << " " ;
	}
	cout << endl;
}

bool Graph::reachable(int u, int v){
	bfs(u);
	if(distance[v] != INT_MAX){
		return true;
	}
	else
	{
		return false;
	}
	
	return true;//change this dummy code
}//reachable

bool Graph::isCycle(){

	cycleC=0;
	dfs();

	if(cycleC>0){
		return true;
	}
	
	return false;//change this dummy code

}//isCycle
/************* End of Directed Graph **************/

/************ Undirected Graph *************/


#ifndef UGRAPH_H
#define UGRAPH_H

class Ugraph{
public:
	Ugraph();
	Ugraph(const Graph &ag);

    void printGraph();

	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);

    void diaPrint(int x, int y);

    
	void printParents();
	void printDistance();

    void DisFromCore();
    void getPar(int y);

	//write these functions
	bool connected();

private:
	vector< vector<int> > Adj; //adjacency lists of the graph 
	vector< int > distance; //for BFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS
    stack<int> final;
    int size;//total vertices in the graph
};

#endif

//constructor copies Adj from a directed graph
Ugraph::Ugraph(const Graph &ag){
	size = ag.size;
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

	//add edges: for each edge (u, v) add edge (v, u)
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)ag.Adj[i].size(); j++){
			int u = i;
			int v = ag.Adj[i][j];
			Adj[u].push_back(v);
			Adj[v].push_back(u);
		}
	}//for i
}//constructor copies Adj from directed graph

//constructor that reads Adj from standard input
Ugraph::Ugraph(){
	cin >> size;
	int m;
	cin >> m;
	int u, v;
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

	for(int i = 0; i < m; i++){
		cin >> u >> v;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}//for

	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
		colors[i] = 'W';
		
	}
}//default

void Ugraph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();
        
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i];
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	
}//bfs

void Ugraph::dfs(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			dfsVisit(i, t);
		}//if
	}//for

}//dfs

void Ugraph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i];
            if(v == 12){
                break;
            }
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisit(v, t);
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	


void Ugraph::diaPrint(int x, int y){

    if (x == y)
    {
        return;
    }
    int para = parents[x];
    final.push(para);
    diaPrint(para, y);
}




void Ugraph::DisFromCore(){
    
    int rand = 0;

    vector< vector<int> > AdjB = Adj; //adjacency lists of the graph 
    vector<int> parentsB = parents; //for BFS and DFS

    bfs(rand);

    // printDistance();
    // cout<<endl<<"Max1 "<< *max_element(distance.begin(), distance.end())<<endl;
    // cout<<endl<<"Max1_Index: "<< max_element(distance.begin(),distance.end()) - distance.begin()<<endl;

    int max1 = max_element(distance.begin(),distance.end()) - distance.begin();
    Adj = AdjB;
    parents = parentsB;
     
    bfs(max1);

    max1 =  max_element(distance.begin(),distance.end()) - distance.begin();
    int l = *max_element(distance.begin(),distance.end());
    int r = (l / 2);
    int par = parents[max1];

    for (int i = 1; i < r; i++)
    {
        par = parents[par];
    }


    bfs(par);

    for (int i = 0; i < size; i++)
    {
        if(i!=par){
        diaPrint(i, par);

            while(!final.empty())
            {
                cout<<final.top()<<" ";
                final.pop();
            }
            cout<< i <<" ";
        
        }
        else
        {
            continue;
        }
        
        cout<<endl;
    }
    
    


    
}

void Ugraph::printGraph(){

        //format: 
        //vertex: list of neighbors
        for(int u = 0; u < size; u++){
            cout << u << ": ";
            for(int j = 0; j < (int)Adj[u].size(); j++){
                int v = Adj[u][j]; //v is a neighbor
                cout << v << " ";
            }
            cout << endl;
        }
}
void Ugraph::printParents(){
	for(int i = 0; i < size; i++){
		cout << parents[i] << " " ;
	}
	cout << endl;
}

void Ugraph::printDistance(){
	for(int i = 0; i < size; i++){
		cout << distance[i] << " " ;
	}
	cout << endl;
}

bool Ugraph::connected(){
	if(size==0)
		return true;
	else
	{
		bfs(0);
		for (size_t i = 0; i < distance.size(); i++)
		{
			if(distance[i]==INT_MAX){
				return false;
			}
		}
		return true;
		
	}
	
	return true;//change this dummy code
}

/************* End of Undirected Graph **************/

int main(){

	Graph ag;//directed graph

	Ugraph ug(ag);//undirected graph
	

    ug.DisFromCore();

  return 0;
}
