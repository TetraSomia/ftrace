/*
** misc.c for lol in /home/tetra/rendu/psu/PSU_2016_strace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Apr  3 10:47:42 2017 Arthur Josso
** Last update Fri Apr 21 19:58:03 2017 Arthur Josso
*/

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <errno.h>
#include <string.h>

void	fat_err(const char *msg)
{
  fprintf(stderr, "ERROR: %s: %s\n", msg, strerror(errno));
  exit(1);
}

void	*xmalloc(size_t size)
{
  void	*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    fat_err("malloc");
  bzero(ptr, size);
  return (ptr);
}
