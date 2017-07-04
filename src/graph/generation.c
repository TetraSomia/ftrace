/*
** generation.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Fri Apr 21 00:16:06 2017 Arthur Josso
** Last update Fri Apr 21 13:46:41 2017 Arthur Josso
*/

#include <stdio.h>
#include "graph.h"
#include "misc.h"

static const t_type_properties prop[] =
  {
    {NODE_SYSCALL, "red"},
    {NODE_FUNC, "green"},
    {NODE_DYN_FUNC, "blue"}
  };

static FILE	*init_file()
{
  FILE		*file;
  char		filename[MAX_GRAPH_FILENAME_LENGTH];

  snprintf(filename, MAX_GRAPH_FILENAME_LENGTH,
	   "%s_graph.dot", binary_name);
  file = fopen(filename, "w+");
  if (file == NULL)
    fat_err("fopen");
  return (file);
}

static void	gen_links(FILE *file, t_graph_node *func)
{
  t_link_node	*link;

  link = func->call;
  while (link)
    {
      fprintf(file, "%s -> %s [label=\"%ld\"];\n",
              func->name, link->func->name, link->nb_call);
      link = link->next;
    }
}

static void	gen_funcs(FILE *file)
{
  t_graph_node	*func;

  func = graph;
  while (func)
    {
      fprintf(file, "%s [shape=polygon, color=%s];\n",
	      func->name, prop[func->type].color);
      gen_links(file, func);
      func = func->next;
    }
}

static void	replace_dots(FILE *file)
{
  char		c;

  rewind(file);
  while ((c = fgetc(file)) != EOF)
    {
      if (c == '.')
        {
          fseek(file, ftell(file) - 1, SEEK_SET);
          fputc('_', file);
        }
    }
}

void	graph_generate()
{
  FILE	*file;

  file = init_file();
  fprintf(file, "digraph callgraph\n{\n");
  gen_funcs(file);
  fprintf(file, "}\n");
  replace_dots(file);
  fclose(file);
}
