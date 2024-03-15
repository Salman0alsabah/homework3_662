#include "stack.h"
#include <stdio.h>
#include <stdlib.h>



int main() {

    int errorOccurred = 0; // Local flag to track if any error occurred

    // Create a new stack
    StringStack* myStack = create_stack();
    if (!myStack) {
        printf("Failed to create stack. Out of memory.\n");
        return OUT_OF_MEMORY;
    }

    // Check if the stack is initially empty
    if (isEmpty(myStack)) {
        printf("The stack is initially empty.\n");
    } else {
        printf("Error: The stack should be empty initially.\n");
        destroy_stack(myStack);
        return -1; // Error code for unexpected stack state
    }

    // Push strings onto the stack
    const char* stringsToPush[] = {
        "First", "Second", "Third", "Fourth", "Fifth",
        "Sixth", "Seventh", "Eighth", "Ninth", "Tenth",
        "Eleventh"  // This one should trigger the expandability feature
    };
    int numStrings = sizeof(stringsToPush) / sizeof(stringsToPush[0]);

    for (int i = 0; i < numStrings; ++i) {
        StackResponse response = push(myStack, (char*)stringsToPush[i]);
        handleStackResponse(response);
        if (errorOccurred) {
            destroy_stack(myStack);
            return response.errorCode;  // Abort on error
        }
    }

    printf("Current stack size after pushing: %d\n", size(myStack));

    // Pop all items and print them
    while (!isEmpty(myStack)) {
        StackResponse response = pop(myStack);
        handleStackResponse(response);
        if (errorOccurred) {
            destroy_stack(myStack);
            return response.errorCode;  // Abort on error
        }
    }

    // Check if the stack is empty after popping all elements
    if (isEmpty(myStack)) {
        printf("The stack is empty after popping all elements.\n");
    } else {
        printf("Error: The stack should be empty after popping all elements.\n");
        destroy_stack(myStack);
        return -2; // Error code for unexpected stack state after popping
    }

    // Clean up and destroy the stack
    destroy_stack(myStack);

    // Check for overall success
    if (!errorOccurred) {
        printf("Test successful. All operations completed without errors.\n");
    } else {
        printf("Test failed. Errors occurred during operations.\n");
    }

    return 0;
}
