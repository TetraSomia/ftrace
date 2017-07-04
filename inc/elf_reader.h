/*
** elf_reader.h for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Apr 18 21:05:08 2017 Arthur Josso
** Last update Tue Apr 18 22:54:10 2017 Arthur Josso
*/

#pragma once

#include <gelf.h>

#define INIT_CHECK_MASK	(0b11111)

typedef unsigned long t_address;

typedef struct
{
  int		fd;
  Elf		*elf;
  size_t	stridx;
  size_t	dynstridx;
  Elf_Data	*raw_symtab;
  Elf_Data	*raw_dynsym;
  Elf_Data	*raw_rela;
  t_address	addr_plt;
  t_address	addr_got;
} t_elf_data;

extern t_elf_data elf_data;

void init_elf_reader(const char *file);
void fini_elf_reader();

/*
** Getter
*/

#define PLT_ORG		(0x10)
#define	PLT_SIZE	(0x10)
#define GOT_ORG		(0x18)
#define GOT_SIZE	(0x8)

const char	*get_sym_name(t_address addr);
const char	*get_dynsym_name(t_address addr);

/*
** Init funcs
*/

typedef struct
{
  const char *section_name;
  void (*func)(Elf_Scn *scn, GElf_Shdr *shdr);
} t_elf_init_funcs;

void get_symtab(Elf_Scn *scn, GElf_Shdr *shdr);
void get_dynsymtab(Elf_Scn *scn, GElf_Shdr *shdr);
void get_relatab(Elf_Scn *scn, GElf_Shdr *shdr);
void get_pltaddr(Elf_Scn *scn, GElf_Shdr *shdr);
void get_gotaddr(Elf_Scn *scn, GElf_Shdr *shdr);
void get_strtab(Elf_Scn *scn, GElf_Shdr *shdr);
void get_dynstrtab(Elf_Scn *scn, GElf_Shdr *shdr);

/*
** Misc
*/

void elf_err();
