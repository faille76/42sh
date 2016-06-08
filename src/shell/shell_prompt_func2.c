/*
** shell_prompt_func2.c for func 2 of prompt in /src/shell/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Fri Jun  3 21:14:55 2016 Frederic ODDOU
** Last update Fri Jun  3 21:23:15 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "shell.h"

void			shell_prompt_time(t_shell		*shell)
{
  struct tm		*now_time;
  time_t		now;

  (void)shell;
  now = 0;
  time(&now);
  if ((now_time = localtime(&now)) != NULL)
    printf("%02d:%02d", now_time->tm_hour, now_time->tm_min);
}

void			shell_prompt_echap(t_shell		*shell)
{
  (void)shell;
  printf("\e");
}
