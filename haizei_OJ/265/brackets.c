#include <stdio.h>

#define MAX_INPUT 10000

char stack[MAX_INPUT] = {0};
int stack_top = -1;

int is_match(char a, char b) {
    return ((a == '(') && (b == ')')) || \
    ((a == '[') && (b == ']')) || \
    ((a == '{') && (b == '}'));
}

int find_max_matching_brackets(char *s) {
    int i = 0;
    int max = -1;
    int length = 0;

    while (s[i]) {
        // printf("s[%d]: %c\n", i, s[i]);
        switch (s[i]) {
            case '{' :
            case '[' :
            case '(' : {
                ++length;
                stack[++stack_top] = s[i];
            } break;
            case ')' :
            case '}' :
            case ']' : {
                if (stack_top != -1) {
                    if (is_match(stack[stack_top], s[i])) {
                        ++length;
                        --stack_top;
                    } else {
                        length -= (stack_top + 1);
                        stack_top = -1;
                        max = length > max ? length : max;
                        length = 0;
                    }
                } else {
                    length = 0;
                }
            } break;
            default : break;
        }
        /*for (int j = 0; j <= stack_top; j++) {
            printf("%c ", stack[j]);
        }
        printf("length: %d\n", length);*/
        ++i;
    }

    length -= (stack_top + 1);
    stack_top = -1;
    max = length > max ? length : max;

    return max;
}

int main() {
    char input[MAX_INPUT + 5];

    scanf("%s", input);

    printf("%d\n", find_max_matching_brackets(input));

    return 0;
}