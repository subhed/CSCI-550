#include <iostream>
#include <vector>
#include <math.h>
#include<string>
#include<list>
#include<queue>
#include <climits>
#include <limits>
#include <cstdint>
#include<algorithm>

using namespace std;

/*************** EDGE STRUCTURE & FUNCTIONS ********************/

struct edge
{
    int neighbor; // adjacent node
    int w;        //keeps auxiliary information
    int v_orig;
    int u_orig;

    edge()
    {
        neighbor = 0;
        w = 0;
        v_orig = 0;
        u_orig = 0;
    };
    edge(int i, int j, int k, int ou, int ov)
    {
        neighbor = i;
        w = j;
        u_orig = ou;
        v_orig = ov;
    };
};

// Edge Structure for node
class Graph
{
public:
    Graph(int N){
        Adj.resize(N);
        size = N;

        distance.resize(size);
        parents.resize(size);
        colors.resize(size);
    }
    void bfs(int s, vector< list<edge> > bfsAdj);
    // void dfs();
    // void dfsVisit(int u, int &t);
    void printGraph(vector< list<edge> > A1);
    void addEdge(int u, int v, int weight, int ou, int ov);
    void MBST( vector<list<edge> > &adjA);
    void buildMBST();
    int connected(vector<list<edge> > adjB, vector<short> &cc);



private:
    vector<list<edge> > Adj; //adjacency lists of the graph
    vector<int> distance;     //for BFS and DFS
    vector<int> parents;      //for BFS and DFS
    vector<char> colors;      //for DFS
    
    int size;
};



void Graph::bfs(int s, vector< list<edge> > bfsAdj){
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

        for (std::list<edge>::iterator it=bfsAdj[u].begin(); it != bfsAdj[u].end(); ++it)
		{
            int v = it->neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
        }
		
	}//while

}//bfs

void Graph::addEdge(int u, int v, int weight, int ou, int ov)
{
    Adj[u].push_back(edge(v, weight, u, ou, ov));
    Adj[v].push_back(edge(u, weight, v, ou, ov));
}

void Graph::printGraph(vector< list<edge> > A1){
	
    for (size_t i = 0; i < A1.size(); i++)
    {
          for (std::list<edge>::iterator it=A1[i].begin(); it != A1[i].end(); ++it)
             std::cout << i << " -> " << it->neighbor << " ," << it->u_orig << " -> " << it->v_orig << " ," << it->w <<endl;
    }
  
}//printGraph



//This function is called inside "mbst" function
//vector v contains all weights of edges in the graph
//start and fin are the starting and ending indices in v (inclusive: 0, and (v.size()-1))
//int k is the index of the median (calculated in mbst)
int select(vector<int> &v, int start, int fin, int k){

    int vsize = fin - start + 1;

    if(start == fin)
        return v[start];
    else if(start > fin)
        return -1;
	
	if(vsize <= 5){
		sort(v.begin() + start, v.begin() + fin + 1);

		return v[k];
	}
	
	int msize = ceil((double)vsize/5);

    vector<int> medians(msize, 0);
    int med_ind = 0;
    for(int i = start; i <= fin; i = i + 5){
        vector<int> temp(5, 0);
        int j = 0;
        for(; j < 5 && (i + j)<= fin; j++){
            temp[j] = v[i+j];
        }//for j
        if(j < 5)
            temp.resize(j);
        sort(temp.begin(), temp.end());
        if(j == 5)
            medians[med_ind++] = temp[2];
        else{
            int jmid = j >> 1;//divide by 2
            if(j % 2 == 0)
                jmid--;
            medians[med_ind++] = temp[jmid];

            }
    }//for i
    //so far we selected medians of n/5 groups of 5 elem
    int mid = msize >> 1; //divide by 2
    if((msize % 2) == 0)
        mid--;
    int x = select(medians, 0, msize - 1, mid);
    //partition v's elements around x
    //find x
    int indx = -1;
    for(int i = start; i <= fin; i++){
        if(v[i] == x){
            indx = i;
            break;
            }
    }//for i
    if(indx == -1)
        return -2;
    int t = v[start];
    v[start] = x;
    v[indx] = t;
    int i = start + 1, j = fin;
    while(i < j){
        if(v[i] > x && v[j] <= x){
            t = v[j];
            v[j] = v[i];
            v[i] = t;
            i++;
            j--;
        }//if
        else if(v[i] <= x){
            i++;
            if(i > fin){
                i--;
                break;
            }
            }
        else{
            j--;
            if(j == 0){
                j++;
                break;
            }
            }
    }//while partition
    int last = i;
    if(v[i] > x)
        last--;//last index that has less than or equal elemenents than x
//count how many elements are equal to x
    int count_equal = 0;	
    for(int u = start; u <= last; u++){
        if(v[u] == x)
            count_equal++;
    }//for u
    
    if(k > (last - count_equal) && k <= last)
        return x;
    else if(last < k)
        return select(v, last + 1, fin, k);
    else
        return select(v, start, last, k);
}//select





void collect_weights(vector<list<edge> > adjA, vector<int> &weights)
{
    weights.clear();
    
    for (size_t i = 0; i < adjA.size(); i++)
    {
       
              for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it)
                   if(it->w!=0 || it->w>0){
                        weights.push_back(it->w);    
                   }
        
    }
    
}

