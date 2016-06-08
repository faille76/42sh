/*
** utils_list.c for utils list in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 12:52:22 2016 Frederic ODDOU
** Last update Fri Apr 29 22:53:59 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"

void			utils_list_delete_list(t_list		*list)
{
  t_list		*tmp;

  while (list != NULL)
    {
      tmp = list;
      list = list->next;
      if (tmp->commands != NULL)
	utils_commands_delete_list(tmp->commands);
      if (tmp->pipe != NULL)
	utils_pipe_delete_list(tmp->pipe);
      free(tmp);
    }
}

void			utils_list_delete_elem(t_shell		*shell,
					       t_list		*list)
{
  if (list->prev != NULL)
    list->prev->next = list->next;
  else
    shell->list = list->next;
  if (list->next != NULL)
    list->next->prev = list->prev;
  if (list->commands != NULL)
    utils_commands_delete_list(list->commands);
  free(list);
}

t_list			*utils_list_add_right(t_list		*list,
					      t_commands	*commands,
					      short		type_separator)
{
  t_list		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->prev = list;
  new->next = NULL;
  new->commands = commands;
  new->type_separator = type_separator;
  new->treat = true;
  new->pipe = NULL;
  new->background = false;
  if (list != NULL)
    {
      if (list->next != NULL)
	{
	  new->next = list->next;
	  list->next->prev = new;
	}
      list->next = new;
    }
  return (new);
}

t_list			*utils_list_go_back(t_list		*list)
{
  while (list != NULL && list->prev != NULL)
    list = list->prev;
  return (list);
}
