/*
** utils_locales.c for locales in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 18 13:01:49 2016 Frederic ODDOU
** Last update Wed May 18 13:19:58 2016 oddou_f
*/

#include <string.h>
#include <stdlib.h>
#include "shell.h"

t_locales		*utils_locales_add_right(char		*reponse[2],
						 t_locales	*loc)
{
  t_locales		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = NULL;
  new->prev = loc;
  if (loc != NULL)
    loc->next = new;
  new->name = reponse[0];
  new->value = reponse[1];
  return (new);
}

t_locales		*utils_locales_add_left(char		*reponse[2],
						t_locales	*loc)
{
  t_locales		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = loc;
  new->prev = NULL;
  if (loc != NULL)
    loc->prev = new;
  new->name = reponse[0];
  new->value = reponse[1];
  return (new);
}

t_locales		*utils_locales_find_elem(char		*name,
						 t_locales	*loc)
{
  while (loc != NULL)
    {
      if (!strcmp(loc->name, name))
	return (loc);
      loc = loc->next;
    }
  return (NULL);
}

void			utils_locales_delete_elem(t_locales	*loc)
{
  if (loc->next != NULL)
    loc->next->prev = loc->prev;
  if (loc->prev != NULL)
    loc->prev->next = loc->next;
  if (loc->name != NULL)
    free(loc->name);
  if (loc->value != NULL)
    free(loc->value);
  free(loc);
}

void			utils_locales_delete_list(t_locales	*loc)
{
  t_locales		*tmp;

  while (loc != NULL)
    {
      tmp = loc;
      loc = loc->next;
      utils_locales_delete_elem(tmp);
    }
}
