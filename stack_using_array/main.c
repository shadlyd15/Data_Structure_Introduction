#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"

struct stack_t{
	int top;
	int size;
	int * array;
};

struct stack_t * create_stack(int size){
	struct stack_t * stack = (struct stack_t *)malloc(sizeof(struct stack_t));
	if(stack){
		stack->array = (int*)malloc(sizeof(int) * size);
		if(stack->array){
			stack->size = size;
			stack->top = -1;			
		} else {
			free(stack);
			stack = NULL;
		}
	}
	return stack;
}

bool stack_push(struct stack_t * stack, int data){
	if(stack){
		if(stack->top < stack->size){
			stack->array[++stack->top] = data;
			return true;
		}
	}
	return false;
}

bool stack_is_empty(struct stack_t * stack){
	return (stack && stack->top < 0) ? true : false;
}

int stack_pop(struct stack_t * stack){
	if(stack && !stack_is_empty(stack)){
		return stack->array[stack->top--];
	}
	return 0;
}

int stack_available(struct stack_t * stack){
	return (stack && !stack_is_empty(stack)) ? (stack->top + 1) : 0;
}

int main(int argc, char const *argv[]){
	DEBUG_OK("Stack Using Array Example");
	struct stack_t * stack = create_stack(5);
	stack_push(stack, 1);
	stack_push(stack, 2);
	stack_push(stack, 4);
	stack_push(stack, 3);

	DEBUG_OK("stack_available : %d", stack_available(stack));
	while(stack_available(stack)){
		DEBUG_OK("Popped : %d", 	stack_pop(stack));
	}

	if(stack_is_empty(stack)){
		DEBUG_OK("stack_is_empty");
	}
	return 0;
}