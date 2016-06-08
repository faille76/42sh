/*
** utils_get_homepath.c for homepath in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 11 13:29:54 2016 Frederic ODDOU
** Last update Sat May 21 23:50:49 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include "shell.h"

static char		*utils_get_path_current_user()
{
  struct passwd		*pws;

  if ((pws = getpwuid(geteuid())) == NULL)
    return (NULL);
  return (pws->pw_dir);
}

static char		*utils_get_path_username(t_commands	*commands)
{
  struct passwd		*pws;
  char			*str;
  int			i;

  i = 0;
  if ((str = strdup(&commands->str[1])) == NULL)
    return (NULL);
  while (str[i] != '\0' && str[i] != '/')
    i++;
  str[i] = '\0';
  if ((pws = getpwnam(str)) == NULL)
    {
      fprintf(stderr, "Unknown user: %s.\n", str);
      free(str);
      return (NULL);
    }
  free(str);
  return (pws->pw_dir);
}

static char		*utils_convert_home(t_commands		*commands,
					    char		*path)
{
  char			*new;
  size_t		len;
  int			i;

  i = 0;
  while (commands->str[i] != '\0' && commands->str[i] != '/')
    i++;
  len = strlen(&commands->str[i]) + strlen(path) + 1;
  if ((new = malloc(sizeof(char) * len)) == NULL)
    return (NULL);
  new = memset(new, '\0', len);
  strcat(new, path);
  strcat(new, &commands->str[i]);
  free(commands->str);
  commands->str = new;
  return (commands->str);
}

char			*utils_get_homepath(t_commands		*commands)
{
  char			*path_user;

  if (!strcmp(commands->str, "~") || !strncmp(commands->str, "~/", 2))
    {
      if ((path_user = utils_get_path_current_user()) == NULL)
	return (NULL);
    }
  else
    {
      if ((path_user = utils_get_path_username(commands)) == NULL)
	return (NULL);
    }
  return (utils_convert_home(commands, path_user));
}
