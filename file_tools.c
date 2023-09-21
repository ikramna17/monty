#include "monty.h"

/**
 * open_file - Opens a file for reading.
 * @file_name: The file path.
 * Return: void
 */
void open_file(char *file_name)
{
	FILE *file_descriptor = fopen(file_name, "r");

	if (file_name == NULL || file_descriptor == NULL)
		error_handler(2, file_name);

	read_file(file_descriptor);
	fclose(file_descriptor);
}

/**
 * read_file - Reads lines from a file.
 * @file_descriptor: Pointer to the file descriptor.
 * Return: void
 */
void read_file(FILE *file_descriptor)
{
	int line_number, storage_format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buffer, &len, file_descriptor) != -1; line_number++)
	{
		storage_format = parse_line(buffer, line_number, storage_format);
	}
	free(buffer);
}

/**
 * parse_line - Parses a line into tokens and determines the storage format.
 * @buffer: Line from the file.
 * @line_number: Line number.
 * @storage_format: Storage format. 0 for stack, 1 for queue.
 * Return: Returns 0 if the opcode is "stack", 1 if "queue".
 */
int parse_line(char *buffer, int line_number, int storage_format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		error_handler(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return storage_format;
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return 0;
	if (strcmp(opcode, "queue") == 0)
		return 1;

	find_function(opcode, value, line_number, storage_format);
	return storage_format;
}

/**
 * find_function - Finds the appropriate function for the opcode.
 * @opcode: Opcode.
 * @value: Argument of the opcode.
 * @line_number: Line number.
 * @storage_format: Storage format. 0 for stack, 1 for queue.
 * Return: void
 */
void find_function(char *opcode, char *value, int line_number, int storage_format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", push_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotate_left},
		{"rotr", rotate_right},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_function(func_list[i].f, opcode, value, line_number, storage_format);
			flag = 0;
		}
	}
	if (flag == 1)
		error_handler(3, line_number, opcode);
}

/**
 * call_function - Calls the required function.
 * @func: Pointer to the function to be called.
 * @opcode: String representing the opcode.
 * @value: String representing a numeric value.
 * @line_number: Line number for the instruction.
 * @storage_format: Storage format. 0 for stack, 1 for queue.
 */
void call_function(op_func func, char *opcode, char *value, int line_number, int storage_format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(opcode, "push") == 0)
	{
		if (value != NULL && value[0] == '-')
		{
			value = value + 1;
			flag = -1;
		}
		if (value == NULL)
			error_handler(5, line_number);
		for (i = 0; value[i] != '\0'; i++)
		{
			if (isdigit(value[i]) == 0)
				error_handler(5, line_number);
		}
		node = create_node(atoi(value) * flag);
		if (storage_format == 0)
			func(&node, line_number);
		if (storage_format == 1)
			push_to_queue(&node, line_number);
	}
	else
		func(&head, line_number);
}
