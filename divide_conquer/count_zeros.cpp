#include <iostream>
#include <vector>

using namespace std;

// complile using: clang++ -std=c++11 -stdlib=libc++ -Wall -Werror count_zeros.cpp -o count_zeros

int count_zeros(vector<int> & A, int begin, int end) {

 	if (A.at(begin) != A.at(end) ) { // ends differ, divide
		int mid = (end + begin)/2; // had to debug heavily, original idea was to make new vectors at every step
		return count_zeros(A, begin, mid) + count_zeros(A, mid+1, end);
	} 

	else if (A.at(begin) == 0) { // all zeros, contribute size of subarray
		return end - begin + 1;
	} 

	else { // all ones, contribute 0
		return 0; 
	}
}


int main() 
{
	vector<int> a({1,1,1,1,1,0,0,0});
	cout << count_zeros(a, 0, a.size()-1) << endl;
}

