
//   Convert this program to C++

// *   change to C++ io

// *   change to one line comments

// *   change defines of constants to const

// *   change array to vector<>

// *   inline any short function

#include <iostream>
#include <vector>
using namespace std;

const int N = 40; // A constant global variable

// It sums up the number in the vector array and assigns the sum to the variable p
inline void sum(int &p, int n, vector<int> d)
{
    p = 0;
    for (int i = 0; i < n; ++i)
        p = p + d[i];
}

int main()

{
    using namespace std;
    // Initializing variables
    int i;

    int accum = 0;

    vector<int> data; // A vector array

    // Add numbers from 0 to 40 to the array
    for (i = 0; i < N; ++i)

        data.push_back(i);
    // Pass the array and accumulator variable to the function sum
    sum(accum, N, data);

    // Print the new value of accum(summed up value) to the screen.
    cout << "sum is " << accum << endl;

    return 0;
}
