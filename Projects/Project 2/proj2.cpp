#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isPalindrome(string S)
{

    int size = S.length();
    vector<vector<int>> P(S.length());

    for (size_t i = 0; i < size; i++)
    {
        P[i].resize(size);
        P[i][i] = 1;
    }

    int count = 0;
    int s_count = size;
    int x = 1;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < s_count - 1; j++)
        {

            if (S[j] == S[j + x])
            {
                P[j][j + x] = 1;
            }
            // else if (P[j + 1][j + x - 1] == 1 && S[j] == S[j + x])
            // {
            //     P[j][j + x] = 1;
            // }
            // else
            // {
            //     P[j][j + x] = 0;
            // }

            // cout<< j << " "<<j+x;
            // cout<<endl;
        }
        s_count--;
        x++;

        // cout << endl;
    }

    // for (size_t i = 0; i < size; i++)
    // {
    //     for (size_t j = 0; j < size; j++)
    //     {
    //         cout << P[i][j] << " ";
    //     }

    //     cout << endl;
    // }

    if (P[0][size-1] == 1)
    {
        return true;
    }

    return false;
}

void P_Cuts(string S){

    int size = S.length();

    vector<int> C(size);
    vector<int> B(size);

    C[0] = 0;
    B[0] = -1;

    for (size_t i = 1; i < size; i++)
    {
        int trim = 0;
        string SC = S;
        
        SC.substr(0, i);
        
        cout<<SC;

        // for (size_t j = 0; j <= i; j++)
        // {
        //     SC.erase(0, 1);
        //     cout<<SC;
        //     trim++;
        //     cout<<endl;
        // }
        cout<<endl;
        
    }
    

}

int main()
{
    string S;
    cin >> S;

    P_Cuts(S);

    return 0;
}