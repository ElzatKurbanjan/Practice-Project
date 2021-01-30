/*************************************************************************
	> File Name: dum_version.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Jan 2021 04:00:30 AM PST
 ************************************************************************/

#include <stdio.h>

#define MAX_ROW 1000
#define MAX_COL 1000

// 该数组用来存储本元素向上数一共有几个F
int arr[MAX_ROW + 5][MAX_COL + 5];

// 以下变量用于求一行中的最大矩形
int l[MAX_COL + 5];
int r[MAX_COL + 5];
int st[MAX_COL + 5], top = -1;

void output_matric(int r, int c) {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            j && printf(" ");
            printf("%d", arr[i][j]);    
        }
        printf("\n");    
    }

}

long long max_region_in_line(int *h, int n) {
    long long max = 0;
    long long tmp = 0;
    
    top = -1;
    st[++top] = 0;
    h[0] = -1;
    for (int i = 1; i <= n; i++) {
        while (h[i] <= h[st[top]]) {
            --top;
        }

        l[i] = i - st[top];
        st[++top] = i;
    }

    top = -1;
    st[++top] = n + 1;
    h[n + 1] = -1;
    for (int i = n; i >= 1; i--) {
        while (h[i] <= h[st[top]]) --top;
        r[i] = st[top] - i;
        st[++top] = i;
    }

    for(int i = 1; i <= n; i++) {
        tmp = h[i] * (l[i] + r[i] - 1);
        max = max > tmp ? max : tmp;
    }

    /*for (int i = 1; i <= n; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", l[i]);
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");*/
    return max;
}

long long find_max_region(int r, int c) {
    long long max = 0;
    long long tmp = 0;

    for (int i = 1; i <= r; i++) {
        tmp = max_region_in_line(arr[i], c);
        max = max > tmp ? max : tmp;
    }

    return max;
}

int main() {
    int row = 0;
    int col = 0;
    char c = 0;
    long long s = 0;

    scanf("%d%d\n", &row, &col);

    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            scanf(" %c", &c);
            if (c == 'F') {
                arr[i][j] = arr[i - 1][j] + 1;
            }
            scanf("\n");
        }
    }

    //output_matric(row, col);
    s = find_max_region(row, col);

    printf("%lld\n", 3 * s);

    return 0;
}
