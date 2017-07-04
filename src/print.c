/*
** print.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Fri Apr 21 19:58:09 2017 Arthur Josso
** Last update Fri Apr 21 20:05:05 2017 Arthur Josso
*/

#include <stdarg.h>
#include <stdio.h>
#include "core.h"

void		print_data(const char *fmt, ...)
{
  va_list	arglist;

  if (!GETFLAG(VERBOSE))
    return;
  va_start(arglist, fmt);
  vfprintf(stderr, fmt, arglist);
  va_end(arglist);
}
