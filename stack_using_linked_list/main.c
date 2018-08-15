#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

struct node_t{
	int size;
	int data;
	struct node_t * link;
};

struct node_t * create_stack(){
	struct node_t * stack = (struct node_t *)malloc(sizeof(struct node_t));
	// memset(stack, 0x00, sizeof(struct node_t));
	stack->size = 0;
	stack->link = NULL;
	return stack;
}

void delete_stack(struct node_t ** stack){
	struct node_t * node = *stack;
	int i = 0;
	if(node){
		while(node){
			struct node_t * temp = node->link;
			free(node);
			node = temp;
		}
	}
	*stack = NULL;
}

bool stack_push(struct node_t ** stack, int data){
	if(*stack){
		struct node_t * node = create_stack();
		if(node){
			node->data = data;
			node->link = *stack;
			node->size = (*stack)->size + 1;
			*stack = node;
			return true;
		}
	}
	return false;
}

bool stack_is_empty(struct node_t * stack){
	return !(bool)stack->link;
}

int stack_size(struct node_t * stack){
	if(stack)	return stack->size;
	else return 0;
}

int stack_pop(struct node_t ** top){
	struct node_t * node = *top;
	int data = (*top)->data;
	*top = (*top)->link;
	free(node);
	return data;
}

int main(int argc, char const *argv[]){
	struct node_t * stack = create_stack();
	if(stack){
		for(int i = 0; i < 5 ; i++){
			if(stack_push(&stack, i)){
				DEBUG_OK("%dth Element %d Pushed", i, i);
			} else {
				DEBUG_ERROR("Can't Push Element");
			}
		}

		DEBUG_VALUE(stack_size(stack), "%d");
		while(!stack_is_empty(stack)){
			DEBUG_OK("Popped Value : %d", stack_pop(&stack));
		}

		if(!stack_is_empty(stack)){
			DEBUG_OK("Stack Not Empty");
		} else{
			DEBUG_OK("Stack Empty");
		}
		DEBUG_VALUE(stack_size(stack), "%d");
		delete_stack(&stack);
	}
	return 0;
}