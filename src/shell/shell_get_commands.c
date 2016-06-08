/*
** shell_get_commands.c for shell_get_commands in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:38:22 2016 Frederic ODDOU
** Last update Tue May 24 16:32:29 2016 oddou_f
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "utils.h"
#include "my.h"
#include "shell.h"
#include "parser.h"
#include "rd.h"

static t_key	g_keys[] =
  {
    {"[A", K_UP},
    {"[B", K_DOWN},
    {"[D", K_LEFT},
    {"[C", K_RIGHT},
    {NULL, K_UNK},
  };

void			shell_step(t_shell			*shell,
				   char				*str)
{
  if (str != NULL)
    {
      shell_commands_free(shell);
      if (parser_control(shell, str) == false)
	shell->last_return = EXIT_FAILURE;
      free(str);
      shell_list_treat(shell);
      shell_commands_free(shell);
      if (shell->exit_active == true)
	{
	  printf("exit\n");
	  shell_close(shell, shell->last_return);
	}
    }
}

bool		shell_get_commands_rd(t_shell			*shell,
				      const char		*line)
{
  char		*str;

  str = NULL;
  utils_special_alias_execute(shell, "postcmd");
  shell_background(shell);
  if ((str = strdup(line)) == NULL)
    return (false);
  if (strlen(str) > 0)
    shell->history = utils_history_add_right(shell->history, strdup(line));
  shell_step(shell, str);
  return (true);
}

bool		shell_get_commands(t_shell			*shell)
{
  const char	*line;

  shell_prompt(shell);
  while (42)
    {
      if ((line = rd_line(STDOUT_FILENO, g_keys)) != NULL)
	{
	  if (shell_get_commands_rd(shell, line) == false)
	    {
	      rd_free();
	      return (false);
	    }
	}
      else if (utils_locales_find_elem("ignoreeof", shell->locales) != NULL)
	printf(MESS_CTRLD, NAME_SHELL);
      else
	{
	  printf("exit\n");
	  rd_free();
	  return (true);
	}
      shell_prompt(shell);
    }
  rd_free();
  return (true);
}

bool			shell_get_commands_moul(t_shell		*shell)
{
  char			*str;
  int			size;
  char			*next;

  size = 0;
  str = NULL;
  if ((next = strdup("")) == NULL)
    return (false);
  shell_prompt(shell);
  while ((str = get_next_line(STDIN_FILENO, &next, &size)) != NULL)
    {
      utils_special_alias_execute(shell, "postcmd");
      shell_background(shell);
      if (strlen(str) > 0)
	shell->history = utils_history_add_right(shell->history, strdup(str));
      shell_step(shell, str);
      shell_prompt(shell);
    }
  free(next);
  return (true);
}
