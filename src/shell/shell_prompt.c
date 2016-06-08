/*
** shell_prompt.c for prompt in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  8 18:29:17 2016 Frederic ODDOU
** Last update Tue May 24 13:42:48 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>
#include "shell.h"
#include "utils.h"

static t_ps1		g_ps1[] =
  {
    {"\\u", &shell_prompt_user},
    {"\\v", &shell_prompt_version},
    {"$?", &shell_prompt_ret_value},
    {"\\W", &shell_prompt_directory},
    {"\\l", &shell_prompt_nb_line},
    {"\\e", &shell_prompt_echap},
    {"\\033", &shell_prompt_echap},
    {"\\t", &shell_prompt_time},
    {NULL, NULL},
  };

static t_ps1		*shell_prompt_find(char			*str)
{
  short			find;

  find = 0;
  while (g_ps1[find].replace != NULL)
    {
      if (!strncmp(g_ps1[find].replace, str, strlen(g_ps1[find].replace)))
	{
	  if (g_ps1[find].func != NULL)
	    return (&g_ps1[find]);
	}
      find++;
    }
  return (NULL);
}

static void		shell_prompt_write(t_shell		*shell,
					   char			*str)
{
  unsigned int		i;
  t_ps1			*ps1;

  i = 0;
  while (str[i] != '\0')
    {
      if ((ps1 = shell_prompt_find(&str[i])) != NULL)
	{
	  (ps1->func)(shell);
	  i += strlen(ps1->replace) - 1;
	}
      else
	printf("%c", str[i]);
      i++;
    }
}

void			shell_prompt(t_shell			*shell)
{
  t_locales		*loc;
  char			*ps1;

  utils_special_alias_execute(shell, "precmd");
  if (isatty(STDIN_FILENO))
    {
      ps1 = "?> ";
      if ((loc = utils_locales_find_elem("PS1", shell->locales)) != NULL)
	ps1 = loc->value;
      shell_prompt_write(shell, ps1);
      fflush(stdout);
    }
}
