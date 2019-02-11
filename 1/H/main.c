#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int N = 500000;

typedef unsigned short int shint;

struct vector {
    shint *arr;
    size_t size, max_size;
};

struct queue {
    struct vector first, second;
} que;

struct command {
    char *str;
};

struct commands {
    struct command *coms;
    size_t size, max_size;
} com;

struct hash_table {
    char *str;
    int num;
    struct hash_table *next_table;
};

struct hash_table hashes[65536];
struct hash_table *cur_hash_table, *prev_hash_table;

void new_commands() {
    com.coms = malloc(sizeof(struct commands));
    com.size = 0;
    com.max_size = 1;
}

void new_vector(struct vector *v) {
    v->arr = malloc(sizeof(shint));
    v->size = 0;
    v->max_size = 1;
}

void new_queue() {
    new_vector(&que.first);
    new_vector(&que.second);
}

void new_hash() {
    for (int i = 0; i < 65536; i++) {
        (hashes + i)->str = NULL;
        (hashes + i)->next_table = NULL;
        (hashes + i)->num = -1;
    }
}

void add_commands() {
    size_t n = com.max_size;
    struct command *new_command = malloc(2 * n * sizeof(struct command));
    for (int i = 0; i < n; i++) {
        *(new_command + i) = *(com.coms + i);
    }
    free(com.coms);
    com.coms = new_command;
    com.max_size *= 2;
}

void add(struct vector *v) {
    size_t n = v->max_size;
    shint *new_arr = malloc(2 * n * sizeof(shint));
    for (int i = 0; i < n; i++) {
        *(new_arr + i) = *(v->arr + i);
    }
    free(v->arr);
    v->arr = new_arr;
    v->max_size *= 2;
}

int mystrlen(const char *str) {
    int len = 0;
    for (; str[len]; len++);
    return len;
}

void push_command(char *str) {
    if (com.size == com.max_size) {
        add_commands();
    }
    (com.coms + com.size)->str = malloc((size_t) mystrlen(str) + 1);
    for (int i = 0;; i++) {
        *((com.coms + com.size)->str + i) = *(str + i);
        if (!str[i]) {
            break;
        }
    }
    com.size++;
}

void push_vector(struct vector *v, shint num) {
    if (v->size == v->max_size) {
        add(v);
    }
    *(v->arr + v->size) = num;
    v->size++;
}

void push(shint num) {
    push_vector(&que.first, num);
}

void transfer() {
    while (que.first.size != 0) {
        if (que.second.size == que.second.max_size) {
            add(&que.second);
        }
        *(que.second.arr + que.second.size) = *(que.first.arr + que.first.size - 1);
        que.first.size--;
        que.second.size++;
    }
    free(que.first.arr);
    que.first.arr = malloc(sizeof(shint));
    que.first.max_size = 1;
}

void delete(struct vector *v) {
    size_t n = v->max_size;
    shint *new_arr = malloc(n * sizeof(shint) / 2);
    for (int i = 0; i < n / 2; i++) {
        *(new_arr + i) = *(v->arr + i);
    }
    free(v->arr);
    v->arr = new_arr;
    v->max_size /= 2;
}

shint pop() {
    if (que.second.size == 0) {
        transfer();
    }
    shint ans = *(que.second.arr + que.second.size - 1);
    que.second.size--;
    if (que.second.size != 0 && que.second.size * 4 < que.second.max_size) {
        delete(&que.second);
    }
    return ans;
}

shint hashCode(const char *str) {
    shint hash = 0, j = 1;
    for (int i = 0; str[i]; i++, j *= 257) {
        hash += str[i] * j;
    }

    return hash;
}

int equals(char *str, char *STR) {
    if (mystrlen(str) != mystrlen(STR)) {
        return 0;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] != STR[i]) {
            return 0;
        }
    }
    return 1;
}

void add_string(char *str, int num) {
    shint hash = hashCode(str);
    cur_hash_table = &hashes[hash];
    prev_hash_table = NULL;
    while (cur_hash_table != NULL && cur_hash_table->str != NULL) {
        prev_hash_table = cur_hash_table;
        cur_hash_table = cur_hash_table->next_table;
    }
    cur_hash_table = malloc(sizeof(struct hash_table));
    cur_hash_table->str = malloc((size_t) mystrlen(str) + 1);
    for (int i = 0;; i++) {
        *(cur_hash_table->str + i) = *(str + i);
        if (!str[i]) {
            break;
        }
    }
    cur_hash_table->num = num;
    cur_hash_table->next_table = NULL;
    if (hashes[hash].str == NULL) {
        hashes[hash] = *cur_hash_table;
    }
    if (prev_hash_table != NULL) {
        prev_hash_table->next_table = cur_hash_table;
    }
}

