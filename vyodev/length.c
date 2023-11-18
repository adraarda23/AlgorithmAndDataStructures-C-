#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int findLength(struct Node* head) {
    return (head == NULL) ? 0 : 1 + findLength(head->next);
}
int main() {
    struct Node* head = NULL;

    for (int i = 5; i > 0; --i) { //test case
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = i;
        newNode->next = head;
        head = newNode;
    }
    int length = findLength(head);
    printf("Linked List Uzunlugu: %d\n", length);

    return 0;
}
