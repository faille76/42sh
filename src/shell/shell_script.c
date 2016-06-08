/*
** shell_script.c for shell script in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May 23 15:06:32 2016 Frederic ODDOU
** Last update Mon May 23 15:18:08 2016 oddou_f
*/

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "my.h"

static void		shell_script_get_av(t_shell	*shell,
					    int		ac,
					    char	**av)
{
  int			i;
  char			name[10];
  char			*reponse[2];

  i = 2;
  while (i < ac)
    {
      memset(name, '\0', 10);
      snprintf(name, 10, "%d", i - 1);
      reponse[0] = strdup(name);
      reponse[1] = strdup(av[i]);
      shell->locales = utils_locales_add_left(reponse, shell->locales);
      i++;
    }
}

bool			shell_script(t_shell	*shell,
				     int	ac,
				     char	**av)
{
  int			fd;
  char			*str;
  int			size;
  char			*next;

  if ((fd = open(av[1], O_RDONLY)) == -1)
    {
      fprintf(stderr, ERROR_NOSCRIPT, av[1]);
      return (false);
    }
  shell_script_get_av(shell, ac, av);
  size = 0;
  str = NULL;
  if ((next = strdup("")) == NULL)
    return (false);
  while ((str = get_next_line(fd, &next, &size)) != NULL)
    {
      if (strlen(str) > 0)
	shell->history = utils_history_add_right(shell->history, strdup(str));
      shell_step(shell, str);
    }
  free(next);
  close(fd);
  return (true);
}
