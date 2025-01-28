/**
 * Stack Implementation using Linked List
 * Created by Aditya Raj
 *
 * ABOUT:
 * This program provides a dynamic implementation of a stack using a singly linked list.
 * The stack is a linear data structure that follows the Last In, First Out (LIFO) principle.
 * The top pointer dynamically manages the stack elements, and the size is maintained as
 * operations are performed. This implementation is suitable for scenarios where the size
 * of the stack is not fixed or known in advance.
 *
 * FEATURES:
 * - **Dynamic Memory Management**: The stack uses a linked list to allocate memory dynamically.
 * - **Push Operation**: Adds an element to the top of the stack.
 * - **Pop Operation**: Removes the top element from the stack.
 * - **Peek Operation**: Retrieves the top element without removing it.
 * - **Stack Traversal**: Prints all elements in the stack from top to bottom.
 * - **Reverse Stack**: Reverses the stack by copying the elements to another stack.
 * - **Search**: Finds an element in the stack and returns its corresponding node pointer.
 * - **Empty Stack**: Clears all elements from the stack.
 * - **Copy Stacks**: Copies the elements of one stack to another stack using an auxiliary stack.
 *
 * USAGE:
 * 1. Initialize a stack using `init_stack()`.
 * 2. Use `push()` to add elements, `pop()` to remove elements, and `peek()` to view the top element.
 * 3. Perform utility operations like reversing, copying, or searching as needed.
 *
 * FUNCTIONS:
 * - `stack* init_stack()`: Initializes a new stack.
 * - `void push(int data, stack* Stack)`: Pushes a new element onto the stack.
 * - `void pop(stack* Stack)`: Removes the top element of the stack.
 * - `int peek(stack* Stack)`: Returns the top element of the stack.
 * - `void print_stack(stack* Stack)`: Prints all elements in the stack.
 * - `void empty_stack(stack* Stack)`: Empties the stack by removing all elements.
 * - `void copy_stacks_aux(stack* source, stack* dest)`: Copies elements of one stack to another.
 * - `void reverse_stack(stack* Stack)`: Reverses the stack order.
 * - `node* search(int value, stack* Stack)`: Searches for a value in the stack and returns the node pointer.
 *
 * EXAMPLE USAGE:
 * ```
 * stack* my_stack = init_stack();
 * push(10, my_stack);
 * push(20, my_stack);
 * printf("Top Element: %d\n", peek(my_stack));  // Output: Top Element: 20
 * print_stack(my_stack);  // Output: 20->10->
 * pop(my_stack);
 * print_stack(my_stack);  // Output: 10->
 * empty_stack(my_stack);
 * ```
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* prev_ptr;

} node;

typedef struct stack{

    node* top_ptr;
    unsigned int size;

} stack;

node* create_node(int data,node* prev_node){
    node* Node = (node*)malloc(sizeof(node));
    if(Node==NULL){
        printf("Memory Allocation Failed!\n");
        exit(2);
    }
    else{
        Node->data = data;
        Node->prev_ptr = prev_node;
        return Node;
    }
}

stack* init_stack(){
    stack* Stack = (stack*)malloc(sizeof(stack));
    if(Stack==NULL){
        printf("Initialisation of stack failed!\n");
        exit(1);
    }
    else{
        Stack->top_ptr =NULL;
        Stack->size = 0;
        return Stack;
    }
}

void push(int data,stack* Stack){
    node* Node = create_node(data,Stack->top_ptr);
    Stack->top_ptr = Node;
    Stack->size = Stack->size+1;
}

void pop(stack* Stack){
    if(Stack->size==0){
        printf("Failed in performing deletion!\n");
    }
    else{
        node* prev_node = Stack->top_ptr->prev_ptr;
        node* temp = Stack->top_ptr;
        Stack->top_ptr = prev_node;
        Stack->size = Stack->size - 1;
        free(temp);
        
    }
}
void print_stack(stack* Stack){
    node* curr_node = Stack->top_ptr;
    while(curr_node!=NULL){
        printf("%d->",curr_node->data);
        curr_node = curr_node->prev_ptr;
    }
    printf("\n");
}

int peek(stack* Stack){
    if(Stack->top_ptr!=NULL){
        return Stack->top_ptr->data;
    }
    else{
        printf("No value at the top!");
        return -1;
    }
}
void empty_stack(stack* Stack){
    node* curr = Stack->top_ptr;
    while(curr!=NULL){
        pop(Stack);
        curr = Stack->top_ptr;
    }

}
void copy_stacks_aux(stack* source, stack* dest){
    //Using Auxillary Stack
    stack* aux_stack = init_stack();
    node* curr = source->top_ptr;
    while(curr!=NULL){
        push(curr->data,aux_stack);
        curr = curr->prev_ptr;
    }
    curr = aux_stack->top_ptr;
    empty_stack(dest);
    while(curr!=NULL){
        push(curr->data,dest);
        curr = curr->prev_ptr;

    }
    empty_stack(aux_stack);
    free(aux_stack);

}

void reverse_stack(stack* Stack){
    stack* rev_stack = init_stack();
    node* curr = Stack->top_ptr;
    while(curr!=NULL){
        push(curr->data,rev_stack);
        curr = curr->prev_ptr;
    }
    copy_stacks_aux(rev_stack, Stack);

}

node* search(int value,stack* Stack){
    node* curr = Stack->top_ptr;
    while(curr!=NULL){
        if(curr->data==value){
            return curr;
            
        }
        curr = curr->prev_ptr;
    }
    return NULL;
}
