/*
** b_builtins.c for builtins in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri May  6 11:57:46 2016 Frederic ODDOU
** Last update Sun May 08 23:46:49 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "builtin.h"

int			b_builtins(int			ac,
				   char			**av,
				   t_shell		*shell)
{
  short			i;

  if (!shell->write)
    return (EXIT_SUCCESS);
  i = 0;
  while (g_builtin[i].name != NULL)
    {
      printf("- %s\n", g_builtin[i].name);
      i++;
    }
  (void)ac;
  (void)av;
  return (EXIT_SUCCESS);
}
