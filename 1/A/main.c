#include <stdio.h>
#include <stdlib.h>

struct vector {
    size_t max_size, size;
    long *arr;
};

struct vector stack;

void new_vector(struct vector *v) {
    v->max_size = 1;
    v->size = 0;
    v->arr = malloc(sizeof(long));
}

void push(struct vector *v) {
    size_t n = v->max_size;
    long *new_arr = malloc(sizeof(long) * 2 * n);
    for (size_t i = 0; i < n; i++) {
        *(new_arr + i) = *(v->arr + i);
    }
    free(v->arr);
    v->arr = new_arr;
    v->max_size *= 2;
}

void pop(struct vector *v) {
    size_t n = v->max_size;
    long *new_arr = malloc(sizeof(long) * n / 2);
    for (size_t i = 0; i < n / 2; i++) {
        *(new_arr + i) = *(v->arr + i);
    }
    free(v->arr);
    v->arr = new_arr;
    v->max_size /= 2;
}

void push_back(struct vector *v, long num) {
    if (v->size != v->max_size) {
        *(v->arr + v->size) = num;
        v->size++;
    } else {
        push(v);
        *(v->arr + v->size) = num;
        v->size++;
    }
}

long back(struct vector *v) {
    return *(v->arr + v->size - 1);
}

void pop_back(struct vector *v) {
    printf("%li\n", back(v));
    v->size--;
    if (v->size > 0 && v->size * 4 < v->max_size) {
        pop(v);
    }
}

int main() {
    new_vector(&stack);
    long m;
    scanf("%li", &m);
    for (long i = 0; i < m; i++) {
        char c;
        scanf(" %c", &c);
        if (c == '+') {
            long num;
            scanf("%li", &num);
            push_back(&stack, num);
        } else {
            pop_back(&stack);
        }
    }
    return 0;
}