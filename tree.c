#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

typedef struct tree {
    node* root;
} tree;
typedef struct Queue {
    node** arr;
    int front, rear, size;
} Queue;
node* create_node(int value) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

tree* init_tree() {
    tree* newTree = (tree*)malloc(sizeof(tree));
    newTree->root = NULL;
    return newTree;
}

node* build_from_pre_in(int preorder[], int inorder[], int* preIndex, int inStart, int inEnd) {
    if (inStart > inEnd) return NULL;
    node* root = create_node(preorder[*preIndex]);
    (*preIndex)++;
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == root->data) break;
    }
    root->left = build_from_pre_in(preorder, inorder, preIndex, inStart, inIndex - 1);
    root->right = build_from_pre_in(preorder, inorder, preIndex, inIndex + 1, inEnd);
    return root;
}

void build_tree_pre_in(tree* t, int preorder[], int inorder[], int n) {
    int preIndex = 0;
    t->root = build_from_pre_in(preorder, inorder, &preIndex, 0, n - 1);
}

node* build_from_post_in(int postorder[], int inorder[], int* postIndex, int inStart, int inEnd) {
    if (inStart > inEnd) return NULL;
    node* root = create_node(postorder[*postIndex]);
    (*postIndex)--;
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == root->data) break;
    }
    root->right = build_from_post_in(postorder, inorder, postIndex, inIndex + 1, inEnd);
    root->left = build_from_post_in(postorder, inorder, postIndex, inStart, inIndex - 1);
    return root;
}

void build_tree_post_in(tree* t, int postorder[], int inorder[], int n) {
    int postIndex = n - 1;
    t->root = build_from_post_in(postorder, inorder, &postIndex, 0, n - 1);
}



Queue* create_queue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (node**)malloc(size * sizeof(node*));
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

int is_empty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, node* n) {
    if (n) q->arr[q->rear++] = n;
}

node* dequeue(Queue* q) {
    if (is_empty(q)) return NULL;
    return q->arr[q->front++];
}

void print_tree(node* root) {
    if (root == NULL) return;
    Queue* q = create_queue(MAX_NODES);
    enqueue(q, root);
    while (!is_empty(q)) {
        int level_size = q->rear - q->front;
        for (int i = 0; i < level_size; i++) {
            node* current = dequeue(q);
            printf("%d ", current->data);
            enqueue(q, current->left);
            enqueue(q, current->right);
        }
        printf("\n");
    }
    free(q->arr);
    free(q);
}

void inorder_traversal(node* root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

void preorder_traversal(node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void postorder_traversal(node* root) {
    if (root == NULL) return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->data);
}

int main() {
    tree* tree1 = init_tree();
    tree* tree2 = init_tree();

    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int inorder[]  = {4, 2, 5, 1, 6, 3, 7};
    int n1 = sizeof(preorder) / sizeof(preorder[0]);
    build_tree_pre_in(tree1, preorder, inorder, n1);
    print_tree(tree1->root);
    printf("Inorder: ");
    inorder_traversal(tree1->root);
    printf("\nPreorder: ");
    preorder_traversal(tree1->root);
    printf("\nPostorder: ");
    postorder_traversal(tree1->root);
    printf("\n");

    int postorder[] = {4, 5, 2, 6, 7, 3, 1};
    int n2 = sizeof(postorder) / sizeof(postorder[0]);
    build_tree_post_in(tree2, postorder, inorder, n2);
    print_tree(tree2->root);
    printf("Inorder: ");
    inorder_traversal(tree2->root);
    printf("\nPreorder: ");
    preorder_traversal(tree2->root);
    printf("\nPostorder: ");
    postorder_traversal(tree2->root);
    printf("\n");
    
    free(tree1);
    free(tree2);
    return 0;
}
