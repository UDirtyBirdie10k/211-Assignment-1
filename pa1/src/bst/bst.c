#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

/* Create a new tree node */
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* Insert a node into the tree */
void insert(TreeNode** tree, int value) {
    if (*tree == NULL) {
        *tree = createNode(value);
        printf("inserted\n"); // Print "inserted" when a new node is created
    } else if (value < (*tree)->data) {
        insert(&((*tree)->left), value);
    } else if (value > (*tree)->data) {
        insert(&((*tree)->right), value);
    } else {
        printf("not inserted\n"); // Value already exists
    }
}

/* Search for a node in the tree */
int search(TreeNode* tree, int value) {
    if (tree == NULL) {
        // printf("absent\n");
        return 0; // Value is absent
    }
    if (value == tree->data) {
        // printf("present\n");
        return 1; // Value is present
    } else if (value < tree->data) {
        return search(tree->left, value);
    } else {
        return search(tree->right, value);
    }
}

void print(TreeNode* tree) {
    if (tree == NULL) {
        return;
    }
    printf("(");
    print(tree->left);
    printf("%d", tree->data);
    print(tree->right);
    printf(")");
}

TreeNode* findMin(TreeNode* tree) {
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

TreeNode* delete(TreeNode* tree, int value) {
    if (tree == NULL) {
        return tree;
    }
    if (value < tree->data) {
        tree->left = delete(tree->left, value);
    } else if (value > tree->data) {
        tree->right = delete(tree->right, value);
    } else {
        if (tree->left == NULL) {
            TreeNode* temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            TreeNode* temp = tree->left;
            free(tree);
            return temp;
        }
        TreeNode* temp = findMin(tree->right);
        tree->data = temp->data;
        tree->right = delete(tree->right, temp->data);
    }
    return tree;
}


void freeTree(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main(int argc, char* argv[]) {
    TreeNode* root = NULL;
    char input;
    int value;
    
    while (scanf(" %c", &input) != EOF) {

        if (input == 'i') {
            scanf("%d", &value);
            insert(&root, value);
        } 
        if (input == 's') {
            scanf("%d", &value);
            if(search(root, value)){
                printf("present\n");
            }
            else{
                printf("absent\n");

            }
        } 
        if (input == 'p') {
            if (root != NULL) {
                print(root);
            }
            printf("\n");
        }
        if (input == 'd') {
            scanf("%d", &value);
            if(search(root, value)){
                root = delete(root, value);
                printf("deleted\n");
            }
            else{
                printf("absent\n");

            }
        } 
    }
freeTree(root);

    return 0;
}

