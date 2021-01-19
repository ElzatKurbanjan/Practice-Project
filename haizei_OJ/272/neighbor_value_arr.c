/*************************************************************************
	> File Name: neighbor_value_arr.c
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Jan 2021 05:47:44 AM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

void get_result(int *arr, int index, int *result, int *pi) {
    int min = 0x7fffffff;
    int j = -1;
    
    for (int i = index - 1; i >= 1; i--) {
        int tmp = abs(arr[i] - arr[index]);
        if (tmp < min || (tmp == min && arr[i] < arr[j])) {
            min = tmp;
            j = i;
        }
    }    
    *result = min;
    *pi = j;
    return;
}

int main() {
    int arr[MAX + 5] = {0};
    int n, input;
    int result, pi;

    scanf("%d\n", &n);
    for (int i = 1; i <= n ;i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 2; i <= n; i++) {
        get_result(arr, i, &result, &pi);
        printf("%d %d\n", result, pi);
    }
}
