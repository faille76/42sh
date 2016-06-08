/*
** b_getenv.c for getenv in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 29 23:40:01 2016 Frederic ODDOU
** Last update Thu May 05 16:53:36 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "builtin.h"

char			*b_getenv(char			**tab,
				  char			*name)
{
  int			i;
  int			len;

  i = 0;
  if (tab == NULL || name == NULL)
    return (NULL);
  len = strlen(name);
  while (tab[i] != NULL)
    {
      if (!strncmp(tab[i], name, len) && tab[i][len] == '=')
	return (&tab[i][len + 1]);
      i++;
    }
  return (NULL);
}

char			*b_findenv(char			**tab,
				   char			*name)
{
  int			i;
  int			len;

  i = 0;
  if (tab == NULL || name == NULL)
    return (NULL);
  len = strlen(name);
  while (tab[i] != NULL)
    {
      if (!strncmp(tab[i], name, len) && tab[i][len] == '=')
	return (tab[i]);
      i++;
    }
  return (NULL);
}

int			b_get_id_env(char		**tab,
				     char		*name)
{
  int			i;
  int			len;

  i = 0;
  if (tab == NULL || name == NULL)
    return (NOT_ID);
  len = strlen(name);
  while (tab[i] != NULL)
    {
      if (!strncmp(tab[i], name, len) && tab[i][len] == '=')
	return (i);
      i++;
    }
  return (NOT_ID);
}
