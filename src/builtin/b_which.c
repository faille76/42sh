/*
** b_which.c for which in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 14:44:42 2016 Frederic ODDOU
** Last update Sun May 08 23:38:35 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"

static int		b_which_treat(char			**av,
				      t_shell			*shell)
{
  char			*str;
  int			i;

  if (!shell->write)
    return (EXIT_SUCCESS);
  i = 1;
  while (av[i] != NULL)
    {
      if (b_is_builtin(av[i]) != NOT_BUILTIN)
	printf(IS_BUILTIN, av[i]);
      else if ((str = shell_get_path(shell, av[i])) != NULL)
	{
	  printf("%s\n", str);
	  free(str);
	}
      i++;
    }
  return (EXIT_SUCCESS);
}

int			b_which(int				ac,
				char				**av,
				t_shell				*shell)
{
  if (ac < 2)
    {
      if (shell->write)
	fprintf(stdout, FEW_ARG, av[0]);
      return (EXIT_FAILURE);
    }
  return (b_which_treat(av, shell));
}
