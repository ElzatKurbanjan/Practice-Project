/*************************************************************************
	> File Name: neighbor_value.c
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Jan 2021 03:41:33 AM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int id;
    int value;
    struct node *next;
    struct node *priv;
} Node;

typedef struct list {
    Node head;  // virtual head
    int length;
} List;

List *init_list() {
    List *p = (List *)malloc(sizeof(List));
    p->head.next = NULL;
    p->head.priv = NULL;
    p->length = 0;
    return p;
}

int insert_node(List *list, int index, int value, int id) {
    if (NULL == list) {
        return -1;
    }
    if (index > list->length || index < 0) {
        return -1;
    }
    Node *p = &list->head;
    int i = index;
    Node *q = NULL;
    while (i--) {
        p = p->next;
    }
    q = (Node *)malloc(sizeof(Node));
    q->value = value;
    q->id = id;
    q->next = p->next;
    q->priv = p;
    p->next->
    p->next = q;
    ++list->length;
    return 0;
}

void output(List *list) {
    Node *p = list->head.next;
    while(p) {
        printf("node[%d]: value = %d\n", p->id, p->value);
        p = p->next;
    }
    return;
}



int main() {
    List *head = init_list();
    int n = 0;
    int input = 0;
    int result,p;

    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &input);
        insert_node(head, i, input, i + 1);
    }

    return 0;
}