shint strToInt(const char *str) {
    long long ans = 0;
    for (int i = 0; str[i]; i++) {
        ans *= 10;
        ans += (str[i] - '0');
    }
    return (shint) ans;
}

int new_i(char *str) {
    shint hash = hashCode(str);
    cur_hash_table = &hashes[hash];
    for (;;) {
        if (equals(cur_hash_table->str, str)) {
            return cur_hash_table->num;
        } else {
            cur_hash_table = cur_hash_table->next_table;
        }
    }
}

int main() {
    freopen("quack.in", "r", stdin);
    freopen("quack.out", "w", stdout);
    new_hash();
    new_queue();
    new_commands();
    char str[N];
    for (;;) {
        scanf("%s", str);
        if (feof(stdin)) {
            break;
        }
        push_command(str);
        //printf("%s\n", ((com.coms + com.size - 1)->str));
        if (*((com.coms + com.size - 1)->str) == ':') {
            char *new_str;
            new_str = ((com.coms + com.size - 1)->str + 1);
            add_string(new_str, (int) (com.size - 1));
        }
    }
    shint reg[26];
    for (int i = 0; i < com.size; i++) {
        if (*((com.coms + i)->str) == '+') {
            long long a = pop();
            long long b = pop();
            push((shint) (a + b));
        } else if (*((com.coms + i)->str) == '-') {
            long long a = pop();
            long long b = pop();
            push((shint) (a - b));
        } else if (*((com.coms + i)->str) == '*') {
            long long a = pop();
            long long b = pop();
            push((shint) (a * b));
        } else if (*((com.coms + i)->str) == '/') {
            long long a = pop();
            long long b = pop();
            if (b != 0) {
                push((shint) (a / b));
            } else {
                push(0);
            }
        } else if (*((com.coms + i)->str) == '%') {
            long long a = pop();
            long long b = pop();
            if (b != 0) {
                push((shint) (a % b));
            } else {
                push(0);
            }
        } else if (*((com.coms + i)->str) == '>') {
            shint a = pop();
            char b = *(((com.coms + i)->str) + 1);
            reg[b - 'a'] = a;
        } else if (*((com.coms + i)->str) == '<') {
            char b = *(((com.coms + i)->str) + 1);
            push(reg[b - 'a']);
        } else if (*((com.coms + i)->str) == 'P') {
            if (mystrlen((com.coms + i)->str) == 1) {
                shint a = pop();
                printf("%hu\n", a);
            } else {
                char b = *(((com.coms + i)->str) + 1);
                shint a = reg[b - 'a'];
                printf("%hu\n", a);
            }
        } else if (*((com.coms + i)->str) == 'C') {
            if (mystrlen((com.coms + i)->str) == 1) {
                shint a = pop();
                printf("%c", (char) (a % 256));
            } else {
                char b = *(((com.coms + i)->str) + 1);
                shint a = reg[b - 'a'];
                printf("%c", (char) (a % 256));
            }
        } else if (*((com.coms + i)->str) == ':') {
            continue;
        } else if (*((com.coms + i)->str) == 'J') {
            char *new_str;
            new_str = ((com.coms + i)->str + 1);
            i = new_i(new_str);
        } else if (*((com.coms + i)->str) == 'Z') {
            char b = *((com.coms + i)->str + 1);
            if (reg[b - 'a'] == 0) {
                char *new_str;
                new_str = ((com.coms + i)->str + 2);
                i = new_i(new_str);
            }
        } else if (*((com.coms + i)->str) == 'E') {
            char b = *((com.coms + i)->str + 1),
                    c = *((com.coms + i)->str + 2);
            if (reg[b - 'a'] == reg[c - 'a']) {
                char *new_str;
                new_str = ((com.coms + i)->str + 3);
                i = new_i(new_str);
            }
        } else if (*((com.coms + i)->str) == 'G') {
            char b = *((com.coms + i)->str + 1),
                    c = *((com.coms + i)->str + 2);
            if (reg[b - 'a'] > reg[c - 'a']) {
                char *new_str;
                new_str = ((com.coms + i)->str + 3);
                i = new_i(new_str);
            }
        } else if (*((com.coms + i)->str) == 'Q') {
            break;
        } else {
            shint y = strToInt((com.coms + i)->str);
            //printf("%s\n", ((com.coms + i)->str));
            push(y);
        }
    }
    return 0;
}