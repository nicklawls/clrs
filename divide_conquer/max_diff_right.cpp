#include <iostream>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <map>
using namespace std;

// complile using: clang++ -std=c++11 -stdlib=libc++ -Wall -Werror max_diff_rigth.cpp -o max_diff_right

int max_index_in_range(vector<int> &A, int begin, int end) { // vector, first index, ACTUAL LAST INDEX

	if ((end - begin) <= 1) { // length of range <= 2
		int max_index = ( (A[begin] > A[end]) ? begin : end );
		return max_index;
	}

	else {
		int mid = ((begin + end) / 2) + 1;
		int max_index_left = max_index_in_range(A, begin, mid - 1);
		int max_index_right = max_index_in_range(A, mid, end);
		int max_index = ( (A[max_index_left] > A[max_index_right]) ? max_index_left : max_index_right );
		return max_index;
	}
}

int min_index_in_range(vector<int> &A, int begin, int end) { // vector, first index, ACTUAL LAST INDEX

	if ((end - begin) <= 1) { // length of range <= 2
		int min_index = ( (A[begin] < A[end]) ? begin : end );
		return min_index;
	}

	else {
		int mid = ((begin + end) / 2) + 1;
		int min_index_left = min_index_in_range(A, begin, mid - 1);
		int min_index_right = min_index_in_range(A, mid, end);
		int min_index = ( (A[min_index_left] < A[min_index_right]) ? min_index_left : min_index_right );
		return min_index;
	}
}


pair<int,int> max_diff_right(vector<int> &A, int begin, int end) {
	int max_index = max_index_in_range(A, begin, end);

	if (max_index < A.size() - 1 ) {
		int min_right_of_max = min_index_in_range(A, max_index, end);
		return make_pair(A[max_index], A[min_right_of_max]);
	}

	else {
		cout << "N/A, array is strictly increasing" << endl;
		return make_pair(-1,-1);
	}
}


int main()
{
	vector<int> test({44,323,5,5135,2,55,8});
	//generate(test.begin(), test.end(), rand);

	auto result = max_diff_right(test, 0, test.size() - 1);

	cout << "First: " << result.first << endl;
	cout << "Second: " << result.second << endl;
}
