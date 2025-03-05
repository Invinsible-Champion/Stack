#include <stdio.h>
#include <stdlib.h>

struct Node {
    int rollNumber;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int rollNumber) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->rollNumber = rollNumber;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int rollNumber) {
    if (root == NULL) {
        return createNode(rollNumber);
    }
    if (rollNumber < root->rollNumber) {
        root->left = insert(root->left, rollNumber);
    } else if (rollNumber > root->rollNumber) {
        root->right = insert(root->right, rollNumber);
    }
    return root;
}

struct Node* search(struct Node* root, int rollNumber) {
    if (root == NULL || root->rollNumber == rollNumber) {
        return root;
    }
    if (rollNumber < root->rollNumber) {
        return search(root->left, rollNumber);
    }
    return search(root->right, rollNumber);
}

struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct Node* deleteNode(struct Node* root, int rollNumber) {
    if (root == NULL) {
        return root;
    }
    if (rollNumber < root->rollNumber) {
        root->left = deleteNode(root->left, rollNumber);
    } else if (rollNumber > root->rollNumber) {
        root->right = deleteNode(root->right, rollNumber);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMin(root->right);
        root->rollNumber = temp->rollNumber;
        root->right = deleteNode(root->right, temp->rollNumber);
    }
    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->rollNumber);
        inorder(root->right);
    }
}

void freeBST(struct Node* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, rollNumber;
    
    while (1) {
        printf("\nStudent Roll Number Management System\n");
        printf("1. Insert Roll Number\n");
        printf("2. Delete Roll Number\n");
        printf("3. Search for Roll Number\n");
        printf("4. Display BST (Sorted Order)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter roll number to insert: ");
                scanf("%d", &rollNumber);
                root = insert(root, rollNumber);
                break;
            case 2:
                printf("Enter roll number to delete: ");
                scanf("%d", &rollNumber);
                root = deleteNode(root, rollNumber);
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &rollNumber);
                if (search(root, rollNumber) != NULL)
                    printf("Roll number %d found in BST.\n", rollNumber);
                else
                    printf("Roll number %d not found in BST.\n", rollNumber);
                break;
            case 4:
                printf("Roll numbers in sorted order: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                freeBST(root);
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
