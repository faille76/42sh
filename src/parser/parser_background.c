/*
** parser_background.c for background in /src/parser/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Fri Jun  3 17:23:05 2016 Frederic ODDOU
** Last update Sun Jun  5 18:12:19 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

static bool		parser_background_find(t_pipe		*pipe,
					       t_list		*list,
					       t_shell		*shell);

static bool		parser_background_commands(t_pipe	*pipe,
						   t_list	*list,
						   t_shell	*shell)
{
  t_commands		*commands;

  commands = pipe->commands;
  while (commands != NULL)
    {
      if (commands->index_delim == ID_BACKGROUND)
	{
	  if (pipe->next ||
	      (commands->prev == NULL && commands->next == NULL))
	    {
	      fprintf(stdout, "%s\n", ERR_NULL);
	      return (false);
	    }
	  list->background = true;
	  if (pipe->commands == commands)
	    pipe->commands = commands->next;
	  utils_commands_delete_elem(shell, commands);
	  return (parser_background_find(pipe, list, shell));
	}
      commands = commands->next;
    }
  return (true);
}

static bool		parser_background_find(t_pipe		*pipe,
					       t_list		*list,
					       t_shell		*shell)
{
  while (pipe != NULL)
    {
      if (parser_background_commands(pipe, list, shell) == false)
	return (false);
      pipe = pipe->next;
    }
  return (true);
}

bool			parser_background(t_shell		*shell)
{
  t_list		*tmp;

  tmp = shell->list;
  while (tmp != NULL)
    {
      if (parser_background_find(tmp->pipe, tmp, shell) == false)
	return (false);
      tmp = tmp->next;
    }
  return (true);
}
