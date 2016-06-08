/*
** utils_get_history.c for get history in /src/utils/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Sat Jun  4 14:54:22 2016 Frederic ODDOU
** Last update Sat Jun  4 15:14:39 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "my.h"

static char		*utils_get_history_number(t_past	*history,
						  char		*str)
{
  unsigned int		nbr;

  nbr = my_atoi(str);
  if (history == NULL || history->id < nbr)
    return (NULL);
  while (history != NULL)
    {
      if (history->id == nbr)
	return (history->str);
      history = history->prev;
    }
  return (NULL);
}

static char		*utils_get_history_past(t_past		*history,
						char		*str)
{
  unsigned int		nbr;
  unsigned int		i;

  i = 1;
  nbr = my_atoi(&str[i]);
  if (history == NULL)
    return (NULL);
  while (history != NULL)
    {
      if (i++ == nbr)
	return (history->str);
      history = history->prev;
    }
  return (NULL);
}

static char		*utils_get_history_value(t_past		*history,
						 char		*str)
{
  size_t		len;

  len = strlen(str);
  if (history == NULL)
    return (NULL);
  while (history != NULL)
    {
      if (!strncmp(history->str, str, len))
	return (history->str);
      history = history->prev;
    }
  return (NULL);
}

static char		*utils_get_history_last(t_past		*history)
{
  if (history == NULL)
    return (NULL);
  return (history->str);
}

char			*utils_get_history(t_shell		*shell,
					   char			*str)
{
  char			*new;
  t_past		*history;

  history = shell->history;
  if (str == NULL || strncmp(str, "!", 1) || history == NULL)
    return (NULL);
  new = str + 1;
  if (*new == '!')
    return (utils_get_history_last(history->prev));
  else if (*new == '-')
    return (utils_get_history_past(history->prev, new));
  else if (*new >= '0' && *new <= '9')
    return (utils_get_history_number(history->prev, new));
  return (utils_get_history_value(history->prev, new));
}
