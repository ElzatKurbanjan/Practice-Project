/*************************************************************************
	> File Name: largest_rectangle.c
	> Author: 
	> Mail: 
	> Created Time: Sat 30 Jan 2021 03:56:12 AM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

long long height[MAX + 5];
int left[MAX + 5];
int right[MAX + 5];

typedef struct _statck {
    int *data;
    int length;
    int top;
} Stack;

Stack *init_stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(n * sizeof(int));
    s->length = n;
    s->top = -1;
    return s;
}

int empty(Stack *s) {
    return (s->top == -1);
}

int top(Stack *s) {
    return s->data[s->top];
}

int push(Stack *s, int val) {
    s->data[++s->top] = val;
    return 1;
}

int pop(Stack *s) {
    s->top--;
    return 1;
}

void erase_stack(Stack *s) {
    if (NULL == s) return;
    free(s->data);
    free(s);
}

long long find_largest_rectangle(long long *h, int n) {
    Stack *s = init_stack(n + 5);
    long long max = 0;
    long long tmp = 0;

    push(s, 0);

    for (int i = 1; i <= n; i++) {
        while (h[i] <= h[top(s)]) {
            pop(s);
        }
        left[i] = i - top(s);
        push(s, i);
    }
    erase_stack(s);

    s = init_stack(n + 5);
    push(s, n + 1);
    for (int i = n; i >= 1; i--) {
        while (h[i] <= h[top(s)]) {
            pop(s);
        }
        right[i] = top(s) - i;
        push(s, i);
    }
    erase_stack(s);

    for (int i = 1; i <= n; i++) {
        tmp = (h[i] * (right[i] + left[i] - 1));
        max = max > tmp ? max : tmp;
    }

    return max;
}

int main() {
    int n;
    
    scanf("%d\n", &n);
    height[0] = -1;
    height[n + 1] = -1;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &height[i]);
    }

    printf("%lld\n", find_largest_rectangle(height, n));

    return 0;
}
