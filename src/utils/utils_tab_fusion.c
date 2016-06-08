/*
** utils_tab_fusion.c for tab fusion in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Tue May 17 13:10:25 2016 Frederic ODDOU
** Last update Wed May 18 12:55:04 2016 oddou_f
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int		find_char(char			*str,
				  char			c)
{
  int			i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == c)
	return (i);
      i++;
    }
  return (-1);
}

bool			utils_if_fusion(char		**tab)
{
  int			i;
  bool			reponse[2];

  i = 0;
  reponse[0] = false;
  reponse[1] = false;
  if (tab[0] == NULL)
    return (false);
  if ((i = find_char(tab[0], '=')) != -1)
    {
      reponse[0] = true;
      if (tab[0][i + 1] != '\0' || tab[1] != NULL)
	reponse[1] = true;
    }
  else if (tab[1] != NULL && (i = find_char(tab[1], '=')) != -1)
    {
      reponse[0] = true;
      if (tab[1][i + 1] != '\0' || tab[2] != NULL)
	reponse[1] = true;
    }
  else
    reponse[0] = true;
  if (reponse[0] == false)
    return (false);
  return (true);
}

bool			utils_tab_fusion(char		**tab,
					 char		*reponse[2])
{
  int			i;

  i = 0;
  if (tab[0] == NULL)
    return (false);
  if ((i = find_char(tab[0], '=')) != -1)
    {
      reponse[0] = strndup(tab[0], i);
      if (tab[0][i + 1] != '\0')
	reponse[1] = strdup(&tab[0][i + 1]);
      else if (tab[1] != NULL)
	reponse[1] = strdup(tab[1]);
    }
  else if (tab[1] != NULL && (i = find_char(tab[1], '=')) != -1)
    {
      reponse[0] = strdup(tab[0]);
      if (tab[1][i + 1] != '\0')
	reponse[1] = strdup(&tab[1][i + 1]);
      else if (tab[2] != NULL)
	reponse[1] = strdup(tab[2]);
    }
  else
    reponse[0] = strdup(tab[0]);
  return ((reponse[0] == NULL) ? false : true);
}
