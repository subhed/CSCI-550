#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int partition(vector<int> &A, const string &S, int low, int high, int index);
void quicksort(vector<int> &A, const string &S, int low, int high);
bool isLessEqual(const string &S, int first, int second);

void calculateSA(const string &S, vector<int> &SA);
void calculateLCP(const string &S, const vector<int> &SA, vector<int> &LCP);

//auxiliary functions
//returns an integer that is smaller by 1 than the smallest char of the string
int findSmallest(const string &S);
//given a string S and empty string revS,
//this function calculates the reverse of S and stores it in revS
void findReverse(const string &S, string &revS);

//Test 3:
//Problem 1
int occRepeated(const string &X, int m, int k)
{

	string str = X;

	str.append("$");

	int L = 0, R = 0, globalL = 0, globalOcc = 0, occur = 0, gOc = 0;

	vector<int> SA(str.size());
	calculateSA(str, SA);

	vector<int> LCP(str.size());
	calculateLCP(str, SA, LCP);

	for (size_t i = 0; i < LCP.size(); i++)
	{

		if (LCP[i] >= m)
		{
			if (L == 0 && R == 0)
			{
				L = i;
				R = L;
			}
			else
			{
				R = R + 1;
			}
		}
		else if (LCP[i] < m && L != 0 && R != 0)
		{

			occur = R - L + 2;

			if (occur >= k)
			{
				gOc = gOc + 1;
			}

			if (occur > globalOcc)
			{
				globalOcc = occur;
				globalL = L;
			}

			R = 0;
			L = 0;
		}
	}

	occur = R - L + 2;
	if (occur >= k)
	{
		gOc = gOc + 1;
	}
	if (occur > globalOcc)
	{
		globalOcc = occur;
		globalL = L;
	}

	//solve your problem 1 here, do whatever needs to be done

	return gOc;
}
//Problem 2
bool isSpecificForm(const string &X, const string &Y)
{
	int n = X.size();

	string T = X;
	T.append(X);
	T.append(X);
	T.append("#");
	T.append(Y);
	T.append("$");

	vector<int> SA(T.size());
	calculateSA(T, SA);
	vector<int> LCP(T.size());
	calculateLCP(T, SA, LCP);

	for (size_t i = 0; i < LCP.size(); i++)
	{
		if (LCP[i] == 2 * n)
		{
			if ((SA[i - 1] < 3 * n && SA[i] > 3 * n) || (SA[i] < 3 * n && SA[i - 1] > 3 * n))
			{

				return true;
			}
		}
	}

	return false;
}
//Problem 3
void maxUniquePal(const string &S, int m)
{
	int Fl = -1;
	string Final;

	int n = S.size(), j = 0, k = 0, x = 0;

	string SR = S;
	string T = S;

	reverse(SR.begin(), SR.end());
	T.append("#");
	T.append(SR);
	T.append("$");

	vector<int> SA(T.size());
	calculateSA(T, SA);

	vector<int> LCP(T.size());
	calculateLCP(T, SA, LCP);

	for (size_t i = 0; i < LCP.size(); i++)
	{
		if (LCP[i] >= m)
		{
			x = LCP[i];
			if (LCP[i + 1] < x && LCP[i - 1] < x)
			{
				if ((SA[i] < n && SA[i - 1] > n) || (SA[i - 1] < n && SA[i] > n))
				{

					if (SA[i] < n)
					{
						j = SA[i];
						k = SA[i - 1];
					}
					else if (SA[i - 1] < n)
					{
						k = SA[i];
						j = SA[i - 1];
					}
					int K1 = (2 * S.size()) - j - x + 1;

					if (k == K1)
					{
						if (Fl < x)
						{
							Fl = x;
							Final = T.substr(k, x);
						}
					}
				}
			}
		}
	}
	if (Fl != -1)
	{
		cout << Final << "\n";
	}
	else
	{
		cout << "No solution."<<"\n";
	}
}

