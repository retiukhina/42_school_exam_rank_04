#include "vbc.h"

node *parse_nbr(char **s)
{
	if(!isdigit(**s))
	{
		unexpected(**s);
		return (NULL);
	}
	node n = { .type = VAL, .val = **s - '0', .l = NULL, .r = NULL };

	(*s)++;
	return (new_node(n));
}

node *parse_parenth(char **s)
{
	if (accept(s, '('))
	{
		node *expr = parse_expr(s);
		if (!expect(s, ')'))
		{
			destroy_tree(expr);
			return (NULL);
		}
		return (expr);
	}
	return (parse_nbr(s));
}

node *parse_term(char **s)
{
	node *left = parse_parenth(s);
	while(accept(s, '*'))
	{
		node *right = parse_parenth(s);
		if(!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		node n = { .type = MULTI, .l = left, .r = right };
		left = new_node(n);
	}
	return (left);
}

node	*parse_expr(char **s)
{
	node *left = parse_term(s);
	while (accept(s, '+'))
	{
		node *right = parse_term(s);
		if(!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		node n = { .type = ADD, .l = left, .r = right };
		left = new_node(n);
	}
	return (left);
}
