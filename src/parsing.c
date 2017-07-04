/*
** parsing.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Fri Apr 21 19:31:50 2017 Arthur Josso
** Last update Fri Apr 21 20:09:30 2017 Arthur Josso
*/

#include <stdio.h>
#include "core.h"

t_flag option_flags = 0;

static int      print_usage(const char *exec)
{
  fprintf(stderr, "Usage : %s [-v] [-g] <commande>\n", exec);
  fprintf(stderr, "\t-v\tDisable verbose on stderr\n");
  fprintf(stderr, "\t-g\tEnbale graph generation (.dot)\n");
  return (0);
}

int     parse_options(int ac, char **av)
{
  int   opt;

  SETFLAG(VERBOSE);
  opterr = 0;
  if (ac == 1)
    return (print_usage(av[0]));
  while ((opt = getopt(ac, av, "+vg")) != -1)
    {
      if (opt == 'v')
	RESETFLAG(VERBOSE);
      else if (opt == 'g')
	SETFLAG(GRAPH);
      else if (opt == '?')
	return (print_usage(av[0]));
    }
  if (optind >= ac)
    return (print_usage(av[0]));
  return (optind);
}