int main()
{

	/* to calculate SA, suffix array, for the given string S, do:
	vector<int> SA(S.size());
	calculateSA(S, SA);
	*/

	/* to calculate LCP for the given string S and its suffix array SA, do:
	vector<int> LCP(S.size());
	calculateLCP(S, SA, LCP);
	*/

	string command;
	getline(cin, command);

	if (command == "occRepeated")
	{
		int m, k;
		string X("");
		string aline;
		cin >> m >> k;
		while (getline(cin, aline))
		{
			X = X + aline;
		}

		int res = occRepeated(X, m, k);
		cout << "The string has " << res << " repeated substrings of length exactly " << m
			 << " that occur at least " << k << " times." << endl;
	}
	else if (command == "isSpecificForm")
	{

		string X(""), Y("");
		getline(cin, X);
		getline(cin, Y);

		bool res = isSpecificForm(X, Y);
		if (res)
			cout << "The string Y is of the specific form." << endl;
		else
			cout << "The string Y is NOT of the specific form." << endl;
	}
	else if (command == "maxUniquePal")
	{
		string S;
		int m;
		cin >> m;
		string aline;
		while (getline(cin, aline))
			S = S + aline;
		maxUniquePal(S, m);
	}
	else
	{
		cerr << "ERROR: the command " << command << " is not recognized." << endl;
	} //else

	return 0;
}

void calculateSA(const string &S, vector<int> &SA)
{
	int size = (int)S.length();

	for (int i = 0; i < size; i++)
		SA[i] = i;

	//sorts the suffixes in Omega(nlog(n))-time
	quicksort(SA, S, 0, size - 1);

} //calculateSA()

void calculateLCP(const string &S, const vector<int> &SA, vector<int> &LCP)
{
	vector<int> Rank(SA.size());
	int size = (int)S.size();
	for (int i = 0; i < size; i++)
	{
		LCP[i] = 0;
		Rank[SA[i]] = i;
	} //for

	int h = 0;
	for (int i = 0; i < size; i++)
	{
		if (Rank[i] > 1)
		{
			int k = SA[Rank[i] - 1];
			while (S[i + h] == S[k + h])
				h++;
			LCP[Rank[i]] = h;
			if (h > 0)
				h--;
		} //if
	}	  //for

} //calculateLCP()

bool isLessEqual(const string &S, int first, int second)
{
	int size = (int)S.length();
	while (first < size && second < size)
	{
		if (tolower(S[first]) < tolower(S[second]))
			return true;
		else if (tolower(S[first]) > tolower(S[second]))
			return false;
		else
		{
			first++;
			second++;
		}

	} //while
	if (first == size)
		return true;
	return false;
} //isLessEqual

int partition(vector<int> &A, const string &S, int low, int high, int index)
{
	//swap A at index with the last element in the range
	int dummy = A[index];
	A[index] = A[high];
	A[high] = dummy;

	int pivotIndex = high;
	int i = low, j = high - 1;
	while (i <= j)
	{
		while ((i < high) && (isLessEqual(S, A[i], A[pivotIndex])))
			i++;
		while ((j >= low) && (!(isLessEqual(S, A[j], A[pivotIndex]))))
			j--;
		if (i < j)
		{ //swap A[i] and A[j]
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			i++;
			j--;
		} //if
	}	  //while
	//swap A[i] and pivot
	int temp = A[high];
	A[high] = A[i];
	A[i] = temp;
	return i;
} //partition

void quicksort(vector<int> &A, const string &S, int low, int high)
{
	if (low < high)
	{
		int pivotIndex = partition(A, S, low, high, high);
		quicksort(A, S, low, pivotIndex - 1);
		quicksort(A, S, pivotIndex + 1, high);
	}
} //quicksort

int findSmallest(const string &S)
{
	if (S.size() == 0)
		return -1;
	int smallest = (int)S[0];
	for (int i = 1; i < (int)S.size(); i++)
	{
		if (S[i] < smallest)
			smallest = (int)S[i];
	}
	return (smallest - 1);
}

void findReverse(const string &X, string &revX)
{
	revX.resize(X.size());
	int j = (int)X.size() - 1;
	int i = 0;
	for (; j >= 0; j--)
	{
		revX[i++] = X[j];
	}
}

