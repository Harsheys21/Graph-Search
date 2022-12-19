Before starting the assignment, I took the time to essentially look over the structs and understand the Stack process. Starting with the push function, I first checked if there was enough memory in stack and if a number was being pushed. After checking, I essentially allocated some heap using malloc got the size of Node. After allocationg that space, I set Calculator item to item and set the next to the former top of Stack. I then set stack top to the pushed Node.

For pop, I first checked if top was null. If not, then i set output to the popped value and then set the next node to top for stack. Finally, I freed the former top node.

Stack_empty was a simple if statment checking if top was equal to null. If not, false was returned. 

Stack_delete essentially used stack_empty to check if the stack was empty for the while loop conditional. In the while loop. I referenced the pop function from the demo and used stack memory to free the heap memory. After the while loop, I finally freed the stack using free(*s). I used the asterisk since the parameter has two asterisks meaning that it was a pointer to a pointer.

For compute_step, I first initialized a local CalculatorItem struct called input1. I then used an if statment to check if a number or an operation was being added. If number, input1 values would be equal to item and it would be added to the stack using stack_push. If stack_push would fail, then false would be returned. If operation, I would check the operation using an if statement, commence the operation and save the value into input1 and then push input1 using stack_push. If stack_push would fail, then false would be returned. If the item was neither number or operand, then false would be returned. 
