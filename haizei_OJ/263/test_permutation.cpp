/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Jan 2021 06:12:29 AM PST
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int arr[] = {1, 2 ,3 , 4};
    do {
        for (int i = 0; i < 4; i++)
            cout << arr[i] << " ";
        cout << endl;
    } while (next_permutation(arr , arr + 4));
}
