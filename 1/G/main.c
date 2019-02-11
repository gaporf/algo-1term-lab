#include <stdio.h>
#include <stdlib.h>

#pragma pack(4)

typedef long long ll;

const ll MOD = 4294967296;

struct list {
    int *arr;
    size_t size, max_size;
};

struct list first, second;
int min_first;

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void new_queue(int n) {
    first.arr = malloc(sizeof(int));
    first.size = 0;
    first.max_size = 1;
    second.arr = malloc(sizeof(int));
    second.size = 0;
    second.max_size = 1;
}

void push(int num) {
    if (first.size == first.max_size) {
        int *new_arr = malloc(sizeof(int) * first.max_size * 2);
        for (int i = 0; i < first.max_size; i++) {
            *(new_arr + i) = *(first.arr + i);
        }
        free(first.arr);
        first.arr = new_arr;
        first.max_size *= 2;
    }
    *(first.arr + first.size) = num;
    if (first.size == 0) {
        min_first = num;
    } else {
        min_first = min(min_first, num);
    }
    first.size++;
}

void transfer() {
    while (first.size != 0) {
        if (second.size == second.max_size) {
            int *new_arr = malloc(sizeof(int) * second.max_size * 2);
            for (int i = 0; i < second.max_size; i++) {
                *(new_arr + i) = *(second.arr + i);
            }
            free(second.arr);
            second.arr = new_arr;
            second.max_size *= 2;
        }
        *(second.arr + second.size) = *(first.arr + first.size - 1);
        if (second.size != 0) {
            *(second.arr + second.size) = min(*(second.arr + second.size), *(second.arr + second.size - 1));
        }
        first.size--;
        if (first.size != 0 && first.size * 4 < first.max_size) {
            int *new_arr = malloc(sizeof(int) * first.max_size / 2);
            for (int i = 0; i < first.size; i++) {
                *(new_arr + i) = *(first.arr + i);
            }
            free(first.arr);
            first.arr = new_arr;
            first.max_size /= 2;
        }
        second.size++;
    }
}

void pop() {
    if (second.size == 0) {
        transfer();
    }
    second.size--;
    if (second.size != 0 && second.size * 4 < second.max_size) {
        int *new_arr = malloc(sizeof(int) * second.max_size / 2);
        for (int i = 0; i < second.size; i++) {
            *(new_arr + i) = *(second.arr + i);
        }
        free(second.arr);
        second.arr = new_arr;
        second.max_size /= 2;
    }
}

ll get_min() {
    if (first.size == 0) {
        return *(second.arr + second.size - 1);
    } else if (second.size == 0) {
        return min_first;
    } else {
        return min(min_first, *(second.arr + second.size - 1));
    }
}

int main() {
    int n, m, k;
    ll a, b, c;
    ll ans = 0;
    scanf("%d%d%d", &n, &m, &k);
    scanf("%lli%lli%lli", &a, &b, &c);
    int x[k];
    for (int i = 0; i < k; i++) {
        scanf("%d", &x[i]);
    }
    new_queue(n);
    int x_1 = x[k - 2],
            x_2 = x[k - 1];
    for (int i = 0; i < m; i++) {
        if (i < k) {
            push(x[i]);
        } else {
            int X = (int) ((a * (ll) x_1 + b * (ll) x_2 + c) % MOD);
            push(X);
            x_1 = x_2;
            x_2 = X;
        }
    }
    ans += (ll) get_min();
    for (int i = m; i < n; i++) {
        pop();
        if (i < k) {
            push(x[i]);
        } else {
            int X = (int) ((a * (ll) x_1 + b * (ll) x_2 + c) % MOD);
            push(X);
            x_1 = x_2;
            x_2 = X;
        }
        ans += (ll) get_min();
    }
    printf("%lli", ans);

    return 0;
}