#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
using namespace std;

int MaxSubarrayBruteForce(const vector<int> &);
int MaxSubarray(const vector<int> &);
int MaxCrossingSubarray(const vector<int> &, int);
int max3(int, int, int); 


int main() 
{
    vector<int> test(100000000);
    generate(test.begin(), test.end(), rand);
    

    //int p = MaxSubarrayBruteForce(test); // poooped at 10,000

    //cout << "Brute Force: " << p << endl << endl;

    int q = MaxSubarray(test);

    cout << "Divide and Conquer: " << q << endl; // did 10,000,000 in about 20 seconds, pooped at 100,000,000

    //int mid = test.size()/2;
    //int f = MaxCrossingSubarray(test, mid);
    //cout << "Cross: " << f << endl;

    
        
}


int MaxSubarrayBruteForce(const vector<int> & A) 
{
    int max = numeric_limits<int>::min(); // lowest value of int
    for (auto i = A.begin(); i != A.end(); ++i) {
    	for (auto j = i + 1; j != A.end(); ++j) {
    	    int current_max = accumulate(i, j, 0);
    	    if (current_max > max) {
    		  max = current_max;
    	    }
    	}
    }
    return max;
}


int MaxSubarray(const vector<int> & A) 
{
    
    if (A.size() == 1) { // base
        return A.at(0);
        cout << "end" << endl;
    } else {             // recursive
        int mid = A.size() / 2;

        vector<int> left(A.begin(), A.begin() + mid);
        vector<int> right(A.begin() + mid, A.end());

        int left_max = MaxSubarray(left);
        int right_max = MaxSubarray(right);
        int cross_max = MaxCrossingSubarray(A, mid);

        //cout << left_max << " " << right_max << " " << cross_max << endl;

        return max3(left_max, right_max, cross_max);
    }
}


int MaxCrossingSubarray(const vector<int> & A, int mid) 
{
    int left_sum = 0, right_sum = 0, sum = 0;
    //int right_sum = 0;
    //int sum = 0;

    for (auto i = A.begin() + mid; i != A.begin(); i--) {
        sum += *i;
        if (sum > left_sum) {
            left_sum = sum;
        } 

    }

    sum = 0;

    for (auto i = A.begin() + mid + 1; i != A.end(); i++) {
        sum += *i;
        if (sum > right_sum) {
            right_sum = sum;
        } 
    }

    return left_sum + right_sum;
}

// return maximum of 3 values
int max3(int a, int b, int c) {
  if (a >= b) {
    if (a >= c) {
      return a;
    } else {
      return c;
    }
  } else { 
    if (b >= c) {
      return b;
    } else {
      return c;
    }
  }
}