#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

void findSubarray(const vector<int> &A)
{

	int lsum, lpos, lindex;
	int fsum, fpos, findex;

	for (size_t i = 0; i < A.size(); i++)
	{
		if (i == 0)
		{

			lsum = A[0];
			lpos = 0;
			lindex = 0;

			fsum = A[0];
			fpos = 0;
			findex = 0;
		}
		else
		{
			if (lsum + A[i] > A[i])
			{

				lsum = lsum + A[i];
				lpos = lpos;

				if (lsum > fsum)
				{
					fsum = lsum;
					fpos = lpos;
					findex = i;
				}
			}
			else if (lsum + A[i] < A[i])
			{

				lsum = A[i];
				lpos = i;

				if (lsum > fsum)
				{
					fsum = lsum;
					fpos = lpos;
					findex = i;
				}
			}
		}
	}

	cout << fpos << " " << findex << " " << fsum << endl;
}

void findBitonic(const vector<int> &A)
{

	vector<int> L(A.size());
	vector<int> B(A.size());

	for (size_t i = 0; i < A.size(); i++)
	{

		if (i == 0)
		{
			L[0] = 1;
			B[0] = 0;
		}
		else
		{
			L[i] = 1;
			B[i] = i;

			for (size_t j = 0; j < i; j++)
			{
				if (A[j] < A[i])
				{
					if (L[j] + 1 > L[i])
					{
						L[i] = L[j] + 1;
						B[i] = j;
					}
				}
			}
		}
	}

	for (size_t i = 0; i < L.size(); i++)
	{
		cout << " " << L[i];
	}

	cout << endl;
	for (size_t i = 0; i < B.size(); i++)
	{
		cout << " " << B[i];
	}
}

int main()
{
	int size;
	cin >> size;
	vector<int> A;
	for (int i = 0; i < size; i++)
	{
		int x;
		cin >> x;
		A.push_back(x);
	}

	string command;
	cin >> command;
	if (command == "findSubarray")
	{
		findSubarray(A); //will print the results inside this function
	}
	else if (command == "findBitonic")
	{
		findBitonic(A); //will print the results inside this function
	}
	else
	{
		cerr << "ERROR: the command " << command << " is not recognized." << endl;
	}
	return 0;
} //main()
