#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10
#define MAX_STR_LENGTH 100

StringStack* create_stack() {
    StringStack* stack = (StringStack*)malloc(sizeof(StringStack));
    if (!stack) {
        return NULL;
    }

    stack->items = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
    if (!stack->items) {
        free(stack);
        exit(OUT_OF_MEMORY);
    }

    stack->capacity = INITIAL_CAPACITY;
    stack->size = 0;
    return stack;
}

void destroy_stack(StringStack* stack) {
    for (int i = 0; i < stack->size; i++) {
        free(stack->items[i]);
    }
    free(stack->items);
    free(stack);
}

int isEmpty(const StringStack* stack) {
    return stack->size == 0;
}

int size(const StringStack* stack) {
    return stack->size;
}


StackResponse push(StringStack* stack, char* str) {
    StackResponse response = {NO_ERROR, NULL};

    // Validate the stack pointer
    if (stack == NULL) {
        response.errorCode = INVALID_STACK;
        return response;
    }

    // Validate the input string pointer
    if (str == NULL) {
        response.errorCode = INVALID_INPUT_NULL;
; 
        return response;
    }

    // Check for string length boundary
    if (strlen(str) > MAX_STR_LENGTH) {
        response.errorCode = STACK_ELEMENT_TOO_LARGE;
        return response;
    }
    
    // Check if the stack is full and try to expand it if necessary
    if (stack->size == stack->capacity) {
        int newCapacity = stack->capacity * 2;
        char** newItems = (char**)realloc(stack->items, newCapacity * sizeof(char*));
        if (!newItems) {
            response.errorCode = OUT_OF_MEMORY;
            return response;
        }
        stack->items = newItems;
        stack->capacity = newCapacity;
    }

    // Duplicate the string and add it to the stack
    stack->items[stack->size] = strdup(str);
    if (!stack->items[stack->size]) {
        response.errorCode = OUT_OF_MEMORY;
        return response;
    }

    // Optionally, return the pushed string
    response.data = stack->items[stack->size];
    stack->size++;
    return response;
}


StackResponse pop(StringStack* stack) {
    StackResponse response = {NO_ERROR, NULL};
    if (isEmpty(stack)) {
        response.errorCode = STACK_EMPTY;
        return response;
    }

    // Free the memory for the popped string
    free(stack->items[stack->size - 1]);

    stack->size--; // Decrease stack size

    // Shrink the stack by one
    if (stack->size > 0) { // Ensure we don't shrink an empty stack
        char** newItems = (char**)realloc(stack->items, stack->size * sizeof(char*));
        if (!newItems) {
            response.errorCode = OUT_OF_MEMORY;
            return response; // Failed to shrink due to memory error, but pop was successful
        }
        stack->items = newItems;
        stack->capacity = stack->size; // Update capacity to reflect the new size
    }

    response.data = NULL; // Since the string is freed, we don't return it
    return response;
}

int handleStackResponse(StackResponse response) {
    if (response.errorCode != NO_ERROR) {
        switch (response.errorCode) {
            case OUT_OF_MEMORY:
                printf("Error: Out of memory\n");
                break;
            case STACK_ELEMENT_TOO_LARGE:
                printf("Error: Stack element too large\n");
                break;
            case STACK_FULL:
                printf("Error: Stack full\n");
                break;
            case STACK_EMPTY:
                printf("Error: Stack empty\n");
                break;
            default:
                printf("Error: Unknown error\n");
        }
        printf("\n");
        return 1; // Indicate an error occurred
    } else {
        if (response.data != NULL) {
            printf("Operation succeeded. Data: %s\n", response.data);
        } else {
            printf("Operation succeeded. No data returned.\n");
        }
        printf("\n");
        return 0; // Indicate success
    }
}
