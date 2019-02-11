#include <stdio.h>
#include <stdlib.h>

const int N = 200000;

struct list {
    struct list *prev_list;
    char value;
};

typedef struct list *plist;

plist stack;

int empty() {
    return stack == NULL;
}

char top() {
    return stack->value;
}

void pop() {
    plist prev_list = stack->prev_list;
    free(stack);
    stack = prev_list;
}

void push(char num) {
    plist new_list = malloc(sizeof(struct list));
    new_list->value = num;
    new_list->prev_list = stack;
    stack = new_list;
}

int main() {
    char str[N];
    for(;;) {
        fgets(str, N, stdin);
        if (feof(stdin)) {
            break;
        }
        /*stack = NULL;
        for (int i = 0; str[i]; i++) {
            if (empty()) {
                push(str[i]);
            } else {
                char y = top();
                if ((y == '(' && str[i] == ')') || (y == '[' && str[i] == ']')) {
                    pop();
                } else {
                    push(str[i]);
                }
            }
        }
        if (empty()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }*/
    }

    return 0;
}