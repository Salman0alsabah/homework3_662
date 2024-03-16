#ifndef STACK_H
#define STACK_H

#include <memory>
#include <string>

struct StackResponse {
    int errorCode;
    const char* data;
    StackResponse(int code) : errorCode(code), data(nullptr) {}

};

typedef enum {
    NO_ERROR,              
    OUT_OF_MEMORY,         
    STACK_ELEMENT_TOO_LARGE, 
    STACK_FULL,            
    STACK_EMPTY,         
} StackErrorCode;


class Stack {
private:
    std::unique_ptr<std::string>* data; // Pointer to an array of smart pointers
    int capacity;
    int size;
    static const int INITIAL_CAPACITY = 10;
    static const int MAX_STR_LENGTH = 100; // Example boundary for string length

public:
    Stack();
    ~Stack();

    bool isEmpty() const;
    int getSize() const;
    StackResponse push(const std::string& str);
    StackResponse pop();

private:
    void resize(int newCapacity);
};


int handleStackResponse(StackResponse response);

#endif /* STACK_H */
