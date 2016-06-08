/*
** parser_redi.c for redi in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 12:13:38 2016 Frederic ODDOU
** Last update Fri May 13 14:16:24 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

static t_commands	*parser_redi_delete_commands(t_pipe	*pipe,
						    t_commands	*commands)
{
  t_commands		*ret;

  commands = commands->next;
  utils_pipe_delete_command(pipe, commands->prev);
  ret = commands->next;
  utils_pipe_delete_command(pipe, commands);
  return (ret);
}

static bool		parser_redi_add_right(t_pipe		*pipe,
					      t_commands	*commands)
{
  if (pipe->next || pipe->redi[RED_RIGHT] || pipe->redi[RED_TWO_RIGHT])
    {
      fprintf(stdout, "%s\n", ERR_AMBIOUT);
      return (false);
    }
  if (commands->next == NULL || commands->next->str == NULL)
    {
      fprintf(stdout, "%s\n", ERR_MISSNAME);
      return (false);
    }
  if (commands->index_delim == ID_DOUBLE_RIGHT)
    pipe->redi[RED_TWO_RIGHT] = strdup(commands->next->str);
  else if (commands->index_delim == ID_RIGHT)
    pipe->redi[RED_RIGHT] = strdup(commands->next->str);
  return (true);
}

static bool		parser_redi_add_left(t_pipe		*pipe,
					     t_commands		*commands)
{
  if (pipe->prev || pipe->redi[RED_LEFT] || pipe->redi[RED_TWO_LEFT])
    {
      fprintf(stdout, "%s\n", ERR_AMBIIN);
      return (false);
    }
  if (commands->next == NULL || commands->next->str == NULL)
    {
      fprintf(stdout, "%s\n", ERR_MISSNAME);
      return (false);
    }
  if (commands->index_delim == ID_DOUBLE_LEFT)
    pipe->redi[RED_TWO_LEFT] = strdup(commands->next->str);
  else if (commands->index_delim == ID_LEFT)
    pipe->redi[RED_LEFT] = strdup(commands->next->str);
  return (true);
}

static bool		parser_redi_find(t_pipe		*pipe,
					 t_commands	*commands)
{
  while (commands != NULL)
    {
      if (commands->index_delim == ID_DOUBLE_RIGHT ||
	  commands->index_delim == ID_RIGHT)
	{
	  if (parser_redi_add_right(pipe, commands) == false)
	    return (false);
	  commands = parser_redi_delete_commands(pipe, commands);
	}
      else if (commands->index_delim == ID_DOUBLE_LEFT ||
	       commands->index_delim == ID_LEFT)
	{
	  if (parser_redi_add_left(pipe, commands) == false)
	    return (false);
	  commands = parser_redi_delete_commands(pipe, commands);
	}
      else
	commands = commands->next;
    }
  if (pipe->commands == NULL)
    {
      fprintf(stdout, "%s\n", ERR_NULL);
      return (false);
    }
  return (true);
}

bool			parser_redi(t_list		*list)
{
  t_pipe		*tmp;

  tmp = list->pipe;
  while (tmp != NULL)
    {
      if (parser_redi_find(tmp, tmp->commands) == false)
	return (false);
      tmp = tmp->next;
    }
  return (true);
}
