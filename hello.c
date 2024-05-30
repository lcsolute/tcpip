#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node * next;
};

struct Node * head;

void remove_list_entry(struct Node * entry)
{
    struct Node ** indirect;
    indirect = &head;
    while ((*indirect) != entry)
        indirect = &(*indirect) -> next;


    *indirect = entry->next;
}

int main(void) {
    struct Node * p = NULL, *entry;
    for (int i = 0; i < 10; i++) {
        struct Node * q = (struct Node *)malloc(sizeof(struct Node));
        q->data = i;
        q->next = p;
        p = q;
        if (i == 3) entry = q;
    }
    head = p;
    remove_list_entry(entry);
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    return 0;
}
