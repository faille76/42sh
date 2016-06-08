/*
** utils_commands.c for utils_commands in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 00:29:02 2016 Frederic ODDOU
** Last update Sat Apr 30 11:24:52 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"

void			utils_commands_delete_list(t_commands	*commands)
{
  t_commands		*tmp;

  while (commands != NULL)
    {
      tmp = commands;
      commands = commands->next;
      if (tmp->str != NULL)
	free(tmp->str);
      free(tmp);
    }
}

void			utils_commands_delete_elem(t_shell	*shell,
						   t_commands	*commands)
{
  if (commands->prev != NULL)
    commands->prev->next = commands->next;
  else
    shell->commands = commands->next;
  if (commands->next != NULL)
    commands->next->prev = commands->prev;
  if (commands->str != NULL)
    free(commands->str);
  free(commands);
}

void			utils_commands_purge_elem(t_commands	*commands)
{
  if (commands->prev != NULL)
    commands->prev->next = NULL;
  if (commands->next != NULL)
    commands->next->prev = NULL;
  if (commands->str != NULL)
    free(commands->str);
  free(commands);
}

t_commands		*utils_commands_add_right(t_commands	*commands,
						  char		*str,
						  short		index_delim)
{
  t_commands		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->prev = commands;
  new->next = NULL;
  new->str = str;
  new->index_delim = index_delim;
  if (commands != NULL)
    {
      if (commands->next != NULL)
	{
	  new->next = commands->next;
	  commands->next->prev = new;
	}
      commands->next = new;
    }
  return (new);
}

t_commands		*utils_commands_go_back(t_commands	*commands)
{
  while (commands != NULL && commands->prev != NULL)
    commands = commands->prev;
  return (commands);
}
