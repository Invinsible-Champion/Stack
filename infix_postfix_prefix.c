#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    char data;
    struct Node* next;
};

void push(struct Node** top, char c) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = c;
    newNode->next = *top;
    *top = newNode;
}

char pop(struct Node** top) {
    if (*top == NULL) return -1;
    struct Node* temp = *top;
    char data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void infixToPostfix(char* infix, char* postfix) {
    struct Node* stack = NULL;
    size_t k = 0;
    for (size_t i = 0; i < strlen(infix); i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(&stack, c);
        } else if (c == ')') {
            while (stack != NULL && stack->data != '(') {
                postfix[k++] = pop(&stack);
            }
            pop(&stack);
        } else if (isOperator(c)) {
            while (stack != NULL && precedence(stack->data) >= precedence(c)) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, c);
        }
    }
    while (stack != NULL) {
        postfix[k++] = pop(&stack);
    }
    postfix[k] = '\0';
}

void infixToPrefix(char* infix, char* prefix) {
    char reversed[MAX], temp[MAX];
    size_t len = strlen(infix);
    for (size_t i = 0; i < len; i++) {
        reversed[i] = infix[len - 1 - i];
        if (reversed[i] == '(') reversed[i] = ')';
        else if (reversed[i] == ')') reversed[i] = '(';
    }
    reversed[len] = '\0';
    infixToPostfix(reversed, temp);
    size_t tempLen = strlen(temp);
    for (size_t i = 0; i < tempLen; i++) {
        prefix[i] = temp[tempLen - 1 - i];
    }
    prefix[tempLen] = '\0';
}

void postfixToInfix(char* postfix, char* result) {
    struct Node* stack = NULL;
    size_t k = 0;
    for (size_t i = 0; i < strlen(postfix); i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            push(&stack, c);
        } else if (isOperator(c)) {
            char operand2 = pop(&stack);
            char operand1 = pop(&stack);
            result[k++] = '(';
            result[k++] = operand1;
            result[k++] = c;
            result[k++] = operand2;
            result[k++] = ')';
            result[k] = '\0';
            push(&stack, result[k-3]);
        }
    }
}

void postfixToPrefix(char* postfix, char* result) {
    struct Node* stack = NULL;
    size_t k = 0;
    for (size_t i = 0; i < strlen(postfix); i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            push(&stack, c);
        } else if (isOperator(c)) {
            char operand2 = pop(&stack);
            char operand1 = pop(&stack);
            result[k++] = c;
            result[k++] = operand1;
            result[k++] = operand2;
            result[k] = '\0';
            push(&stack, result[k-3]);
        }
    }
}

void prefixToInfix(char* prefix, char* result) {
    struct Node* stack = NULL;
    size_t len = strlen(prefix);
    for (int i = len - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isalnum(c)) {
            push(&stack, c);
        } else if (isOperator(c)) {
            char operand1 = pop(&stack);
            char operand2 = pop(&stack);
            result[0] = '(';
            result[1] = operand1;
            result[2] = c;
            result[3] = operand2;
            result[4] = ')';
            result[5] = '\0';
            push(&stack, result[1]);
        }
    }
}

void prefixToPostfix(char* prefix, char* result) {
    struct Node* stack = NULL;
    size_t len = strlen(prefix);
    size_t k = 0;

    for (int i = len - 1; i >= 0; i--) {
        char c = prefix[i];
        
        if (isalnum(c)) {
            push(&stack, c);
        } else if (isOperator(c)) {
            char operand1 = pop(&stack);
            char operand2 = pop(&stack);
            result[k++] = operand1;
            result[k++] = operand2;
            result[k++] = c;
            result[k] = '\0';
            push(&stack, result[k-3]);
        }
    }

    while (stack != NULL) {
        result[k++] = pop(&stack);
    }
    result[k] = '\0';
}

int main() {
    char postfix[MAX], prefix[MAX], result[MAX];
    char* infixExpr = "A+B*(C-D)";
    
    printf("Infix: %s\n", infixExpr);

    infixToPostfix(infixExpr, postfix);
    printf("Postfix: %s\n", postfix);

    infixToPrefix(infixExpr, prefix);
    printf("Prefix: %s\n", prefix);

    postfixToInfix(postfix, result);
    printf("Postfix to Infix: %s\n", result);

    postfixToPrefix(postfix, result);
    printf("Postfix to Prefix: %s\n", result);

    prefixToInfix(prefix, result);
    printf("Prefix to Infix: %s\n", result);

    prefixToPostfix(prefix, result);
    printf("Prefix to Postfix: %s\n", result);

    return 0;
}
