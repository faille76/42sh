/*
** b_yes.c for yes in /src/builtin/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Tue May 31 23:03:10 2016 Frederic ODDOU
** Last update Tue May 31 23:05:33 2016 Frederic ODDOU
*/

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int			b_yes(int			ac,
			      char			**av,
			      t_shell			*shell)
{
  int			i;

  if (!shell->write)
    return (EXIT_SUCCESS);
  if (ac == 1)
    {
      while (1)
	printf("y\n");
    }
  while (1)
    {
      i = 1;
      while (i < ac)
	{
	  printf("%s", av[i]);
	  if (i + 1 < ac)
	    printf(" ");
	  i++;
	}
      printf("\n");
    }
  return (EXIT_SUCCESS);
}
