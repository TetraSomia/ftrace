/*
** main.c for lol in /home/tetra/rendu/psu/PSU_2016_strace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Apr  3 10:52:33 2017 Arthur Josso
** Last update Fri Apr 21 20:09:59 2017 Arthur Josso
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core.h"
#include "elf_reader.h"
#include "func_stack.h"
#include "graph.h"

char *binary_name;

static void	clear_ressources(char *file)
{
  free(file);
  fini_elf_reader();
  stack_clear();
  graph_clear();
}

int    	main(int ac, char **av)
{
  char 	*file;
  int  	cmd_beg;

  cmd_beg = parse_options(ac, av);
  if (cmd_beg == 0)
    return (EXIT_FAILURE);
  if ((file = find_path(av[cmd_beg])) == NULL)
    {
      fprintf(stderr, "No such file or directory: \'%s\'\n", av[1]);
      return (EXIT_FAILURE);
    }
  binary_name = strrchr(file, '/') + 1;
  init_elf_reader(file);
  av[cmd_beg] = file;
  fork_routine(av + cmd_beg);
  trace_proc();
  if (GETFLAG(GRAPH))
    graph_generate();
  clear_ressources(file);
  return (EXIT_SUCCESS);
}
