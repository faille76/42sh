/*
** shell_close.c for close in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:30:33 2016 Frederic ODDOU
** Last update Sat May 21 21:46:36 2016 oddou_f
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"
#include "utils.h"
#include "rd.h"

bool		shell_close(t_shell		*shell,
			    unsigned char	value)
{
  if (shell->oldpwd != NULL)
    free(shell->oldpwd);
  shell_commands_free(shell);
  utils_locales_delete_list(shell->locales);
  utils_alias_delete_list(shell->alias);
  utils_jobs_delete_list(shell, shell->jobs);
  utils_history_delete_list(shell->history);
  my_tab_free(shell->path);
  my_tab_free(shell->ae);
  rd_free();
  exit(value);
}
