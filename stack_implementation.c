
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