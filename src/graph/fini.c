/*
** fini.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Apr 20 20:49:15 2017 Arthur Josso
** Last update Thu Apr 20 20:58:35 2017 Arthur Josso
*/

#include <stdlib.h>
#include "graph.h"

void		graph_clear()
{
  t_graph_node	*tmp;
  t_link_node	*tmp_link;

  while (graph)
    {
      while (graph->call)
	{
	  tmp_link = graph->call->next;
	  free(graph->call);
	  graph->call = tmp_link;
	}
      tmp = graph->next;
      free(graph);
      graph = tmp;
    }
}
