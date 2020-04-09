#include <climits>
#include <algorithm>
#include <queue>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main()
{

    string aline;
    string T;

    while (getline(cin, aline))
    {
        T = T + aline;
    }

    vector<int> count(257, 0);

    for (int i = 0; i < (int)T.size(); i++)
    {
        count[T[i]] = 1;
    }

    int curName = 1;
    for (size_t i = 0; i < 257; i++)
    {
        if (count[i] == 1)
        {
            count[i] = curName++;
        }
    }

    // Vector Tint - Char Int Array

    vector<int> Tint;

    for (size_t i = 0; i < T.size(); i++)
    {
        Tint.push_back(count[T[i]]);
    }
    Tint.push_back(0);

    // for (size_t i = 0; i < Tint.size(); i++)
    // {
    //     cout << Tint[i] << " ";
    // }
    // cout << endl;

    // Vector t - Type Array

    vector<int> t(Tint.size());

    t[Tint.size() - 1] = 1;

    for (size_t i = Tint.size() - 2; i > 0; --i)
    {
        if (Tint[i] > Tint[i + 1])
        {
            t[i] = 0;
        }
        else if (Tint[i] == Tint[i + 1])
        {
            t[i] = t[i + 1];
        }
        else
        {
            t[i] = 1;
        }
    }

    // for (size_t i = 0; i < t.size(); i++)
    // {
    //     cout << t[i] << " ";
    // }
    // cout << endl;

    vector<int> lms(Tint.size());

    for (size_t i = Tint.size() - 1; i > 0; --i)
    {
        if (t[i] > t[i - 1])
        {
            lms[i] = 1;
        }
        else
        {
            lms[i] = 0;
        }
    }

    // for (size_t i = 0; i < lms.size(); i++)
    // {
    //     cout <<lms[i] << " ";
    // }
    // cout << endl;

    // Max Element in Array

    int maxi = *max_element(Tint.begin(), Tint.end());
    // cout << maxi;
    // cout << endl;

    // Vector A

    vector<int> A(maxi + 1, 0);

    for (size_t i = 0; i < Tint.size(); i++)
    {
        A[Tint[i]] = A[Tint[i]] + 1;
    }

    // for (size_t i = 0; i < A.size(); i++)
    // {
    //     cout << A[i] << " ";
    // }
    // cout << endl;

    // Vector C
    vector<int> BC(maxi + 1, 0);
    vector<int> BE(maxi + 1, 0);

    vector<int> C(maxi + 1, 0);
    C[0] = 0;

    for (size_t i = 1; i < Tint.size(); i++)
    {
        C[i] = C[i - 1] + A[i - 1];
    }

    // for (size_t i = 0; i < C.size(); i++)
    // {
    //     cout << C[i] << " ";
    // }
    // cout << endl;

    // Vector End

    vector<int> End(maxi + 1, 0);
    End[C.size() - 1] = T.size();

    for (size_t i = C.size() - 1; i > 0; --i)
    {
        End[i - 1] = C[i] - 1;
    }

    // for (size_t i = 0; i < C.size(); i++)
    // {
    //     cout << End[i] << " ";
    // }
    // cout << endl;

    BC = C;
    BE = End;

    vector<int> SA(Tint.size(), -1);
    
    for (size_t i = lms.size()-1; i > 0; --i)
    {
        if(lms[i]==1){
            SA[End[Tint[i]]] = i;
            End[Tint[i]] = End[Tint[i]] - 1; 
        }
    }


    for (size_t i = 0; i < SA.size(); i++)
    {
        if(SA[i]==-1){
            continue;
        }
        else if(SA[i]==0){
            continue;
        }
        else
        {
            int x = SA[i] - 1;

            if(t[x] == 0){
                SA[C[Tint[x]]] = x;
                C[Tint[x]] = C[Tint[x]]+1;
            }

        }
        
    }
 

    

    for (unsigned i = SA.size(); i-- > 0; )
    {
         if(SA[i]==-1){
            continue;
        }
        if(SA[i]==0){
            continue;
        }
        else
        {

        int x = SA[i]-1;

        if(t[x]==1){
            SA[BE[Tint[x]]] = x;
            BE[Tint[x]] = BE[Tint[x]] - 1;
        }

        }
        
       
    }


    for (size_t i = 0; i < SA.size(); i++)
    {
        cout<< SA[i]<<" ";
    }
    cout<<endl;    



    return 0;
}