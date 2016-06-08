/*
** parser_commands_comment.c for comment in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May 23 14:27:59 2016 Frederic ODDOU
** Last update Mon May 23 14:40:33 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

t_commands		*parser_commands_comment(t_commands	*commands)
{
  t_commands		*tmp;

  tmp = commands;
  while (tmp != NULL)
    {
      if (tmp->str != NULL &&
	  GET_TYPE(tmp->index_delim) == D_NORMAL &&
	  !strncmp(tmp->str, "#", 1))
	{
	  if (tmp->prev != NULL)
	    tmp->prev->next = NULL;
	  utils_commands_delete_list(tmp);
	  if (tmp == commands)
	    return (NULL);
	  return (commands);
	}
      tmp = tmp->next;
    }
  return (commands);
}
