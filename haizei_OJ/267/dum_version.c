/*************************************************************************
	> File Name: dum_version.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Jan 2021 04:00:30 AM PST
 ************************************************************************/

#include <stdio.h>

#define MAX_ROW 1005
#define MAX_COL 1005

unsigned char arr[MAX_ROW][MAX_COL];

void output_matric(int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            j && printf(" ");
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}


int lf_max_region(int x, int y, int r, int c) {
    int r_length = 0;
    int c_length = 0;

    for (int i = y; i < c; i++ ) {
        if (!arr[x][i]) break;
        c_length += 1;
    }

    if (!c_length) goto out;

    r_length += 1;
    for (int i = x + 1; i < r; i++) {
        for (int j = y; j < (y + c_length) && j < c; j++) {
            if (!arr[i][j]) goto out;
        }
        r_length += 1;
    }

out:
    printf("x: %d y: %d r_length: %d c_length: %d ret: %d\n", x, y, r_length, c_length, r_length * c_length);
    return r_length * c_length;
}

int find_max_region(int r, int c) {
    int max = 0;
    int tmp = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            tmp = lf_max_region(i, j, r, c);
            max = (max > tmp) ?  max : tmp;
        }
    }

    return max;
}

int main() {
    int row = 0;
    int col = 0;
    char c = 0;
    int s = 0;
    char input[2500];
    
    scanf("%d%d\n", &row, &col);

    for (int i = 0; i < row; i++) {
        scanf("%[^\n]\n", input);
        for (int j = 0, c_idx = 0; j < col; j++, c_idx+=2) {
            c = input[c_idx];
            switch (c) {
                case 'R': {
                    arr[i][j] = 0;
                } break;
                case 'F': {
                    arr[i][j] = 1;
                } break;
            }
        }
    }
 
    output_matric(row, col);
    s = find_max_region(row, col);
    printf("%d\n", 3 * s);

    return 0;
}
