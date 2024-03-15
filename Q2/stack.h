// stack.h
#ifndef STACK_H
#define STACK_H


// capacity is at 10 

typedef struct {
    char** items;
    int capacity;
    int size;
} StringStack;

typedef enum {
    NO_ERROR,              
    OUT_OF_MEMORY,         
    STACK_ELEMENT_TOO_LARGE, 
    STACK_FULL,            
    STACK_EMPTY,
    INVALID_STACK,
    INVALID_INPUT_NULL           
} StackErrorCode;

typedef struct {
    StackErrorCode errorCode; 
    char* data;               
} StackResponse;

// Function prototypes
int handleStackResponse(StackResponse response);
StringStack* create_stack();
void destroy_stack(StringStack* stack);
int isEmpty(const StringStack* stack);
int size(const StringStack* stack);
StackResponse push(StringStack* stack, char* str);
StackResponse pop(StringStack* stack);

#endif // STACK_H
