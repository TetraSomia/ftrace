/*
** init.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Apr 18 21:06:22 2017 Arthur Josso
** Last update Tue Apr 18 23:00:52 2017 Arthur Josso
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "elf_reader.h"

t_elf_data	elf_data;

static const t_elf_init_funcs init_funcs[] =
  {
    {".dynsym", get_dynsymtab},
    {".rela.plt", get_relatab},
    {".plt", get_pltaddr},
    {".got.plt", get_gotaddr},
    {".dynstr", get_dynstrtab},
    {".symtab", get_symtab},
    {".strtab", get_strtab},
    {NULL, NULL},
  };

static void	init_elf_data()
{
  Elf_Scn	*scn;
  GElf_Shdr	shdr;
  size_t	i;
  size_t	initCheckMask;
  size_t	shstrndx;

  if (elf_getshdrstrndx(elf_data.elf, &shstrndx) == -1)
    elf_err();
  initCheckMask = 0;
  scn = NULL;
  while ((scn = elf_nextscn(elf_data.elf, scn)) != NULL)
    {
      if (gelf_getshdr(scn, &shdr) == NULL)
	elf_err();
      i = -1;
      while (init_funcs[++i].section_name)
	if (strcmp(elf_strptr(elf_data.elf, shstrndx, shdr.sh_name),
		   init_funcs[i].section_name) == 0)
	  {
	    init_funcs[i].func(scn, &shdr);
	    initCheckMask |= (size_t)pow(2, i);
	  }
    }
  if ((initCheckMask & INIT_CHECK_MASK) != INIT_CHECK_MASK)
    elf_err();
}

void	init_elf_reader(const char *file)
{
  if (elf_version(EV_CURRENT) == EV_NONE)
    elf_err();
  if ((elf_data.fd = open(file, O_RDONLY)) == -1)
    elf_err();
  if ((elf_data.elf = elf_begin(elf_data.fd, ELF_C_READ, NULL)) == NULL)
    elf_err();
  if (elf_kind(elf_data.elf) != ELF_K_ELF)
    elf_err();
  elf_data.raw_symtab = NULL;
  init_elf_data();
}
