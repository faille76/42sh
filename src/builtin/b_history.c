/*
** b_history.c for env in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 13:40:11 2016 Frederic ODDOU
** Last update Sat May 21 21:44:58 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "shell.h"
#include "utils.h"

int			b_history(int			ac,
				  char			**av,
				  t_shell		*shell)
{
  t_past		*history;
  struct tm		*now_time;

  if (!shell->write)
    return (EXIT_SUCCESS);
  history = utils_history_go_back(shell->history);
  while (history != NULL)
    {
      printf("%u\t", history->id);
      if ((now_time = localtime(&history->date)) != NULL)
	printf("%02d:%02d\t", now_time->tm_hour, now_time->tm_min);
      printf("%s\n", history->str);
      history = history->next;
    }
  (void)ac;
  (void)av;
  return (EXIT_SUCCESS);
}