void select_smallest(vector<list<edge> > &adjA, vector<list<edge> > &adjB, int median_weight){
    
    
   for (size_t i = 0; i < adjA.size(); i++)
    {
          for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it)

                if(it->w <= median_weight){
                    adjB[i].push_back(*it);
                    adjA[i].erase(it);
                }
    }
    

}


int Graph::connected(vector<list<edge> > adjB, vector<short> &cc){



    int countCC = -1;

 
    for (size_t i = 0; i < cc.size(); i++)
    {
    
        
        if(cc[i]==-1){
            countCC = countCC+1;
            // cout<<"In: "<<i<<endl;
        
        bfs(i, adjB);

        for (size_t i = 0; i < distance.size(); i++)
        {
            if(distance[i]!=INT_MAX && cc[i]==-1){
                cc[i] = countCC;
            }
        }

        }


    }

  

    // for (size_t i = 0; i < cc.size(); i++)
    // {
    //     cout<<cc[i]<<" ";
    // }
    

    return countCC+1; 
}


void Graph::buildMBST(){

    MBST(Adj);
}
/*********************************************
1. Initially, in adjA's vector is indexed by vertices of
original graph, and for each edge (u, v),
adjA[u] has v
adjA[v] has u

2. At each recursive call adjA will be different 
(see parameters passed in the recursive calls below)

3. Once you reach the termination condition, print out 
the required output and return

4. Do not do anything after recursive call
***********************************************/
void Graph::MBST( vector<list<edge> > &adjA){


        //Count the number of edges in adjA
        int m = 0;
        int size = adjA.size();

        for(int i = 0; i < size; i++){
                m += adjA[i].size();
        }   

        
        // m = m >> 1;//divide by 2, each edge occurs twice in Adj

        //termination case, if the number of edges is 1, print out the output and return
        if(m == 2){

			//print out the output
            cout<< adjA[0].front().u_orig<<" "<<adjA[0].front().v_orig<<" "<<adjA[0].front().w<<endl;
            return;
        }

        /***********   Collect weights of edges **********/
        vector<int> weights(m, 0);
        //You need to write this function:
		//We need to add only one weight for each edge (u, v)
		//Since each edge occurs in adjA twice, use this condition to add the weight only once:
		//if u < v, then add weight
        collect_weights(adjA, weights);



        /*******   Find the median of weights *********/
        int k = m >> 1;//divide by 2
        if(m % 2 == 0)
                k--;
        
        // cout<<endl<< m<<endl<<endl; 

        int median_weight = select(weights, 0, m-1,k);

        //Function "select" is provided above

        // cout<<endl<<"Median: "<< median_weight<<endl;

        
        /*****  Collect edges with weights <= median_weight
                from adjA into adjB
                Erase an edge from adjA:
                it takes O(1) to erase (use erase) from
                a list
        *************************************************/
        vector< list<edge> > adjB(adjA.size());//smallest edges Initialize

        //You need to write this function
		//when adding the smallest half edges to adjB, erase them from adjA:
        select_smallest(adjA, adjB, median_weight);

        // printGraph(adjA);

        // cout<<endl;

        // printGraph(adjB);


        /******* Find connected components in adjB 
                in linear time 
         ***************************************/
        
        vector<short int> cc(adjB.size(), -1);
        int total_cc = connected(adjB, cc);//number of comp is returned



        /**********     If connected (only one component)
                we don't need edges of A anymore
                just call recursively MBST and return 
                after the recursive call returns 
                i.e. do nothing after recursive call returns
        ****************************************/

        if(total_cc == 1){
                MBST(adjB);
                return;
        }else{ //If not connected

            /******   You need to find a function that  
				constructs adjC (a new graph)
                with contracted connected components
                Construct adjC:
				each vertex of C corresponds to a single connected component of adjB,
				add each edge from adjA if this edge is between different connected components.

                Rename edges of adjC according to the names
                of their new vertices (connected components) as 0, 1,.., total_cc-1.
			**************************************************/



				//call recursively MBST on adjC: 

                // cout<<endl;


                vector<list<edge> > adjC(total_cc);

                for (size_t i = 0; i < adjB.size(); i++)
                {
                    for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it)
                        {
                            
                            // cout<< "[ "<< i<<" ]"<<cc[i] <<" | "<<  "[ "<< it->neighbor <<" ]"<<cc[it->neighbor]<<endl;

                            if(cc[i] != cc[it->neighbor]){
                                // adjC[cc[i]].push_back(edge(cc[it->neighbor], it->w, cc[i],  it->u_orig, it->v_orig));
                                // cout<<cc[i]<<" | "<<cc[it->neighbor]<<" "<<it->w<<endl;
                                adjC[cc[i]].push_back(edge(cc[it->neighbor], it->w, cc[i], it->u_orig, it->v_orig));
                            }
                        }
                }
                
                // cout<<adjC.size();
                // printGraph(adjC);


				 MBST(adjC);
                




           /*** In original Camerini's algorithm, at this place of the program,
				we would add edges from adjB (use original names)
                into the resulting graph MBST, but
				in this project we don't need to do anything here.
            *****************************************/ 

                return;
        }//else not connected
}//MBST recursive



int main()
{

    int M, N;

    cin >> M >> N;

    Graph ag(M);
    

    for (size_t i = 0; i < N; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        ag.addEdge(u, v, w, u, v);
    }

    ag.buildMBST();


    return 0;
}