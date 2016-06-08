/*
** utils_alias.c for locales in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 18 13:01:49 2016 Frederic ODDOU
** Last update Thu May 19 12:50:32 2016 oddou_f
*/

#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "my.h"

t_alias			*utils_alias_add_right(t_alias		*alias,
					       char		**av_origin,
					       char		**av_to)
{
  t_alias		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = NULL;
  new->prev = alias;
  if (alias != NULL)
    alias->next = new;
  new->av_origin = av_origin;
  new->av_to = av_to;
  return (new);
}

t_alias			*utils_alias_add_left(t_alias		*alias,
					      char		**av_origin,
					      char		**av_to)
{
  t_alias		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = alias;
  new->prev = NULL;
  if (alias != NULL)
    alias->prev = new;
  new->av_origin = av_origin;
  new->av_to = av_to;
  return (new);
}

void			utils_alias_delete_elem(t_alias		*alias)
{
  if (alias->next != NULL)
    alias->next->prev = alias->prev;
  if (alias->prev != NULL)
    alias->prev->next = alias->next;
  my_tab_free(alias->av_origin);
  my_tab_free(alias->av_to);
  free(alias);
}

void			utils_alias_delete_list(t_alias		*alias)
{
  t_alias		*tmp;

  while (alias != NULL)
    {
      tmp = alias;
      alias = alias->next;
      utils_alias_delete_elem(tmp);
    }
}
