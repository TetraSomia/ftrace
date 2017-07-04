/*
** init_funcs.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Apr 18 22:06:10 2017 Arthur Josso
** Last update Tue Apr 18 22:20:54 2017 Arthur Josso
*/

#include "elf_reader.h"

void	get_strtab(Elf_Scn *scn, GElf_Shdr *shdr)
{
  (void)shdr;
  elf_data.stridx = elf_ndxscn(scn);
  if (elf_data.stridx == SHN_UNDEF)
    elf_err();
}

void	get_dynstrtab(Elf_Scn *scn, GElf_Shdr *shdr)
{
  (void)shdr;
  elf_data.dynstridx = elf_ndxscn(scn);
  if (elf_data.dynstridx == SHN_UNDEF)
    elf_err();
}
