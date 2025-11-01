#include <stdio.h>

void push(int stack[], int *top, int maxSize) {
    if (*top == maxSize - 1) {
        printf("Stack Overflow. Cannot push more elements.\n");
        return;
    }
    int value;
    printf("Enter value to push onto stack: ");
    scanf("%d", &value);
    stack[++(*top)] = value;
    printf("Value %d pushed onto stack.\n", value);
}

void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack Underflow. No elements to pop.\n");
        return;
    }
    int poppedValue = stack[(*top)--];
    printf("Value %d popped from stack.\n", poppedValue);
}

void peek(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty. No top element.\n");
        return;
    }
    printf("Top element is: %d\n", stack[top]);
}

void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty. No elements to display.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}

int main() {
    int size;
    printf("Enter the maximum size of the stack: ");
    scanf("%d", &size);
    int stack[size];
    int top = -1;
    int choice = -1;
    do {
        printf("\n--- Stack Operations Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display Stack\n");
        printf("5. Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top, size);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);
}