/*
** main.c for  in /home/broggi_t/projet/nm-objdump/nm
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Mon Apr 13 17:53:13 2015 broggi_t
** Last update Mon Apr 13 17:53:13 2015 broggi_t
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"

static int	print_usage(char const *const bin_name)
{
  printf("Usage: %s [--sort=24] [--help] [bin]...\n", bin_name);
  return (1);
}

static int	nb_files(int const ac,
			 char const *const *const av)
{
  register int	i;
  char		found;

  i = 0;
  found = 0;
  while (++i < ac)
    if (strcmp(av[i], "--sort=24")
	&& strcmp(av[i], "--help"))
      ++found;
  return (found);
}

static int	get_args(int const ac,
			 char const *const *const av,
			 t_elf *const elf)
{
  int		i;

  elf->sort = 23;
  i = 0;
  while (++i < ac)
    {
      if (!strcmp(av[i], "--sort=24"))
	elf->sort = 24;
      else if (!strcmp(av[i], "--help"))
	return (print_usage(*av));
      else
	{
	  if (nb_files(ac, av) > 1)
	    printf("\n%s:\n", av[i]);
	  if (!parse_file(av[i], elf)
	      || !run_elf(elf))
	    return (0);
	}
    }
  if (!nb_files(ac, av))
    return (parse_file("a.out", elf)
	    && run_elf(elf));
  return (1);
}

int	main(int const ac, char const *const *const av)
{
  t_elf	elf;

  return (get_args(ac, av, &elf) ? EXIT_SUCCESS : EXIT_FAILURE);
}
