#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1000

int operand[MAX] = {0};
int operand_top = -1;
char operator[MAX] = {0};
int operator_top = -1;

int get_num(char *s, int *i) {
    int re = 0;
    while (s[*i] && s[*i] >= '0' && s[*i] <= '9') {
        re = re * 10 + s[*i] - '0';
        (*i)++;
    }
    (*i)--;
    return re;
}

int single_cal(char op, int a, int b) {
    switch(op) {
        case '+' : return a + b;
        case '-' : return a - b;
        case '*' : return a * b;
        case '/' : return a / b;
        case '^' : return (int)pow(a, b);
    }
}

int calc(char *exp) {
    int i = 0;
    int opr = 0;
    // int op_flag = 0;    // 用于区分加减号与正负号
    int in_priority[256] = {0};
    // int out_priority[256] = {0};
    int tmp_val = 0;

    in_priority['+'] = 3;
    in_priority['-'] = 3;
    in_priority['*'] = 6;
    in_priority['/'] = 6;
    in_priority['^'] = 9;

    while (exp[i]) {
        //printf("%c i: %d\n", exp[i], i);
        switch (exp[i]) {
            case '+' : 
            case '-' :
            case '*' :
            case '/' : 
            case '^' :{
                if ((-1 != operator_top) && (in_priority[operator[operator_top]] > in_priority[exp[i]])) {
                    tmp_val = single_cal(operator[operator_top], operand[operand_top - 1], operand[operand_top]);
                    printf("%d %c %d = %d\n", operand[operand_top - 1], operator[operator_top], operand[operand_top], tmp_val);
                    operator_top -= 1;
                    operand_top -= 2;
                    operand[++operand_top] = tmp_val;
                }
                operator[++operator_top] = exp[i];
            } break;
            default : {
                opr = get_num(exp, &i);
                operand[++operand_top] = opr;
            } 
        }
        ++i;
    }

    while (-1 != operator_top) {
        tmp_val = single_cal(operator[operator_top], operand[operand_top - 1], operand[operand_top]);
        printf("%d %c %d = %d\n", operand[operand_top - 1], operator[operator_top], operand[operand_top], tmp_val);
        operator_top -= 1;
        operand_top -= 2;
        operand[++operand_top] = tmp_val;
    }

    return operand[operand_top];
}

int main() {
    char exp[MAX + 5] = {0};

    scanf("%s", exp);
    printf("%d\n", calc(exp));

    return 0;
}