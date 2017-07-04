/*
** getter.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Apr 18 22:34:07 2017 Arthur Josso
** Last update Wed Apr 19 17:50:23 2017 Arthur Josso
*/

#include <stddef.h>
#include "elf_reader.h"

const char	*get_sym_name(t_address addr)
{
  GElf_Sym	sym;
  size_t	i;
  const char	*name;

  if (elf_data.raw_symtab == NULL)
    return (NULL);
  i = 0;
  while (gelf_getsym(elf_data.raw_symtab, i, &sym))
    {
      if (addr == sym.st_value)
	{
	  name = elf_strptr(elf_data.elf, elf_data.stridx, sym.st_name);
	  if (*name)
	    return (name);
	}
      i++;
    }
  return (NULL);
}

static t_address	get_dynsym_addr(t_address plt_addr)
{
  t_address		addr;
  size_t		idx;

  idx = (plt_addr - (elf_data.addr_plt + PLT_ORG)) / PLT_SIZE;
  addr = idx * GOT_SIZE + elf_data.addr_got + GOT_ORG;
  return (addr);
}

const char	*get_dynsym_name(t_address addr)
{
  GElf_Rela	rela;
  GElf_Sym	sym;
  size_t	i;
  const char	*name;

  i = 0;
  addr = get_dynsym_addr(addr);
  while (gelf_getrela(elf_data.raw_rela, i, &rela))
    {
      if (addr == rela.r_offset)
	{
	  if (gelf_getsym(elf_data.raw_dynsym,
			  GELF_R_SYM(rela.r_info), &sym) == NULL)
	    elf_err();
	  name = elf_strptr(elf_data.elf, elf_data.dynstridx, sym.st_name);
	  if (name == NULL)
	    elf_err();
	  return (name);
	}
      i++;
    }
  return (NULL);
}
