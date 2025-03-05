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

struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct Node* findMax(struct Node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

int findHeight(struct Node* root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int isBSTUtil(struct Node* root, struct Node* min, struct Node* max) {
    if (root == NULL) {
        return 1;
    }
    if ((min != NULL && root->rollNumber <= min->rollNumber) || 
        (max != NULL && root->rollNumber >= max->rollNumber)) {
        return 0;
    }
    return isBSTUtil(root->left, min, root) && isBSTUtil(root->right, root, max);
}

int isValidBST(struct Node* root) {
    return isBSTUtil(root, NULL, NULL);
}

struct Node* mirror(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }
    struct Node* temp = root->left;
    root->left = mirror(root->right);
    root->right = mirror(temp);
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
    int numbers[] = {8, 3, 10, 1, 6, 14, 13, 7, 4};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < n; i++) {
        root = insert(root, numbers[i]);
    }
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");
    printf("Minimum: %d\n", findMin(root)->rollNumber);
    printf("Maximum: %d\n", findMax(root)->rollNumber);
    printf("Height: %d\n", findHeight(root));
    printf("Is Valid BST: %s\n", isValidBST(root) ? "Yes" : "No");
    root = mirror(root);
    printf("Inorder of Mirror Image: ");
    inorder(root);
    printf("\n");
    freeBST(root);
    return 0;
}
