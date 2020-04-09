#include <iostream>
#include <vector>
#include <string>

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
	if (command == "problem1")
	{
		int k;
		string X("");
		getline(cin, X);
		cin >> k;
		X.append("$");

		int L = 0, R = 0, globalL = 0, globalOcc = 0, occur = 0;

		vector<int> SA(X.size());
		calculateSA(X, SA);

		vector<int> LCP(X.size());
		calculateLCP(X, SA, LCP);

		for (size_t i = 0; i < SA.size(); i++)
		{
			cout<< i<<" : "<<SA[i]<<endl;
		}
		

		for (size_t i = 0; i < LCP.size(); i++)
		{

			if (LCP[i] >= k)
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
			else if (LCP[i] < k && L != 0 && R != 0)
			{

				occur = R - L + 2;

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
		if (occur > globalOcc)
		{
			globalOcc = occur;
			globalL = L;
		}

		if (globalOcc < 1 || X.substr(SA[globalL], k) == "$")
		{
			cout << "Not found." << endl;
		}
		else
			cout << X.substr(SA[globalL], k) << " " << globalOcc << endl;

		//solve your problem 1 here, do whatever needs to be done
	}
	else if (command == "problem2")
	{

		string X(""), Y("");
		getline(cin, X);
		getline(cin, Y);
		int n = X.length();
		int flag = 0;

		string Z = X + X + "#" + Y + "$";

		vector<int> SA(Z.size());
		calculateSA(Z, SA);

		vector<int> LCP(Z.size());
		calculateLCP(Z, SA, LCP);

		for (size_t i = 0; i < LCP.size(); i++)
		{
			if (LCP[i] == n)
			{
				if (SA[i] < 2 * n && SA[i - 1] > 2 * n)
				{
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
		}

		if (flag == 1)
		{
			cout << "Y is a circular shift of X." << endl;
		}
		else
		{
			cout << "Y is not a circular shift of X." << endl;
		}

	} //else if
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
