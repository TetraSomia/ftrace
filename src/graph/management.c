/*
** graph.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Apr 20 19:56:40 2017 Arthur Josso
** Last update Thu Apr 20 20:49:41 2017 Arthur Josso
*/

#include <string.h>
#include "graph.h"
#include "func_stack.h"

t_graph_node *graph = NULL;

static t_graph_node	*find_node(const char *name)
{
  t_graph_node		*tmp;

  if (name == NULL)
    return (NULL);
  tmp = graph;
  while (tmp)
    {
      if (strcmp(tmp->name, name) == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

static t_graph_node	*create_node(t_node_type type, const char *name)
{
  t_graph_node  *new;

  new = xmalloc(sizeof(t_graph_node));
  new->type = type;
  new->name = name;
  new->call = NULL;
  new->next = graph;
  graph = new;
  return (new);
}

static t_link_node	*find_link(t_graph_node *caller,
				   t_graph_node *callee)
{
  t_link_node		*tmp;

  tmp = caller->call;
  while (tmp)
    {
      if (strcmp(tmp->func->name, callee->name) == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

static t_link_node	*create_link(t_graph_node *caller,
				     t_graph_node *callee)
{
  t_link_node		*new;

  new = xmalloc(sizeof(t_link_node));
  new->func = callee;
  new->nb_call = 0;
  new->next = caller->call;
  caller->call = new;
  return (new);
}

void		graph_add_node(t_node_type type, const char *name)
{
  t_graph_node	*new;
  t_graph_node	*caller;
  t_link_node	*link;

  if (name == NULL)
    return;
  if ((new = find_node(name)) == NULL)
    new = create_node(type, name);
  caller = find_node(stack_get_named_caller());
  if (caller == NULL)
    return;
  if ((link = find_link(caller, new)) == NULL)
    link = create_link(caller, new);
  link->nb_call++;
}
