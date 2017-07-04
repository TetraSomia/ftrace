/*
** init_funcs.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Apr 18 22:06:10 2017 Arthur Josso
** Last update Tue Apr 18 22:46:30 2017 Arthur Josso
*/

#include <stddef.h>
#include "elf_reader.h"

void	get_symtab(Elf_Scn *scn, GElf_Shdr *shdr)
{
  (void)shdr;
  elf_data.raw_symtab = elf_getdata(scn, NULL);
  if (elf_data.raw_symtab == NULL)
    elf_err();
}

void	get_dynsymtab(Elf_Scn *scn, GElf_Shdr *shdr)
{
  (void)shdr;
  elf_data.raw_dynsym = elf_getdata(scn, NULL);
  if (elf_data.raw_dynsym == NULL)
    elf_err();
}

void	get_relatab(Elf_Scn *scn, GElf_Shdr *shdr)
{
  (void)shdr;
  elf_data.raw_rela = elf_getdata(scn, NULL);
  if (elf_data.raw_rela == NULL)
    elf_err();
}

void	get_pltaddr(Elf_Scn *scn, GElf_Shdr *shdr)
{
  (void)scn;
  elf_data.addr_plt = shdr->sh_addr;
}

void	get_gotaddr(Elf_Scn *scn, GElf_Shdr *shdr)
{
  (void)scn;
  elf_data.addr_got = shdr->sh_addr;
}
