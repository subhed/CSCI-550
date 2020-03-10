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

void printI(int i, vector<int> A, vector<int> B){
	if(B[i] != i){
		printI(B[i], A, B);
	}
	cout<< A[i]<<" ";
}

void printD(int i, vector<int> A, vector<int> B){
	cout<< A[i]<<" ";

	if(B[i] != i){
		printD(B[i], A, B);
	}
}

void findBitonic(const vector<int> &A)
{

	vector<int> L(A.size());
	vector<int> B(A.size());

	vector<int> LD(A.size());
	vector<int> BD(A.size());

	vector<int> LenCal(A.size());

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

	LD[A.size() - 1] = 1;
	BD[A.size() - 1] = A.size() - 1;

	for (size_t i = A.size() - 1; i--; i >= 0)
	{
		LD[i] = 1;
		BD[i] = i;

		for (size_t j = A.size(); j--; j > i)
		{

			if (A[j] < A[i])
			{
				if (LD[j] + 1 > LD[i])
				{
					LD[i] = LD[j] + 1;
					BD[i] = j;
				}
			}
		}
	}

	for (size_t i = 0; i < A.size(); i++)
	{
		LenCal[i] = L[i] + LD[i] - 1;
	}

	int max_sum_i = max_element(LenCal.begin(), LenCal.end()) - LenCal.begin();
	int max_sum = *max_element(LenCal.begin(), LenCal.end());

	
	printI(max_sum_i, A, B);
	printD(BD[max_sum_i], A, BD);
	cout<<endl;

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
