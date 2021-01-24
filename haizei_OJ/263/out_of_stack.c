/*************************************************************************
	> File Name: out_of_train_station.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Jan 2021 05:06:10 AM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

#define SWAP(a, b) do { \
        a = (a) ^ (b);\
        b = (a) ^ (b);\
        a = (a) ^ (b);\
} while(0)

typedef struct stack {
    int *data;
    int size;
    int top;
} Stack;

/* return 0 if next permutation doesn't exist
 * return 1 if next permutation exist */
int next_permutation(int arr[], int size) {
    int i = 0;
    int sub_head = 0;
   
    /* 找第m项，即已经完成逆序迭代的子序列 */
    for (i = size - 1; i > 0; i--) {
        if (arr[i] > arr[i - 1]) {
            break;
        }   
    }
        
    /* 若完全逆序，则无下一个排列 */
    if (0 == i) {
        return 0;   
    } else {
        sub_head = i - 1;    
    }
        
    /* 找出后m项中比sub_head大的最小元素 */
    for (i = size - 1; i > sub_head; i--) {
        if (arr[i] > arr[sub_head]) {
            break;  
        }   
    }
    SWAP(arr[i], arr[sub_head]);   

    /* 反转后m项 */
    for (i = sub_head + 1; i < size - 1; i++, size--) {
        SWAP(arr[i], arr[size - 1]);    
    }

    return 1;
}

Stack *init_stack(int n){
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->size = n;
    p->top = -1;
    p->data = (int *)malloc(sizeof(int) * n);
    return p;
}

void clear(Stack *s) {
    if (NULL == s) return;
    free(s->data);
    free(s);
    return;
}

int push(Stack *s, int val) {
    if (NULL == s) {
        return 0;
    }
    if (s->top == s->size - 1) {
        return 0;
    }
    s->data[++s->top] = val;
    return 1;
}

int top(Stack *s) {
    return s->data[s->top];
}

int pop(Stack *s) {
    if (NULL == s) return 0;
    if (s->top == 0) return 0;
    s->top--;
    return 1;
}

int is_valid(int arr[], int size) {
    Stack *s = init_stack(MAX_N + 5);
    int current_item = 1;

    push(s, -1); // 保证第一个元素一定大于栈顶元素

    for (int i = 0; i < size; i++) {
        if (arr[i] > top(s)) {
            for (int j = current_item; j <= arr[i]; j++, current_item++) {
                push(s, j);
            }
        } else {
            if (top(s) != arr[i]) {
                clear(s);
                return 0;
            }
        }
        pop(s);
    }

    clear(s);
    return 1;
}

int main() {
    int n = 0;
    int arr[MAX_N + 5] = {0};
    int cnt = MAX_N;

    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    do {
        if (is_valid(arr, n)) {
            for (int i = 0; i < n; i++) {
                printf("%d", arr[i]);
            }
            printf("\n");
            cnt--;
        }
    }while (next_permutation(arr, n) && cnt);    

    return 0;
}
