/*
** b_unset.c for unset in /src/builtin/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Sun Jun  5 16:36:21 2016 Frederic ODDOU
** Last update Sun Jun  5 16:47:03 2016 Frederic ODDOU
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"

static int		b_unset_delete(t_shell			*shell,
				       char			*name)
{
  t_locales		*loc;

  if ((loc = utils_locales_find_elem(name, shell->locales)) == NULL)
    return (EXIT_FAILURE);
  if (loc == shell->locales)
    shell->locales = shell->locales->next;
  utils_locales_delete_elem(loc);
  return (EXIT_SUCCESS);
}

int			b_unset(int				ac,
				char				**av,
				t_shell				*shell)
{
  int			i;

  if (ac == 1)
    {
      if (shell->write)
	fprintf(stdout, FEW_ARG, av[0]);
      return (EXIT_FAILURE);
    }
  i = 1;
  while (i < ac)
    {
      b_unset_delete(shell, av[i]);
      i++;
    }
  return (EXIT_SUCCESS);
}
