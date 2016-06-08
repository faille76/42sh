/*
** parser_check_separator.c for parser_check_separator in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed Apr 27 22:48:24 2016 Frederic ODDOU
** Last update Fri May 13 22:02:55 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

/*
** Si deux séparateurs sont à la suite :
** Le 1er est différent de ";" c'est une erreur SAUF si c'est suivi de "||"
** Suppression des séparateurs en excès.
*/

static bool		parser_delete_excess(t_shell		*shell)
{
  t_commands		*tmp;

  tmp = shell->commands;
  while (tmp != NULL && tmp->next != NULL)
    {
      if (tmp->index_delim != ID_WITHOUT &&
	  tmp->next->index_delim != ID_WITHOUT &&
	  (IF_SEP(tmp->index_delim)) && (IF_SEP(tmp->next->index_delim)))
	{
	  if (GET_ID(tmp->index_delim) != ID_SEP ||
	      (GET_ID(tmp->index_delim) == ID_SEP &&
	       GET_ID(tmp->next->index_delim) == ID_OR))
	    {
	      fprintf(stdout, "%s\n", ERR_NULL);
	      return (false);
	    }
	  else
	    {
	      utils_commands_delete_elem(shell, tmp->next);
	      return (parser_delete_excess(shell));
	    }
	}
      tmp = tmp->next;
    }
  return (true);
}

/*
** Vérification des extémités
** Impossibilité de mettre un séparateur "||" en début de chaine
** Impossibilité de mettre un séparateur en fin de chaine sauf ";"
*/

static bool		parser_check_limit(t_shell		*shell)
{
  t_commands		*tmp;

  tmp = shell->commands;
  if (tmp != NULL)
    {
      if (tmp->index_delim != ID_WITHOUT && GET_ID(tmp->index_delim) == ID_OR)
	{
	  fprintf(stdout, "%s\n", ERR_NULL);
	  return (false);
	}
      while (tmp != NULL && tmp->next != NULL)
	tmp = tmp->next;
      if (tmp != shell->commands)
	{
	  if (tmp->index_delim != ID_WITHOUT &&
	      GET_TYPE(tmp->index_delim) == D_SEPARATOR &&
	      GET_ID(tmp->index_delim) != ID_SEP)
	    {
	      fprintf(stdout, "%s\n", ERR_NULL);
	      return (false);
	    }
	}
    }
  return (true);
}

/*
** On supprime les séparateurs qui sont aux limites
*/

static void		parser_delete_limit(t_shell		*shell)
{
  t_commands		*tmp;
  t_commands		*first;
  int			del;

  del = 0;
  tmp = first = shell->commands;
  if (tmp != NULL)
    {
      while (tmp != NULL && tmp->next != NULL)
	tmp = tmp->next;
      if (tmp != first &&
	  tmp->index_delim != ID_WITHOUT && (IF_SEP(tmp->index_delim)))
	{
	  del++;
	  utils_commands_delete_elem(shell, tmp);
	}
      if (first->index_delim != ID_WITHOUT && (IF_SEP(first->index_delim)))
	{
	  del++;
	  utils_commands_delete_elem(shell, first);
	}
    }
  if (del > 0)
    parser_delete_limit(shell);
}

bool			parser_check_separator(t_shell		*shell)
{
  if (parser_check_limit(shell) == false)
    return (false);
  if (parser_delete_excess(shell) == false)
    return (false);
  parser_delete_limit(shell);
  return (true);
}
