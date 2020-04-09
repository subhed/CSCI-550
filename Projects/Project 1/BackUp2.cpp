#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <list>
#include <queue>
#include <climits>
#include <limits>
#include <cstdint>
#include <algorithm>
#include <iterator>

using namespace std;

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
    Graph(int N)
    {
        Adj.resize(N);
        size = N;

        distance.resize(size);
        parents.resize(size);
        colors.resize(size);
    }
    void bfs(int s, vector<list<edge> > bfsAdj);
    // void dfs();
    // void dfsVisit(int u, int &t);
    void printGraph(vector<list<edge> > A1);
    void addEdge(int u, int v, int weight, int ou, int ov);
    void MBST(vector<list<edge> > adjA);
    void buildMBST();
    int connected(vector<list<edge> > adjB, vector<short> &cc);

private:
    vector<list<edge> > Adj; //adjacency lists of the graph
    vector<int> distance;   //for BFS and DFS
    vector<int> parents;    //for BFS and DFS
    vector<char> colors;    //for DFS

    int size;
};

void Graph::bfs(int s, vector<list<edge> > bfsAdj)
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
        if (bfsAdj[u].size() > 0)
            {
        for (std::list<edge>::iterator it = bfsAdj[u].begin(); it != bfsAdj[u].end(); ++it)
        {
            int v = it->neighbor;
            if (distance[v] == INT_MAX)
            {
                distance[v] = distance[u] + 1;
                parents[v] = u;
                aq.push(v);
            }
        }
            }

    } //while

} //bfs

void Graph::addEdge(int u, int v, int weight, int ou, int ov)
{
    Adj[u].push_back(edge(v, weight, u, ou, ov));
    Adj[v].push_back(edge(u, weight, v, ou, ov));
}

// void Graph::printGraph(vector<list<edge> > A1)
// {

//     for (int i = 0; i < A1.size(); i++)
//     {
//         for (std::list<edge>::iterator it = A1[i].begin(); it != A1[i].end(); ++it)
//             std::cout << i << " -> " << it->neighbor << " ," << it->u_orig << " -> " << it->v_orig << " ," << it->w << endl;
//     }

// } //printGraph

int select(vector<int> &v, int start, int fin, int k)
{

    int vsize = fin - start + 1;

    if (start == fin)
        return v[start];
    else if (start > fin)
        return -1;

    if (vsize <= 5)
    {
        sort(v.begin() + start, v.begin() + fin + 1);

        return v[k];
    }

    int msize = ceil((double)vsize / 5);

    vector<int> medians(msize, 0);
    int med_ind = 0;
    for (int i = start; i <= fin; i = i + 5)
    {
        vector<int> temp(5, 0);
        int j = 0;
        for (; j < 5 && (i + j) <= fin; j++)
        {
            temp[j] = v[i + j];
        } //for j
        if (j < 5)
            temp.resize(j);
        sort(temp.begin(), temp.end());
        if (j == 5)
            medians[med_ind++] = temp[2];
        else
        {
            int jmid = j >> 1; //divide by 2
            if (j % 2 == 0)
                jmid--;
            medians[med_ind++] = temp[jmid];
        }
    } //for i
    //so far we selected medians of n/5 groups of 5 elem
    int mid = msize >> 1; //divide by 2
    if ((msize % 2) == 0)
        mid--;
    int x = select(medians, 0, msize - 1, mid);
    //partition v's elements around x
    //find x
    int indx = -1;
    for (int i = start; i <= fin; i++)
    {
        if (v[i] == x)
        {
            indx = i;
            break;
        }
    } //for i
    if (indx == -1)
        return -2;
    int t = v[start];
    v[start] = x;
    v[indx] = t;
    int i = start + 1, j = fin;
    while (i < j)
    {
        if (v[i] > x && v[j] <= x)
        {
            t = v[j];
            v[j] = v[i];
            v[i] = t;
            i++;
            j--;
        } //if
        else if (v[i] <= x)
        {
            i++;
            if (i > fin)
            {
                i--;
                break;
            }
        }
        else
        {
            j--;
            if (j == 0)
            {
                j++;
                break;
            }
        }
    } //while partition
    int last = i;
    if (v[i] > x)
        last--; //last index that has less than or equal elemenents than x
                //count how many elements are equal to x
    int count_equal = 0;
    for (int u = start; u <= last; u++)
    {
        if (v[u] == x)
            count_equal++;
    } //for u

    if (k > (last - count_equal) && k <= last)
        return x;
    else if (last < k)
        return select(v, last + 1, fin, k);
    else
        return select(v, start, last, k);
} //select

