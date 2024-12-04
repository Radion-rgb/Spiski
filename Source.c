
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIST_SIZE 100000
#define NUM_INSERTIONS 1000

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void fillArrayList(int* list, int size);
void fillLinkedList(Node** head, int size);
void comparePerformanceArrayList(int* list);
void comparePerformanceLinkedList(Node* head);
void insertAtBeginningLinkedList(Node** head, int value);
void insertAtEndLinkedList(Node** head, int value);
void insertAtMiddleLinkedList(Node** head, int value, int size);

int main() {
    int* arrayList = (int*)malloc(LIST_SIZE * sizeof(int));
    Node* linkedList = NULL;

    fillArrayList(arrayList, LIST_SIZE);
    fillLinkedList(&linkedList, LIST_SIZE);

    comparePerformanceArrayList(arrayList);
    comparePerformanceLinkedList(linkedList);

    free(arrayList);
    // Free linked list memory
    Node* temp;
    while (linkedList != NULL) {
        temp = linkedList;
        linkedList = linkedList->next;
        free(temp);
    }

    return 0;
}

void fillArrayList(int* list, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        list[i] = rand() % size;
    }
}

void fillLinkedList(Node** head, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        insertAtEndLinkedList(head, rand() % size);
    }
}

void comparePerformanceArrayList(int* list) {
    printf("Performance for ArrayList\n");

    // Random Access
    clock_t start = clock();
    for (int i = 0; i < LIST_SIZE; i++) {
        int value = list[i];
    }
    clock_t end = clock();
    printf("Random Access: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // Sequential Access
    start = clock();
    for (int i = 0; i < LIST_SIZE; i++) {
        int value = list[i];
    }
    end = clock();
    printf("Sequential Access: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // Insertion at Beginning
    start = clock();
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        for (int j = LIST_SIZE - 1; j > 0; j--) {
            list[j] = list[j - 1];
        }
        list[0] = i;
    }
    end = clock();
    printf("Insertion at Beginning: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // Insertion at End
    start = clock();
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        list[LIST_SIZE - 1] = i;
    }
    end = clock();
    printf("Insertion at End: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // Insertion in Middle
    start = clock();
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        for (int j = LIST_SIZE - 1; j > LIST_SIZE / 2; j--) {
            list[j] = list[j - 1];
        }
        list[LIST_SIZE / 2] = i;
    }
    end = clock();
    printf("Insertion in Middle: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    printf("\n");
}

void comparePerformanceLinkedList(Node* head) {
    printf("Performance for LinkedList\n");

    // Random Access
    clock_t start = clock();
    Node* current = head;
    for (int i = 0; i < LIST_SIZE; i++) {
        current = head;
        for (int j = 0; j < i; j++) {
            current = current->next;
        }
        int value = current->data;
    }
    clock_t end = clock();
    printf("Random Access: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // Sequential Access
    start = clock();
    current = head;
    while (current != NULL) {
        int value = current->data;
        current = current->next;
    }
    end = clock();
    printf("Sequential Access: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // Insertion at Beginning
    start = clock();
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        insertAtBeginningLinkedList(&head, i);
    }
    end = clock();
    printf("Insertion at Beginning: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // Insertion at End
    start = clock();
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        insertAtEndLinkedList(&head, i);
    }
    end = clock();
    printf("Insertion at End: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);


        // Insertion in Middle
        start = clock();
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        insertAtMiddleLinkedList(&head, i, LIST_SIZE);
    }
    end = clock();
    printf("Insertion in Middle: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    printf("\n");
}

void insertAtBeginningLinkedList(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void insertAtEndLinkedList(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void insertAtMiddleLinkedList(Node** head, int value, int size) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        Node* current = *head;
        for (int i = 0; i < size / 2 - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}