#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define T int

void panic(char message[]) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

typedef struct ListNode_t {
    T value;
    struct ListNode_t* next;
} ListNode;

ListNode* node_init(int value) {
    ListNode* node = malloc(sizeof(ListNode));
    if (node == NULL) {
        panic("Malloc failed");
    }
    node->value = value;
    return node;
}

typedef struct LinkedList {
    int length;
    ListNode* head;
} LinkedList;

LinkedList list_init() {
    LinkedList list = {
        .length = 0,
        .head = NULL,
    };
    return list;
}

void list_free(LinkedList list) {
    ListNode* node = list.head;
    while (node != NULL) {
        ListNode* node_to_free = node;
        node = node->next;
        free(node_to_free);
    }
}

void list_push(LinkedList* list, int value) {
    ListNode* node = node_init(value);

    if (list->length == 0) {
        list->head = node;
    } else {
        ListNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
    list->length++;
}

int list_pop(LinkedList* list) {
    ListNode* node;

    if (list->length == 0) {
        panic("Collection is empty");
    }

    if (list->length == 1) {
        node = list->head;
    } else {
        ListNode* current = list->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        node = current->next;
        current->next = NULL;
    }

    int value = node->value;
    free(node);
    list->length--;
    return value;
}

void list_print(LinkedList list) {
    printf("[");
    if (list.head != NULL) {
        ListNode* current = list.head;
        printf("%d", current->value);
        while (current->next != NULL) {
            current = current->next;
            printf(", %d", current->value);
        }
    }
    printf("]\n");
}

int main() {
    LinkedList list = list_init();
    for (int i = 0; i < 10; ++i) {
        list_push(&list, i);
    }
    list_print(list);
    printf("popped %d\n", list_pop(&list));
    list_print(list);
    list_free(list);
}
