#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<cmath>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "graph.h"

int main(){
	int N;
	cin >> N;

    Graph ag(N);
	string command;
	while(cin >> command){
		if(command == "addEdge"){
			int u, v;
			cin >> u >> v;
			cin.ignore();
			ag.addEdge(u, v);
		}else if(command == "printGraph"){
			ag.printGraph();
		}
        else if(command == "longestCycleSCC"){
			cout << "The longest cycle in the SCC graph is: " << endl;
			int L = ag.longestCycle();
			cout << "The length of the longest cycle is " << L << endl;
			
		}
        else{
			cerr << "ERROR: command " << command << " is not recognized." << endl;
		}
	}//while
  
  return 0;
}
