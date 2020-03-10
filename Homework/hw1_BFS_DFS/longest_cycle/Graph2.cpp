#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "graph.h"

Graph::Graph(int N){

	size = N;
	
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

}//default

void Graph::addEdge(int u, int v){
	Adj[u].push_back(edge(v, 0));
}
void Graph::addEdge(int u, int v, int weight){
	Adj[u].push_back(edge(v, weight));

}

void Graph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			cout << v << " " ;
		}//for j
		cout << endl;
	}
}//printGraph

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
			int v = Adj[u][i].neighbor;
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
			//color[i] = 'G';
			dfsVisit(i, t);
		}//if
	}//for

}//dfs

void Graph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[u] = v;
				colors[v] = 'G';
				dfsVisit(v, t);
			}
			if(colors[v] == 'G'){
				if(stamps[v].d==1){
					if(distance[u]==-1){
						distance[u]=1;
						parents[u]= v;
					}
				}
				else if(stamps[v].d!=1)
				{
					distance[u]=-1;
				}
				
				colors[u] = 'B';
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	for (size_t i = 0; i < Adj[u].size(); i++)
	{
		if((distance[Adj[u][i].neighbor]+1)	> distance[u] && (colors[Adj[u][i].neighbor] == 'B' ||  colors[Adj[u][i].neighbor] == 'G')){
			
			if((distance[Adj[u][i].neighbor]+1) == 0){
				distance[u]=1;
				parents[u] = 0;
			}
			else{
				distance[u]=distance[Adj[u][i].neighbor]+1;
				parents[u] = Adj[u][i].neighbor;

				if(distance[u] > tMax){
					tMax = distance[u];
					tSource = u;
				}

			}
		}
	}
	t++;
}//dfsVisit	


int Graph::longestCycle(){

	tSource = -1;
	tMax= -1;

	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
		distance[i] = -1;
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//color[i] = 'G';

			dfsVisit(i, t);
		
		}//if
	}//for

	cout<<"0 ";

	int child=0;
	
	for (size_t i = 0; i < tMax; i++)
	{
		cout<<parents[child]<<" ";
		child = parents[child];
	}
	
	
	
	
	cout<<endl;
	
	return tMax;	
}