void collect_weights(vector<list<edge> > adjA, vector<int> &weights)
{
    weights.clear();

    for (int i = 0; i < adjA.size(); i++)
    {

        if(adjA[i].size()>0){

        
        for (std::list<edge>::iterator it = adjA[i].begin(); it != adjA[i].end(); ++it)
            if (it->w != 0 || it->w > 0)
            {
                weights.push_back(it->w);
            }
        }
    }
}

void select_smallest(vector<list<edge> > &adjA, vector<list<edge> > &adjB, int median_weight)
{

    for (int i = 0; i < adjA.size(); i++)
    {
        if(adjA[i].size()>0){
        for (std::list<edge>::iterator it = adjA[i].begin(); it != adjA[i].end(); ++it)

            if (it->w <= median_weight)
            {
                adjB[i].push_back(*it);
                adjA[i].erase(it);
            }
        }
    }
}

int Graph::connected(vector<list<edge> > adjB, vector<short> &cc)
{

    int countCC = -1;

    for (int i = 0; i < cc.size(); i++)
    {

        if (cc[i] == -1)
        {
            countCC = countCC + 1;
            // cout<<"In: "<<i<<endl;

            bfs(i, adjB);

            for (int i = 0; i < distance.size(); i++)
            {
                if (distance[i] != INT_MAX && cc[i] == -1)
                {
                    cc[i] = countCC;
                }
            }
        }
    }

    return countCC + 1;
}

void Graph::buildMBST()
{

    MBST(Adj);
    return;
}

void Graph::MBST(vector<list<edge> > adjA)
{
    int m = 0;
    int size = adjA.size();

    for (int i = 0; i < size; i++)
    {
        m += adjA[i].size();
    }

    if (m == 2)
    {
        cout << adjA[0].front().u_orig << " " << adjA[0].front().v_orig << " " << adjA[0].front().w << endl;
        return;
    }

    vector<int> weights(m, 0);

    collect_weights(adjA, weights);

    int k = m >> 1; //divide by 2
    if (m % 2 == 0)
        k--;

    int median_weight = select(weights, 0, m - 1, k);

    vector<list<edge> > adjB(adjA.size()); //smallest edges Initialize

    select_smallest(adjA, adjB, median_weight);

    vector<short int> cc(adjB.size(), -1);
    int total_cc = connected(adjB, cc); //number of comp is returned

    if (total_cc == 1)
    {
        MBST(adjB);
        return;
    }
    else
    {

        vector<list<edge> > adjC;
        adjC.resize(total_cc);

        for (int i = 0; i < adjB.size(); i++)
        {
            if (adjA[i].size() > 0)
            {
                for (std::list<edge>::iterator it = adjA[i].begin(); it != adjA[i].end(); ++it)
                {

                    if (cc[i] != cc[it->neighbor])
                    {
                        adjC[cc[i]].push_back(edge(cc[it->neighbor], it->w, cc[i], it->u_orig, it->v_orig));
                    }
                }
            }
        }

        MBST(adjC);

        return;
    } //else not connected
} //MBST recursive

int main()
{

    int M, N;

    cin >> M >> N;

    Graph ag(M);

    for (int i = 0; i < N; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        ag.addEdge(u, v, w, u, v);
    }

    ag.buildMBST();

    return 0;
}