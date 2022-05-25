#include "monty.h"

/**
 * get_op_code - tydt
 * @token: operation code
 * @line: line readed
 * Return: void
 */
void (*get_op_code(char *token, unsigned int line))(stack_t **, unsigned int)
{
	int i = 0;
	char *tokens = NULL;
	char *save = NULL;

	tokens = tokenizer(token, "\n\t\r ");
	save = tokens[0];

	if (isdigit(tokens[1]) > 0 && strcmp(save, "push") == 0)
	{	
		printf("L%i: usage: push integer\n", line);
		exit(EXIT_FAILURE);
	}
	glb_number = atoi(tokens[1]);

	for (i = 0; list[i].opcode != NULL; i++)
	{
		if (strcmp(token, list[i].opcode) == 0)
		{
			free(tokens);
			return (list[i].f);
		}
	}
	(void)line;
	return (NULL);
}

/**
 * tokenizer - Function that split a string.
 * @s: string to split.
 * @delim: words delimiter.
 * Return: a char double pointer that contains splited words.
 */

char *tokenizer(char *s, char *delim)
{
	int i = 0, cword = 0;
	char *splitedw = NULL;

	cword = countw(s);

	splitedw = malloc(sizeof(char) * (cword + 1));
	if (splitedw == NULL)
	{
		malloc_error();
		return (NULL);
	}

	splitedw[0] = strtok(s, delim);

	if (splitedw[0] == NULL)
	{
		malloc_error();
		free(splitedw[0]);
		free(splitedw);
		return (NULL);
	}

	for (i = 1; i < cword; i++)
	{
		splitedw[i] = strtok(NULL, delim);
	}
	return (splitedw);
}

#define OUT 0
#define IN 1

/**
 * countw - function that counts words depending on delimiters
 * @str: string to be evaluated.
 * Return: number of words in the string.
 */

int countw(char *str)
{
	int state = OUT;
	unsigned int wc = 0;

	while (*str)
	{
		if (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == ':' || *str == '=')
			state = OUT;

		else if (state == OUT)
		{
			state = IN;
			++wc;
		}
		++str;
	}
	return (wc);
}
/**
 * free_all -  free a dlistint_t list.
 * @stack: pointer to a pointer to the head of a list.
 * Return: void
 */
void free_all(stack_t **stack)
{
	stack_t *fre;

	while (*stack)
	{
		fre = (*stack);
		(*stack) = fre->prev;
		free(fre);
	}
}

/**
 * int_error - print message if parameter receivedis not integer
 * @line: line
 * Return: void
 */
void int_error(int line)
{
	fprintf(stderr, "L%u: usage: push integer\n", line);
	exit(EXIT_FAILURE);
}
