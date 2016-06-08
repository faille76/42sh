/*
** parser_commands_double_quotes.c for double quotes in /src/parser/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Fri Jun  3 22:01:00 2016 Frederic ODDOU
** Last update Fri Jun  3 23:46:22 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "parser.h"

static t_quote_type	g_quotes_type[] =
  {
    {"\\a", "\a"},
    {"\\b", "\b"},
    {"\\t", "\t"},
    {"\\n", "\n"},
    {"\\v", "\v"},
    {"\\f", "\f"},
    {"\\r", "\r"},
    {NULL, NULL}
  };

static char		*parser_quotes_treat_find_tab(char	*str)
{
  short			i;

  i = 0;
  while (g_quotes_type[i].in != NULL)
    {
      if (!strncmp(str, g_quotes_type[i].in, strlen(g_quotes_type[i].in)))
	return (g_quotes_type[i].to);
      i++;
    }
  return (NULL);
}

static void		parser_replace_quotes(char		*str,
					      char		replace)
{
  unsigned int		i;

  i = 1;
  *str = replace;
  while (str[i] != '\0')
    {
      str[i] = str[i + 1];
      i++;
    }
}

static void		parser_quotes_treat(char		*str)
{
  unsigned int		i;
  char			*replace;

  i = 0;
  while (str[i] != '\0')
    {
      replace = NULL;
      if ((replace = parser_quotes_treat_find_tab(&str[i])) != NULL)
	parser_replace_quotes(&str[i], replace[0]);
      i++;
    }
}

void		parser_commands_double_quotes(t_commands	*commands)
{
  while (commands != NULL)
    {
      if (commands->index_delim == ID_DOUBLE_QUOTE)
	parser_quotes_treat(commands->str);
      commands = commands->next;
    }
}
