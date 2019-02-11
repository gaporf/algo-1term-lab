#include <stdio.h>
#include <stdlib.h>

struct vector {
    size_t size, max_size;
    int *arr, head, tail;
};

struct vector queue;

void new_vector(struct vector *v) {
    v->max_size = 1;
    v->size = 0;
    v->arr = malloc(1 * sizeof(int));
    v->head = v->tail = 0;
}

void add(struct vector *v) {
    size_t n = v->max_size;
    int *new_arr = malloc(2 * n * sizeof(int));
    *(new_arr) = *(v->arr + v->head);
    for (int i = (int) ((v->head + 1) % n), j = 1; i != v->tail; j++, i++, i %= n) {
        *(new_arr + j) = *(v->arr + i);
    }
    free(v->arr);
    v->arr = new_arr;
    v->head = 0;
    v->tail = (int) v->size;
    v->max_size *= 2;
}

void sub(struct vector *v) {
    size_t n = v->max_size;
    int *new_arr = malloc(sizeof(int) * n / 2);
    *(new_arr) = *(v->arr + v->head);
    for (int i = (int) ((v->head + 1) % n), j = 1; i != v->tail; j++, i++, i %= n) {
        *(new_arr + j) = *(v->arr + i);
    }
    free(v->arr);
    v->arr = new_arr;
    v->head = 0;
    v->tail = (int) v->size;
    v->max_size /= 2;
}

int back(struct vector *q) {
    return *(q->arr + q->head);
}

void push(struct vector *q, int num) {
    if (q->size == q->max_size) {
        add(q);
    }
    *(q->arr + q->tail) = num;
    q->tail = (int) ((q->tail + 1) % q->max_size);
    q->size++;
}

void pop(struct vector *q) {
    printf("%d\n", back(q));
    q->head = (int) ((q->head + 1) % q->max_size);
    q->size--;
    if (q->size != 0 && q->size * 4 < q->max_size) {
        sub(q);
    }
}

int main() {
    new_vector(&queue);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char c;
        scanf(" %c", &c);
        if (c == '+') {
            int num;
            scanf("%d", &num);
            push(&queue, num);
        } else {
            pop(&queue);
        }
    }
    return 0;
}