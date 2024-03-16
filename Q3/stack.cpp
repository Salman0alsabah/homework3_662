#include "stack.h"
#include <stdexcept>
#include <iostream>

const int INITIAL_CAPACITY = 10;
const int MAX_STR_LENGTH = 100;

Stack::Stack() : capacity(INITIAL_CAPACITY), size(0) {
    try {
        data = new std::unique_ptr<std::string>[capacity];
    } catch (const std::bad_alloc&) {
        throw std::bad_alloc(); // Throw bad_alloc exception
    }
}

Stack::~Stack() {
    for (int i = 0; i < size; i++) {
        data[i].reset(); // Release the smart pointer
    }
    delete[] data;
}

bool Stack::isEmpty() const {
    return size == 0;
}

int Stack::getSize() const {
    return size;
}

#include "stack.h"
#include <stdexcept>

StackResponse Stack::push(const std::string& str) {
    // Validate the input string pointer if it is not null
    if (str.empty()) {
        throw std::invalid_argument("Invalid input: null string");
    }

    // Check for string length boundary
    if (str.length() > MAX_STR_LENGTH) {
        throw std::invalid_argument("String length exceeds maximum limit");
    }
    
    // Check if the stack is full and try to expand it if necessary
    if (size == capacity) {
        int newCapacity = capacity * 2;
        std::unique_ptr<std::string>* newData;
        try {
            newData = new std::unique_ptr<std::string>[newCapacity];
        } catch (const std::bad_alloc&) {
            throw std::bad_alloc(); // Throw bad_alloc exception
        }
        for (int i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    // Add the string to the stack
    data[size] = std::unique_ptr<std::string>(new std::string(str));
    if (!data[size]) {
        throw std::bad_alloc(); // Throw bad_alloc exception
    }

    // Increment size after successful push
    size++;

    return StackResponse(NO_ERROR);
}

StackResponse Stack::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty"); // Throw out_of_range exception
    }

    // Retrieve the string from the stack
    const char* poppedString = data[size - 1]->c_str();

    // Decrease stack size
    size--;

    // Shrink the stack by one element
    int newCapacity = capacity - 1;
    if (size > 0 && size < capacity) {
        std::unique_ptr<std::string>* newData;
        try {
            newData = new std::unique_ptr<std::string>[newCapacity];
        } catch (const std::bad_alloc&) {
            throw std::bad_alloc(); // Throw bad_alloc exception
        }
        for (int i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        capacity = newCapacity; // Update capacity to reflect the new size
    }

    return StackResponse(NO_ERROR);
}



int handleStackResponse(StackResponse response) {
    if (response.errorCode != NO_ERROR) {
        switch (response.errorCode) {
            case OUT_OF_MEMORY:
                throw std::bad_alloc(); // Throw bad_alloc exception
            case STACK_ELEMENT_TOO_LARGE:
                throw std::length_error("Stack element too large"); // Throw length_error exception
            case STACK_FULL:
                throw std::length_error("Stack full"); // Throw length_error exception
            case STACK_EMPTY:
                throw std::out_of_range("Stack empty"); // Throw out_of_range exception
            default:
                throw std::runtime_error("Unknown error"); // Throw runtime_error exception
        }
    }
    // No error occurred, return 0
    return 0;
}
