#include <stdio.h>
#include <stdlib.h>

struct list {
    struct list *next_list;
    int value;
};

typedef struct list *plist;

plist cur_list = NULL, head = NULL;

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
            new_list->next_list = NULL;
            if (head == NULL) {
                head = new_list;
                cur_list = new_list;
            } else {
                cur_list->next_list = new_list;
            }
            cur_list = new_list;
        } else {
            printf("%d\n", head->value);
            plist next_list = head->next_list;
            free(head);
            head = next_list;
        }
    }
    return 0;
}