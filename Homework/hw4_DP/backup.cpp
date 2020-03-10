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

	vector<int> sum(A.size());
	vector<int> pos(A.size());

	
	for (size_t i = 0; i < A.size(); i++)
	{
		if (i == 0)
		{
			sum[0] = A[0];
			pos[0] = 0;
		}
		else
		{
			if (sum[i - 1] + A[i] > A[i])
			{
				sum[i] = sum[i - 1] + A[i];
				pos[i] = pos[i - 1];
			}
			else if (sum[i - 1] + A[i] < A[i])
			{
				sum[i] = A[i];
				pos[i] = i;
			}
		}
	}

	int max_sum_i = max_element(sum.begin(), sum.end()) - sum.begin();
	int max_sum = *max_element(sum.begin(), sum.end());

	cout << pos[max_sum_i] << " " << max_sum_i << " " << max_sum << endl;
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
