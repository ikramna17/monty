#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/**
 * struct StackNode - Doubly linked list representation of a stack (or queue)
 * @data: Integer value stored in the node
 * @prev: Points to the previous element in the stack (or queue)
 * @next: Points to the next element in the stack (or queue)
 *
 * Description: Structure for a doubly linked list node used for stacks and queues
 *              Supports LIFO and FIFO operations.
 */
typedef struct StackNode
{
        int data;
        struct StackNode *prev;
        struct StackNode *next;
} StackNode;

/**
 * struct Instruction - Opcode and its corresponding function
 * @opcode: The opcode as a string
 * @func: Pointer to the function that handles the opcode
 *
 * Description: Structure defining an opcode and its associated function
 *              for stack and queue operations.
 */
typedef struct Instruction
{
        char *opcode;
        void (*func)(StackNode **stack, unsigned int line_number);
} Instruction;

extern StackNode *head;
typedef void (*OperationFunc)(StackNode **, unsigned int);

/* File operations */
void open_file(char *file_name);
int parse_line(char *buffer, int line_number, int format);
void read_file(FILE *);
int count_chars(FILE *);
void find_function(char *, char *, int, int);

/* Stack operations */
StackNode *create_node(int data);
void free_nodes(void);
void print_stack(StackNode **stack, unsigned int line_number);
void push_to_stack(StackNode **stack, unsigned int line_number);
void push_to_queue(StackNode **stack, unsigned int line_number);

void execute_function(OperationFunc, char *, char *, int, int);

void print_top(StackNode **stack, unsigned int line_number);
void pop_top(StackNode **stack, unsigned int line_number);
void nop(StackNode **stack, unsigned int line_number);
void swap_nodes(StackNode **stack, unsigned int line_number);

/* Mathematical operations with nodes */
void add_nodes(StackNode **stack, unsigned int line_number);
void subtract_nodes(StackNode **stack, unsigned int line_number);
void divide_nodes(StackNode **stack, unsigned int line_number);
void multiply_nodes(StackNode **stack, unsigned int line_number);
void modulo_nodes(StackNode **stack, unsigned int line_number);

/* String operations */
void print_character(StackNode **stack, unsigned int line_number);
void print_string(StackNode **stack, unsigned int line_number);
void rotate_left(StackNode **stack, unsigned int line_number);

/* Error handling */
void handle_error(int error_code, ...);
void handle_more_error(int error_code, ...);
void handle_string_error(int error_code, ...);
void rotate_right(StackNode **stack, unsigned int line_number);

#endif

