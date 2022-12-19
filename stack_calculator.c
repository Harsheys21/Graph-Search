#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack_calculator.h"


// Allocate a new Stack struct and return a pointer to it.
Stack *stack_create(void) {
  // this one is complete, no need to change it!
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {
  // your code here
  //  Also, do I check if value is a calculator value #question
  if(sizeof(Stack) > sizeof(s) || item.type != NUMBER){
    return false;
  }

  Node *output = (Node *)malloc(sizeof(Node));
  output->item = item;
  output->next = s->top;
  s->top = output;
  return true;
}

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {
  // your code here
  if(s->top == NULL){
    return false;
  }
  *output = s->top->item;
  // do i free up the space for the popped value. Also, do I check if value is a calculator value #question
  Node *foo = s->top;
  s->top = s->top->next;
  free(foo);
  return true;
}

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
  if(s->top == NULL){
    return true;
  }
  return false;
}

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {
  
  while(!stack_empty(*s)){
    Node *foo = (*s)->top;
    (*s)->top = (*s)->top->next;
    free(foo);
  }
  free(*s);
  *s = NULL;
}

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {
  // your code here
  CalculatorItem input1;
  bool value;

  if(item.type == NUMBER){
    input1.value = item.value;
    input1.type = NUMBER;
    value = stack_push(s, input1);
    if(value){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    CalculatorItem input2;

    if(item.type == ADD){
      value = stack_pop(s, &input1);
      if(!value){
        return false;
      }

      value = stack_pop(s, &input2);
      if(!value){
        return false;
      }

      input1.value += input2.value;
    }


    if(item.type == SUBTRACT){
      value = stack_pop(s, &input1);
      if(!value){
        return false;
      }

      value = stack_pop(s,&input2);
      if(!value){
        return false;
      }

      input1.value = input2.value - input1.value;
    }


    if(item.type == MULTIPLY){
      value = stack_pop(s, &input1);
      if(!value){
        return false;
      }

      value = stack_pop(s, &input2);
      if(!value){
        return false;
      }

      input1.value *= input2.value;
    }


    if(item.type == DIVIDE){
      value = stack_pop(s, &input1);
      if(!value){
        return false;
      }

      value = stack_pop(s, &input2);
      if(!value){
        return false;
      }

      input1.value = input2.value/input1.value;
    }

    stack_push(s, input1);
    return true;
  }

  return false;
}
