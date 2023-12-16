#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/*Create a new node*/
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/*Insert a node at the beginning of the list*/
void insertBegin(Node** root, int value) {
    Node* newNode = createNode(value);
    newNode->next = *root;
    *root = newNode;
}

/*Insert a node at the end of the list*/
void insertEnd(Node** root, int value) {
    Node* newNode = createNode(value);
    if (*root == NULL) {
        *root = newNode;
    } else {
        Node* curr = *root;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}


/*Insert a node into a sorted list (avoid duplicates)*/
void insertSorted(Node** root, int value) {
    if (*root == NULL) {
        insertBegin(root, value); 
    } else if (value < (*root)->data) {
        insertBegin(root, value); 
    } else if (value > (*root)->data) {
        Node* curr = *root;
        while (curr->next != NULL) {
            if (value < curr->next->data) {
                break;
            } else if (value == curr->next->data) {
                return; 
            }
            curr = curr->next;
        }
        if (curr->next == NULL || value != curr->next->data) {
            
            Node* newNode = createNode(value);
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }
}



/*Delete a node with the given value from the list*/
void deleteNode(Node** root, int value) {
    if (*root == NULL) {
        return;
    }

    if ((*root)->data == value) {
        Node* toRemove = *root;
        *root = (*root)->next;
        free(toRemove);
        return;
    }

    Node* curr = *root;
    while (curr->next != NULL) {
        if (curr->next->data == value) {
            Node* toRemove = curr->next;
            curr->next = curr->next->next;
            free(toRemove);
            return;
        }
        curr = curr->next;
    }
}

/*Free the memory allocated for the list*/
void freeList(Node** root) {
    while (*root != NULL) {
        Node* toRemove = *root;
        *root = (*root)->next;
        free(toRemove);
    }
}

int main() {
    Node* root = NULL;
    char input;
    int value;

    while (1) {
        if (scanf(" %c %d", &input, &value) != 2) {
            break; 
        }

        if (input == 'i') {
            insertSorted(&root, value);
        } else if (input == 'd') {
            deleteNode(&root, value);
        }

        Node* current = root;
        int count = 0;

        while (current != NULL) {

            count++;
            current = current->next;
            
        }

        printf("%d :", count);

        current = root;

        while(current != NULL){

            printf(" %d", current->data);
            current = current->next;

        }
        printf("\n");

    }

    freeList(&root);

    return 0;
}

