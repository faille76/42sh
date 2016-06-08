/*
** tab.c for tab in lib/getch/src/rd/
**
** Made by Frederic ODDOU
** Login   <login_x@epitech.eu>
**
** Started on  Tue May 24 23:20:11 2016 Frederic ODDOU
** Last update Sat Jun  4 18:11:23 2016 Frederic ODDOU
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include "rd.h"

static char	*get_ptr(char		*cursor,
			 char		*first)
{
  char		*new;
  size_t	len;
  char		*nav;

  nav = cursor;
  while (nav != first && (nav == cursor ||
			  (*nav != ' ' && *nav != '\t' &&
			   *nav != '"' && *nav != '\'')))
    nav = nav - 1;
  if (nav != cursor &&
      (*nav == ' ' || *nav == '\t' || *nav == '"' || *nav == '\''))
    nav = nav + 1;
  if (*nav == '\0' || (len = (cursor - nav)) <= 0)
    return (NULL);
  if ((new = malloc(sizeof(char) * (len + 2))) == NULL)
    return (NULL);
  memset(new, '\0', len + 2);
  strncpy(new, nav, len);
  strcat(new, "*");
  return (new);
}

static void		auto_fill(t_rd *rd, char *str, glob_t *globbuf)
{
  unsigned int		i;

  i = strlen(str) - 1;
  while (globbuf->gl_pathv[0][i] != '\0')
    {
      rd_put(rd, globbuf->gl_pathv[0][i]);
      rd_add_char(rd, globbuf->gl_pathv[0][i]);
      rd->curs += 1;
      i++;
    }
  rd_disp(rd);
}

static void		max_fill(t_rd *rd, glob_t *globbuf)
{
  unsigned int		i;
  unsigned int		max;

  i = 0;
  printf("\n");
  while (globbuf->gl_pathv[i] != NULL)
    {
      if (strlen(globbuf->gl_pathv[i]) > max)
	max = strlen(globbuf->gl_pathv[i]);
      i++;
    }
  i = 0;
  while (globbuf->gl_pathv[i] != NULL)
    {
      printf("%-*s", max + 2, globbuf->gl_pathv[i]);
      if (i % 8 == 0)
	printf("\n");
      i++;
    }
  printf("\n$> ");
  fflush(stdout);
  rd_disp(rd);
}

int     		rd_tab(t_rd *rd, int key)
{
  char			*str;
  glob_t		globbuf;

  if ((str = get_ptr(&(RD_LINE)[rd->curs], RD_LINE)) == NULL)
    return (0);
  if (glob(str, 0, NULL, &globbuf) != 0)
    return (0);
  if (globbuf.gl_pathv == NULL)
    return (0);
  if (globbuf.gl_pathc == 1)
    auto_fill(rd, str, &globbuf);
  else if (globbuf.gl_pathc > 1)
    max_fill(rd, &globbuf);
  free(str);
  globfree(&globbuf);
  (void)key;
  return (0);
}
