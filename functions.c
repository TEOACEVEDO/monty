#include "monty.h"

/**
 * open_file - Function that open, read and execute.
 * @argv: arguments
 * Return: void
 **/

void open_file(char **argv)
{
	FILE *m = NULL;
	char *buf = NULL, *token = NULL;
	size_t len = 0;
	int line = 1;
	stack_t *stack = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);

	m = fopen(argv[1], "r");
	if (m == NULL)
	{
		open_error(argv);
	}

	for (line = 1; getline(&buf, &len, m) != -1; line++)
	{
		f = get_op_code(buf, line);
		if (f == NULL)
				(line, strtok(buf, " "));
		else
			f(&stack, line);
	}

	fclose(m);
	free(buf);
	free_all(&stack);
	(void)token;
}

/**
 * push (add) node to list.
 * @stack: element at the top of the stack.
 * @line_number: constant int value in the structure
 * Return: void
 **/
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;

	new_node = (stack_t *)malloc(sizeof(stack_t));
	if (new_node == NULL)
		malloc_error();

	new_node->n = glb_number;
	new_node->next = NULL;
	new_node->prev = NULL;

	if (*stack == NULL)
	{
		*stack = new_node;
	}
	else
	{
		(*stack)->next = new_node;
		new_node->prev = *stack;
		*stack = new_node;
	}
	(void)line_number;
}

/**
 * pall - Function that print the elements of a stack
 * @stack: element at the top of the stack (head)
 * @line_number: constant int value in the structure
 * Return: void
 **/
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	(void)line_number;

	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->prev;
	}
}
/**
 * pint -  prints the value at the top of the stack
 * @stack: element at the top of the stack (head)
 * @line_number: constant int value in the structure
 * Return: void
 **/

void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	(void)line_number;
	if (tmp != NULL)
		printf("%d\n", tmp->n);
	else
		pint_error(line_number);
}

/**
 * pop - Function that pop (delete) the value at top of stack
 * @stack: element at the top of the stack (head)
 * @line_number: constant int value in the structure
 * Return: void
 **/
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (*stack == NULL)
		pop_error(line_number);

	*stack = (*stack)->prev;

	if ((*stack) != NULL)
		(*stack)->next = NULL;

	free(tmp);

	(void)line_number;
}
/**
 * swap - Function that swaps the top 2 elements of stack
 * @stack: element at the top of the stack (head)
 * @line_number: constant int value in the structure
 * Return: void
 **/
void swap(stack_t **stack, unsigned int line_number)
{
	int i;

	if (*stack == NULL || (*stack)->prev == NULL)
		swap_error(line_number);

	i = (*stack)->n;
	(*stack)->n = (*stack)->prev->n;
	(*stack)->prev->n = i;

	(void)line_number;
}

/**
 * add - Function that adds the top two elements of the stack
 * @stack: element at the top of the stack (head)
 * @line_number: constant int value in the structure
 * Return: void
 **/
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (tmp == NULL || (*stack)->prev == NULL)
		add_error(line_number);

	(tmp->prev)->n = tmp->n + (tmp->prev)->n;
	pop(stack, line_number);
}

/**
 * nop - Doesnt do anything
 * @stack: element at the top of the stack (head)
 * @line_number: constant int value in the structure
 * Return: void
 **/
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
