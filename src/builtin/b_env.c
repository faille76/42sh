/*
** b_env.c for env in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 13:40:11 2016 Frederic ODDOU
** Last update Sun May 08 23:45:25 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"

int			b_env(int			ac,
			      char			**av,
			      t_shell			*shell)
{
  int			i;

  if (!shell->write)
    return (EXIT_SUCCESS);
  i = 0;
  if (shell->ae != NULL)
    {
      while (shell->ae[i] != NULL)
	{
	  printf("%s\n", shell->ae[i]);
	  i++;
	}
    }
  (void)ac;
  (void)av;
  return (EXIT_SUCCESS);
}
