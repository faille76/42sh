/*
** parser_list.c for list in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 12:46:15 2016 Frederic ODDOU
** Last update Mon May 16 17:53:37 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

void			parser_list(t_shell			*shell)
{
  t_commands		*tmp;

  tmp = shell->commands;
  shell->list = NULL;
  if (tmp != NULL)
    {
      shell->list = utils_list_add_right(shell->list, tmp, ID_SEP);
      while (tmp != NULL)
	{
	  if (tmp->prev != NULL &&
	      tmp->prev->index_delim != ID_WITHOUT &&
	      (IF_SEP(tmp->prev->index_delim)))
	    {
	      shell->list = utils_list_add_right(shell->list,
						 tmp,
						 tmp->prev->index_delim);
	      utils_commands_purge_elem(tmp->prev);
	    }
	  tmp = tmp->next;
	}
    }
  shell->list = utils_list_go_back(shell->list);
  shell->commands = NULL;
}
