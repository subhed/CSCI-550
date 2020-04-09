#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isPalindrome(string S)
{
    int size = S.length();
    vector<vector<int> > P(S.length());

    for (size_t i = 0; i < size; i++)
    {
        P[i].resize(size);
        P[i][i] = 1;
    }

    for (int i = 0; i < size - 1; ++i)
    {
        if (S[i] == S[i + 1])
        {
            P[i][i + 1] = 1;
        }
    }

    for (int k = 3; k <= size; ++k)
    {
        for (int i = 0; i < size - k + 1; ++i)
        {
            int j = i + k - 1;
            if (P[i + 1][j - 1] && S[i] == S[j])
            {
                P[i][j] = 1;
            }
        }
    }

    if (P[0][size - 1] == 1)
    {
        return true;
    }

    return false;
}

void printPalindrome(int x, string S, vector<int> B)
{

    if (B[x] != -1)
    {
        printPalindrome(B[x], S, B);
    }
    cout << S.substr(B[x] + 1, (x - B[x]));
    cout << endl;
}

void P_Cuts(string S)
{

    int size = S.length();

    vector<int> C(size, 999);
    vector<int> B(size);

    C[0] = 0;
    B[0] = -1;

    for (size_t i = 1; i < size; i++)
    {

        string SC = S;

        SC = SC.substr(0, i + 1);

        for (size_t j = 0; j <= i; j++)
        {

            if (isPalindrome(SC) == true)
            {

                if (j - 1 == -1)
                {
                    C[i] = 0;
                    B[i] = -1;
                }
                else
                {
                    if (C[i] > C[j - 1] + 1)
                    {
                        C[i] = C[j - 1] + 1;
                        B[i] = j - 1;
                    }
                }
            }

            SC = SC.substr(1);
        }
    }

    printPalindrome(size - 1, S, B);
}

int main()
{
    string S;
    cin >> S;

    P_Cuts(S);
    // cout<<isPalindrome(S);

    return 0;
}