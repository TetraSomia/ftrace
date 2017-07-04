/*
** fini.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Apr 18 21:07:27 2017 Arthur Josso
** Last update Tue Apr 18 22:17:29 2017 Arthur Josso
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "elf_reader.h"

void	fini_elf_reader()
{
  elf_end(elf_data.elf);
  close(elf_data.fd);
}

void	elf_err()
{
  fprintf(stderr, "ERROR: ELF not supported\n");
  exit(1);
}
