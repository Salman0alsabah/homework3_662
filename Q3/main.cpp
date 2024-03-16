#include "stack.h"
#include <iostream>

int main() {
    int errorOccurred = 0; // Local flag to track if any error occurred

    // Create a new stack
    Stack myStack;

    // Check if the stack is initially empty
    if (myStack.isEmpty()) {
        std::cout << "The stack is initially empty." << std::endl;
    } else {
        std::cerr << "Error: The stack should be empty initially." << std::endl;
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
        StackResponse response = myStack.push(stringsToPush[i]);
        errorOccurred = handleStackResponse(response);
        if (errorOccurred) {
            return response.errorCode;  // Abort on error
        }
    }

    std::cout << "Current stack size after pushing: " << myStack.getSize() << std::endl;

    // Pop all items and print them
    while (!myStack.isEmpty()) {
        StackResponse response = myStack.pop();
        errorOccurred = handleStackResponse(response);
        if (errorOccurred) {
            return response.errorCode;  // Abort on error
        }
    }

    // Check if the stack is empty after popping all elements
    if (myStack.isEmpty()) {
        std::cout << "The stack is empty after popping all elements." << std::endl;
    } else {
        std::cerr << "Error: The stack should be empty after popping all elements." << std::endl;
        return -2; // Error code for unexpected stack state after popping
    }

    // Check for overall success
    if (!errorOccurred) {
        std::cout << "Test successful. All operations completed without errors." << std::endl;
    } else {
        std::cout << "Test failed. Errors occurred during operations." << std::endl;
    }

    return 0;
}
