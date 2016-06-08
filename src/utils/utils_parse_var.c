/*
** utils_parse_var.c for parse var in /src/utils/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Wed Jun  1 13:54:41 2016 Frederic ODDOU
** Last update Wed Jun  1 13:58:51 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "builtin.h"

int			utils_get_acolade_count(char		*find)
{
  int			i;

  i = 0;
  if (*find != DELIM_VAR_OPEN)
    return (-1);
  while (find[i] != '\0')
    {
      if (find[i] == DELIM_VAR_CLOSE)
	return (i);
      i++;
    }
  return (-1);
}

char			*utils_get_acolade(char			*find)
{
  char			*new;
  int			i;
  int			len;

  i = 0;
  len = utils_get_acolade_count(find) + 1;
  if ((new = malloc(sizeof(char) * len)) == NULL)
    return (NULL);
  while (find[i + 1] != '\0' && find[i + 1] != DELIM_VAR_CLOSE)
    {
      new[i] = find[i + 1];
      i++;
    }
  new[i] = '\0';
  return (new);
}

char			*utils_get_var_find(t_shell		*shell,
					    char		*find)
{
  char			*var;
  t_locales		*loc;

  loc = shell->locales;
  if ((var = b_getenv(shell->ae, find)) != NULL)
    return (var);
  while (loc != NULL)
    {
      if (!strcmp(loc->name, find))
	return (loc->value);
      loc = loc->next;
    }
  fprintf(stderr, "%s: Undefined variable.\n", find);
  return (NULL);
}
