#include <stdio.h>
#include <stdlib.h>

struct list {
    struct list *prev_list;
    int value;
};

typedef struct list *plist;

plist stack = NULL;

void push(int value) {
    plist new_list = malloc(sizeof(struct list));
    new_list->value = value;
    new_list->prev_list = stack;
    stack = new_list;
}

int pop() {
    int ans = stack->value;
    plist prev_list = stack->prev_list;
    free(stack);
    stack = prev_list;
    return ans;
}

int main() {
    char str[500];
    fgets(str, 405, stdin);
    for(int i = 0; str[i]; i++) {
        char c = str[i];
        if (c == ' ') {
            continue;
        }
        if (c == '+') {
            int a = pop(),
                    b = pop();
            push(b + a);
        } else if (c == '-') {
            int a = pop(),
                    b = pop();
            push(b - a);
        } else if (c == '*') {
            int a = pop(),
                    b = pop();
            push(b * a);
        } else if (c >= '0' && c <= '9'){
            int value = c - '0';
            push(value);
        }
    }
    printf("%d", pop());

    return 0;
}