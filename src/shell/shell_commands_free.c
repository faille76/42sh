/*
** shell_commands_free.c for free commands in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 29 22:50:19 2016 Frederic ODDOU
** Last update Fri Apr 29 23:53:32 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"

void			shell_commands_free(t_shell		*shell)
{
  if (shell->commands != NULL)
    utils_commands_delete_list(shell->commands);
  else if (shell->list != NULL)
    utils_list_delete_list(shell->list);
  shell->commands = NULL;
  shell->list = NULL;
}
