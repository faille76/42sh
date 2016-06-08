/*
** parser_pipe.c for parser pipe in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 14:38:03 2016 Frederic ODDOU
** Last update Fri May 13 23:10:50 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

/*
** On vérifie qu'une pipe n'est pas au début ni à la fin
** On vérifie aussi si une pipe n'est pas suivi d'une pipe
** Si c'est le cas c'est une erreur
*/

static bool		parser_check_pipe(t_commands		*commands)
{
  t_commands		*tmp;

  tmp = commands;
  while (tmp != NULL)
    {
      if (tmp->index_delim != ID_WITHOUT && (IF_PIPE(tmp->index_delim)))
	{
	  if ((tmp == commands || tmp->next == NULL) ||
	      (tmp->next != NULL && tmp->next->index_delim != ID_WITHOUT &&
	       (IF_PIPE(tmp->next->index_delim))))
	    {
	      fprintf(stdout, "%s\n", ERR_NULL);
	      return (false);
	    }
	}
      tmp = tmp->next;
    }
  return (true);
}

/*
** On sépare les pipes avec la liste chainée pipe
*/

static void		parser_get_pipe(t_list			*list)
{
  t_commands		*tmp;

  tmp = list->commands;
  if (list != NULL && list->commands)
    list->pipe = utils_pipe_add_right(list->pipe, list->commands);
  while (tmp != NULL)
    {
      if (tmp->prev != NULL &&
	  tmp->prev->index_delim != ID_WITHOUT &&
	  (IF_PIPE(tmp->prev->index_delim)))
	{
          list->pipe = utils_pipe_add_right(list->pipe, tmp);
	  utils_commands_purge_elem(tmp->prev);
	}
      tmp = tmp->next;
    }
  list->commands = NULL;
  list->pipe = utils_pipe_go_back(list->pipe);
}

/*
** Si il y a des parenthèses avec des commandes dans le même pipes on rejete
*/

static bool		parser_pipe_parenthese(t_pipe		*pipe)
{
  t_commands		*tmp;

  while (pipe != NULL)
    {
      tmp = pipe->commands;
      while (tmp != NULL)
	{
	  if (tmp->index_delim == ID_PARENTHESE)
	    {
	      if (tmp->next || tmp->prev)
		{
		  fprintf(stderr, ERR_PARENTHESE);
		  return (false);
		}
	    }
	  tmp = tmp->next;
	}
      pipe = pipe->next;
    }
  return (true);
}

bool			parser_pipe(t_shell			*shell)
{
  t_list		*tmp;

  tmp = shell->list;
  while (tmp != NULL)
    {
      if (parser_check_pipe(tmp->commands) == false)
	{
	  utils_list_delete_list(shell->list);
	  shell->list = NULL;
	  return (false);
	}
      parser_get_pipe(tmp);
      if (parser_pipe_parenthese(tmp->pipe) == false ||
	  parser_redi(tmp) == false)
	{
	  utils_list_delete_list(shell->list);
	  shell->list = NULL;
	  return (false);
	}
      tmp = tmp->next;
    }
  return (true);
}
