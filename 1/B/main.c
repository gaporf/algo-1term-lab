#include <stdio.h>
#include <stdlib.h>

struct list {
    struct list *prev;
    int value;
};

typedef struct list *plist;

plist cur_list = NULL;

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char c;
        scanf(" %c", &c);
        if (c == '+') {
            int num;
            scanf("%d", &num);
            plist new_list = malloc(sizeof(struct list));
            new_list->value = num;
            new_list->prev = cur_list;
            cur_list = new_list;
        } else {
            printf("%d\n", cur_list->value);
            plist prev_list = cur_list->prev;
            free(cur_list);
            cur_list = prev_list;
        }
    }

    return 0;
}