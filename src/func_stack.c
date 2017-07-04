/*
** func_stack.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed Apr 19 20:02:02 2017 Arthur Josso
** Last update Thu Apr 20 20:29:46 2017 Arthur Josso
*/

#include <stdlib.h>
#include "func_stack.h"

static t_stack_node *top = NULL;

void		stack_push_func(t_address addr, t_address rip,
				const char *name)
{
  t_stack_node	*new;

  new = xmalloc(sizeof(t_stack_node));
  new->addr = addr;
  new->rip = rip;
  new->next = top;
  new->name = name;
  top = new;
}

t_address      	stack_pop_func()
{
  t_stack_node	*tmp;
  t_address	addr;

  if (top == NULL)
    return (0);
  addr = top->addr;
  tmp = top->next;
  free(top);
  top = tmp;
  return (addr);
}

t_address	stack_get_rip()
{
  if (top == NULL)
    return (0);
  return (top->rip);
}

void		stack_clear()
{
  t_stack_node	*tmp;

  while (top != NULL)
    {
      tmp = top->next;
      free(top);
      top = tmp;
    }
}

const char      *stack_get_named_caller()
{
  t_stack_node	*tmp;

  tmp = top;
  while (tmp)
    {
      if (tmp->name != NULL)
	return (tmp->name);
      tmp = tmp->next;
    }
  return (NULL);
}
