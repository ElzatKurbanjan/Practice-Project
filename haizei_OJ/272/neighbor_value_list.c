/*************************************************************************
	> File Name: neight_value_list.c
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Jan 2021 06:55:49 AM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct node {
    long long value;
    int index;
} Node;

Node arr[MAX + 5];
int pos[MAX + 5]; // 索引表示第i个输入的元素，对应值表示其排序后所在位置
int l[MAX + 5];   // 索引表示排序后的位置，对应值表示排序后的前一个元素的索引
int r[MAX + 5];   // 索引表示排序后的位置，对应值表示排序后的后一个元素的索引
Node result[MAX + 5];  // 每一个元素的邻值及其index

int cmp(const void* a, const void* b) {
    Node *p = (Node *)a;
    Node *q = (Node *)b;
    if (p->value > q->value) return 1;
    else if (p->value < q->value) return -1;
    else return 0;
}

int main() {
    int n;

    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i].value);
        arr[i].index = i;
    }

    qsort(&arr[1], n, sizeof(Node), cmp);

    /* 初始化0和n+1元素，使其值与输入值的差值尽可能的大 */
    arr[0].value = 0x80000000;
    arr[n + 1].value = 0x7fffffff;

    /* 创建排序后的链表结构 */
    for (int i = 1; i <=n ; i++)
    {
        l[i] = i - 1;
        r[i] = i + 1;
        pos[arr[i].index] = i;
    }

    for (int i = n; i >= 2; i--) {
        int ordered_pos = pos[i];
        int left = l[ordered_pos];
        int right = r[ordered_pos];
        unsigned long long left_value = abs(arr[ordered_pos].value - arr[left].value);
        unsigned long long right_value = abs(arr[right].value - arr[ordered_pos].value);
        if (left_value <= right_value) {
            result[i].value = left_value;
            result[i].index = arr[left].index;
        } else {
            result[i].value = right_value;
            result[i].index = arr[right].index;
        }
        l[right] = left;
        r[left] = right;
    }

    for (int i = 2; i <= n; i++) {
        printf("%lld %d\n", result[i].value, result[i].index);
    }
}
