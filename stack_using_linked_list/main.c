#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "debug.h"

struct node_t{
	int data;
	struct node_t * link;
};

struct node_t * create_stack(){
	struct node_t * node = (struct node_t *)malloc(sizeof(struct node_t));
	node->link = NULL;
}

bool stack_push(struct node_t ** stack, int data){
	if(*stack){
		struct node_t * node = create_stack();
		if(node){
			node->data = data;
			node->link = *stack;
			*stack = node;
			return true;
		}
	}
	return false;
}

bool stack_is_empty(struct node_t * stack){
	return !stack;
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
		
		if(stack_push(&stack, 1)){
			DEBUG_OK("Element Pushed");
		}
		if(!stack_is_empty(stack)){
			DEBUG_OK("Stack Not Empty");
		} else{
			DEBUG_OK("Stack Empty");
		}

		stack_push(&stack, 2);
		DEBUG_OK("Popped : %d", stack_pop(&stack));
		if(!stack_is_empty(stack)){
			DEBUG_OK("Stack Not Empty");
		} else{
			DEBUG_OK("Stack Empty");
		}

		DEBUG_OK("Popped : %d", stack_pop(&stack));
	}
	return 0;
}