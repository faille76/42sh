/*
** parser_commands_history.c for history in /src/parser/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Sat Jun  4 15:16:18 2016 Frederic ODDOU
** Last update Sat Jun  4 16:13:55 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

static t_commands	*parser_commands_go_out(t_commands	*commands)
{
  while (commands != NULL && commands->next != NULL)
    commands = commands->next;
  return (commands);
}

static t_commands	*parser_commands_history_push(t_shell	*shell,
						      t_commands*commands,
						      char	*str)
{
  t_commands		*shell_sauv;
  t_commands		*last;
  t_commands		*next;

  shell_sauv = shell->commands;
  next = commands->next;
  parser_commands(shell, str, false);
  if (shell->commands == NULL)
    {
      shell->commands = shell_sauv;
      return (commands->next);
    }
  last = parser_commands_go_out(shell->commands);
  if (commands->next != NULL)
    commands->next->prev = last;
  if (last != NULL)
    last->next = commands->next;
  commands->next = shell->commands;
  shell->commands = shell_sauv;
  utils_commands_delete_elem(shell, commands);
  return (next);
}

void			parser_commands_history(t_shell		*shell,
						t_commands	*commands)
{
  char			*new;

  while (commands != NULL)
    {
      new = NULL;
      if (commands->index_delim == ID_DOUBLE_QUOTE ||
	  commands->index_delim == ID_BACK_QUOTE)
	{
	  if ((new = utils_get_history(shell, commands->str)) != NULL)
	    {
	      free(commands->str);
	      commands->str = strdup(new);
	    }
	  commands = commands->next;
	}
      else if (commands->index_delim == ID_WITHOUT)
	{
	  if ((new = utils_get_history(shell, commands->str)) != NULL)
	    commands = parser_commands_history_push(shell, commands, new);
	  else
	    commands = commands->next;
	}
      else
	commands = commands->next;
    }
}
