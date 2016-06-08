/*
** utils_get_var.c for utils get var in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 21:32:58 2016 Frederic ODDOU
** Last update Sun Jun  5 17:50:24 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"
#include "my.h"

static char		*utils_parser_var_normal(char		*str,
						 char		s)
{
  char			c[2];

  c[0] = s;
  c[1] = '\0';
  return (my_str_realloc(str, c));
}

static char		*utils_parser_var_get_var(t_shell	*shell,
						  char		*str,
						  char		*new,
						  int		*i)
{
  char			*find;
  char			*var;

  find = var = NULL;
  if (utils_get_acolade_count(&str[*i + 1]) != -1)
    find = utils_get_acolade(&str[*i + 1]);
  if ((var = utils_get_var_find(shell,
				(find != NULL) ? find : &str[*i + 1])) == NULL)
    {
      if (new != NULL)
	free(new);
      return (NULL);
    }
  if (find != NULL)
    *i += utils_get_acolade_count(&str[*i + 1]) + 1;
  else
    *i += (int)strlen(&str[*i]) - 1;
  new = my_str_realloc(new, var);
  if (find != NULL)
    free(find);
  return (new);
}

static char		*utils_parser_var_return_val(t_shell	*shell,
						     char	*str,
						     char	*new,
						     int	*i)
{
  char			*val;

  if ((val = malloc(sizeof(char) * 4)) == NULL)
    return (new);
  val = memset(val, '\0', 4);
  snprintf(val, 4, "%d", shell->last_return);
  new = my_str_realloc(new, val);
  free(val);
  if (!strncmp(&str[*i], "$?", 2))
    *i += 1;
  else if (!strncmp(&str[*i], "${?}", 4))
    *i += 3;
  return (new);
}

static char		*utils_parse_var(t_shell		*shell,
					 char			*str,
					 t_commands		*commands)
{
  int			i;
  char			*new;

  i = 0;
  new = NULL;
  while (str[i] != '\0')
    {
      if (!strncmp(&str[i], "$?", 2) || !strncmp(&str[i], "${?}", 4))
	new = utils_parser_var_return_val(shell, str, new, &i);
      else if (str[i] == '$')
	new = utils_parser_var_get_var(shell, str, new, &i);
      else
	new = utils_parser_var_normal(new, str[i]);
      i++;
    }
  free(commands->str);
  commands->str = new;
  return (new);
}

char			*utils_get_var(t_shell			*shell,
				       t_commands		*commands)
{
  if (GET_ID(commands->index_delim) == ID_SIMPLE_QUOTE)
    return (commands->str);
  if (commands->str == NULL)
    return (NULL);
  if (strstr(commands->str, "$"))
    commands->str = utils_parse_var(shell, commands->str, commands);
  if (commands->str != NULL && !strncmp(commands->str, "~", 1))
    return (utils_get_homepath(commands));
  return (commands->str);
}
