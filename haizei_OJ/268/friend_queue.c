/* !!!程序存在内存泄漏!!! */

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000
#define OP_LEN 10

unsigned short map[MAX];

typedef struct _node {
    int val;
    struct _node *next;
} Node;

typedef struct _list {
    Node head;  // 虚拟头节点
    int length;
    int id;     // 本链表编号
} List;

typedef struct _queue {
    List **data;
    int head;
    int tail;
} Queue;

List *init_list(int id) {
    List *l = (List *)malloc(sizeof(List));
    l->length = 0;
    l->head.val = 0;
    l->head.next = NULL;
    l->id = id;
    return l;
}

void insert_list_to_tail(List *l, int val) {
    if (NULL == l) return;
    Node *p = &l->head;
    Node *tmp = (Node *)malloc(sizeof(Node));

    while (p->next) p = p->next;
    tmp->val = val;
    tmp->next = NULL;
    p->next = tmp;
    l->length += 1;

    return;
}

int delete_list_from_head(List *l) {
    if (NULL == l) return -1;
    if (!l->length) return -1;
    
    Node *p = l->head.next;
    int re = 0;

    re = p->val;
    l->head.next = p->next;
    l->length -= 1; 
    free(p);
    return re;
}

Queue *init_queue(int length) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = 0;
    q->tail = 0;
    q->data = (List **)malloc(sizeof(List *) * length);
    return q;
}

/* 插入元素优先判断是否有朋友队列 
 * 若有朋友队列则优先插入朋友队列
 * 否则新建朋友队列并插入该队列 */
void enqueue(Queue *q, int val) {
    int list_id = map[val];
    int idx = q->head;
    
    while (idx < q->tail) {
        if (list_id == q->data[idx]->id) break;
        ++idx;
    }

    // 若idx==tail则需要新建队列，否则插入ind所在队列尾部
    if (idx != q->tail) {
        insert_list_to_tail(q->data[idx], val);
    } else {
        List *l = init_list(list_id);
        insert_list_to_tail(l, val);
        q->data[q->tail++] = l;
    }
    return;
}

int dequeue(Queue *q) {
    int re = 0;

    re = q->data[q->head]->head.next->val;

    delete_list_from_head(q->data[q->head]);
    if (q->data[q->head]->length == 0) {
        free(q->data[q->head]);
        q->head++;
    }

    return re;
}

void output(Queue *q) {
    printf("output: \n");
    List *l = NULL;
    Node *p = NULL;
    for (int i = q->head; i < q->tail; ++i) {
        l = q->data[i];
        p = l->head.next;
        while (p) {
            printf("%d ", p->val);
            p = p->next;
        }
    }
    printf("\n");
}

int main() {
    int n = 0;
    int m = 0;
    int temp = 0;
    char op[OP_LEN] = {0};
    int x = 0;
    Queue *q = init_queue(1005);

    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &temp);
            map[temp] = i;          // 记录对应节点的朋友队列号
        }
    }

    while (op[0] != 'S') {
        scanf("%s", op);
        // printf("%s ", op);
        switch (op[0]) {
            case 'E':{
                scanf("%d\n", &x);
                // printf("%d\n", x);
                enqueue(q, x);
            } break;
            case 'D': {
                int out = dequeue(q);
                printf("%d\n", out);
            } break;
        }
        // output(q);
    }

    return 0;
}