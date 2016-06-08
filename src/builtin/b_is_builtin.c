/*
** b_is_builtin.c for if builtin in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 30 22:30:55 2016 Frederic ODDOU
** Last update Mon May 16 16:37:01 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "builtin.h"

short			b_is_builtin(char		*name)
{
  short			i;

  i = 0;
  if (name == NULL)
    return (NOT_BUILTIN);
  while (g_builtin[i].name != NULL)
    {
      if (strcmp(g_builtin[i].name, name) == 0)
	{
	  if (g_builtin[i].func != NULL)
	    return (i);
	}
      i++;
    }
  return (NOT_BUILTIN);
}
