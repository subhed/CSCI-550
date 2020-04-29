#include <climits>
#include <algorithm>
#include <queue>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

bool compareLMS(int F, int S, vector<int> &T, vector<int> &t)
{

    int p1 = -1;
    int p2 = -1;

    int pt1 = F, pt2 = S;

    // cout << "\n F:" << F << " S:" << S << " ";

    // cout<<"\n"<< p1<<" --> "<<t[pt1]<<"\n";

    while ((p1 != 0 || t[pt1] != 1) && (p2 != 0 || t[pt2] != 1) && pt1 < T.size() && pt2 < T.size())
    {
        // cout << T[pt1] << "==" << T[pt2] << "\n";

        if (T[pt1] != T[pt2] || t[pt1] != t[pt2])
        {
            return false;
        }

        p1 = t[pt1];
        pt1 = pt1 + 1;
        p2 = t[pt2];
        pt2 = pt2 + 1;
    }
    if (T[pt1] != T[pt2] || t[pt1] != t[pt2])
    {
        return false;
    }

    // cout << "Pt: " << pt1 << "\n";
    // cout << " Pt2: " << pt2 << "\n";

    return true;
}

/*********** SAIS ***********/

vector<int> SAIS(vector<int> &Tint, vector<int> &SA, int alphabetSize)
{

    cout << endl
         << endl
         << "Iteration" << endl;

    cout << "T at iteration :" << endl;
    for (size_t i = 0; i < Tint.size(); i++)
    {
        cout << Tint[i] << " ";
    }
    cout << endl;

    if (Tint.size() == alphabetSize)
    {

        for (size_t i = 0; i < Tint.size(); i++)
        {
            SA[Tint[i]] = i;
        }

        return SA;
    }

    vector<int> t(Tint.size());

    t[Tint.size() - 1] = 1;

    // for (size_t i = Tint.size() - 2; i > 0; --i)
    for (unsigned i = Tint.size() - 1; i-- > 0;)
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

    cout << "Type array:" << endl;
    for (size_t i = 0; i < t.size(); i++)
    {
        cout << t[i] << " ";
    }
    cout << endl;

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
    //     cout<<i<<" " <<lms[i]<<" \n";
    // }

    // cout<<endl;

    // Max Element in Array

    int maxi = *max_element(Tint.begin(), Tint.end());
    int size = maxi + 1;

    // cout<<maxi<<endl;

    // Vector A

    vector<int> A(size, 0);

    for (size_t i = 0; i < Tint.size(); i++)
    {
        A[Tint[i]] = A[Tint[i]] + 1;
    }

    // Vector C
    vector<int> BC(size);
    vector<int> BE(size);

    vector<int> C(size, 0);

    for (size_t i = 1; i < A.size(); i++)
    {
        C[i] = C[i - 1] + A[i - 1];
    }

    // Vector End

    vector<int> End(maxi + 1, 0);
    End[C.size() - 1] = Tint.size();

    for (size_t i = C.size() - 1; i > 0; --i)
    {
        End[i - 1] = C[i] - 1;
    }

    BC = C;
    BE = End;

    for (size_t i = lms.size() - 1; i > 0; --i)
    {
        if (lms[i] == 1)
        {
            SA[End[Tint[i]]] = i;
            End[Tint[i]] = End[Tint[i]] - 1;
        }
    }

    for (size_t i = 0; i < SA.size(); i++)
    {
        if (SA[i] == -1)
        {
            continue;
        }
        else if (SA[i] == 0)
        {
            continue;
        }
        else
        {
            int x = SA[i] - 1;

            if (t[x] == 0)
            {
                SA[C[Tint[x]]] = x;
                C[Tint[x]] = C[Tint[x]] + 1;
            }
        }
    }

    for (unsigned i = SA.size(); i-- > 0;)
    {
        if (SA[i] == -1)
        {
            continue;
        }
        if (SA[i] == 0)
        {
            continue;
        }
        else
        {

            int x = SA[i] - 1;

            if (t[x] == 1)
            {
                SA[BE[Tint[x]]] = x;
                BE[Tint[x]] = BE[Tint[x]] - 1;
            }
        }
    }

    cout << "SA at iteration :" << endl;
    for (size_t i = 0; i < SA.size(); i++)
    {
        cout << SA[i] << " ";
    }
    cout << endl;

    int prev = -1, name = -1;
    vector<int> N(Tint.size(), -1);

    for (size_t i = 0; i < SA.size(); i++)
    {
        if (lms[SA[i]] == 1)
        {
            // cout<< "SA:"<<SA[i]<<" PREV:"<<prev<<"\n";
            if (prev == -1)
            {
                name = name + 1;
                N[SA[i]] = name;
                prev = SA[i];
            }
            else
            {
                // cout<<compareLMS(prev, SA[i], Tint, t)<<"\n";
                if (compareLMS(prev, SA[i], Tint, t) == true)
                {
                    N[SA[i]] = name;
                }
                else
                {
                    name = name + 1;
                    N[SA[i]] = name;
                }

                prev = SA[i];
            }
        }
    }

    vector<int> T1;

    for (size_t i = 0; i < N.size(); i++)
    {
        if (N[i] != -1)
        {
            T1.push_back(N[i]);
        }
    }

    cout << "T1 at Iteration" << endl;
    for (size_t i = 0; i < T1.size(); i++)
    {
        cout << T1[i] << " ";
    }

    vector<int> SA1(T1.size(), -1);

    int largest = *max_element(T1.begin(), T1.end());

    SAIS(T1, SA1, largest + 1);

    cout << endl
         << "Before Return" << endl;

    // cout << "T1" << endl;
    // for (size_t i = 0; i < T1.size(); i++)
    // {
    //     cout << T1[i] << " ";
    // }

    cout << endl
         << "SA1" << endl;
    for (size_t i = 0; i < SA1.size(); i++)
    {
        cout << SA1[i] << " ";
    }

    cout << endl;

    cout << "SA" << endl;
    for (size_t i = 0; i < SA.size(); i++)
    {
        cout << SA[i] << " ";
    }

    int fxc = 0;
    for (size_t i = 0; i < lms.size(); i++)
    {
        if (lms[i] == 1)
        {
            T1[fxc] = i;
            fxc = fxc + 1;
        }
    }
    cout << endl;

    vector<int> AX(size, 0);
    vector<int> CX(size, 0);

    for (size_t i = 0; i < Tint.size(); i++)
    {
        AX[Tint[i]] = AX[Tint[i]] + 1;
    }

    for (size_t i = 1; i < AX.size(); i++)
    {
        CX[i] = CX[i - 1] + AX[i - 1];
    }

    vector<int> EX(maxi + 1, 0);
    EX[C.size() - 1] = Tint.size() - 1;

    for (size_t i = CX.size() - 1; i > 0; --i)
    {
        EX[i - 1] = CX[i] - 1;
    }

    vector<int> EXX = EX;

    cout << endl;

    vector<int> SAX(Tint.size(), -1);

    for (unsigned i = SA1.size(); i-- > 0;)
    {
        int p = T1[SA1[i]];
        // cout << "*" << p << "*";
        SAX[EX[Tint[p]]] = p;
        EX[Tint[p]] = EX[Tint[p]] - 1;
    }

    cout << endl;

    cout << "SAX" << endl;
    for (size_t i = 0; i < SAX.size(); i++)
    {
        cout << SAX[i] << " ";
    }

    cout << endl;

    cout << "SAX" << endl;

    for (size_t i = 0; i < SAX.size(); i++)
    {
        if (SAX[i] == -1)
        {
            continue;
        }
        if (SAX[i] == 0)
        {
            continue;
        }
        else
        {
            int x = SAX[i] - 1;
            // cout<<i<<" : "<<SAX[x]<<" -> "<<x<<"      ";
            if (t[x] == 0)
            {
                SAX[CX[Tint[x]]] = x;
                CX[Tint[x]] = CX[Tint[x]] + 1;
            }
        }
    }

    for (unsigned i = SAX.size(); i-- > 0;)
    {
        if (SAX[i] == -1)
        {
            continue;
        }
        if (SAX[i] == 0)
        {
            continue;
        }
        else
        {

            int x = SAX[i] - 1;

            if (t[x] == 1)
            {
                SAX[EXX[Tint[x]]] = x;
                EXX[Tint[x]] = EXX[Tint[x]] - 1;
            }
        }
    }

    cout << endl;

    // for (size_t i = 0; i < SAX.size(); i++)
    // {
    //   cout<<SAX[i]<<" ";
    // }

    return SAX;
}

/*********** MAIN ***********/
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

    vector<int> SA(Tint.size(), -1);

    int largest = *max_element(Tint.begin(), Tint.end());

    // cout<< Tint.size();
    // cout<<endl<<largest<<endl;

    cout << "Project 5 Begins" << endl
         << endl;

    vector<int> SAX = SAIS(Tint, SA, largest + 1);

    cout << endl
         << endl;

    cout << "After Recurssion" << endl;

    cout << "SA :" << endl;
    for (size_t i = 0; i < SAX.size(); i++)
    {
        cout << SAX[i] << " ";
    }
    cout << endl;

    return 0;
}