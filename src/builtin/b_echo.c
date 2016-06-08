/*
** b_echo.c for echo in /src/builtin/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Wed May 25 23:18:31 2016 Frederic ODDOU
** Last update Fri Jun  3 23:35:12 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

static t_echo_type	g_echo_type[] =
  {
    {"x", 'x'},
    {"d", 'd'},
    {"\0", '0'},
    {0, 0}
  };

static long int		b_echo_calc(char 		*str,
				    long int		i)
{
  char			*nb;
  long int		tmp;
  int			j;

  tmp = i;
  if (str[i] == '\0' || (nb = malloc(sizeof(char))) == NULL)
    return (i);
  nb[0] = '\0';
  j = 0;
  while (str[i] >= '0' && str[i] <= '9')
    {
      if ((nb = realloc(nb, sizeof(char) * (strlen(nb) + 2))) == NULL)
	return (i);
      nb[j++] = str[i++];
      nb[j] = '\0';
    }
  if (str[tmp - 1] == 'x')
    printf("%c", base_converter(nb, 16));
  if (str[tmp - 1] == '0')
    printf("%c", base_converter(nb, 8));
  if (str[tmp - 1] == 'd')
    printf("%c", base_converter(nb, 10));
  free(nb);
  return (i);
}

static char		*b_echo_get_elem_from_tab(char c)
{
  short			i;

  i = 0;
  while (g_echo_type[i].str != NULL)
    {
      if (g_echo_type[i].c == c)
	return (g_echo_type[i].str);
      i++;
    }
  return (NULL);
}

static long int		b_echo_check_param(char			*str,
					   char			param)
{
  long int		i;

  if (str[0] != '-' && param == 'n')
    return (EXIT_FAILURE);
  else if (str[0] != '-' && param == 'e')
    return (EXIT_FAILURE);
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == param)
	return (EXIT_SUCCESS);
      i++;
    }
  return (EXIT_FAILURE);
}

static void		b_echo_print(char			*str)
{
  long int		i;
  char			*type;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '\\' &&
	  (type = b_echo_get_elem_from_tab(str[i + 1])) != NULL)
	{
	  if (str[i + 1] == 'x' || str[i + 1] == '0' || str[i + 1] == 'd')
	    i = b_echo_calc(str, i + 2);
	  else
	    {
	      printf("%s", type);
	      i += 2;
	    }
	}
      else
	{
	  printf("%c", str[i]);
	  i++;
	}
    }
}

int			b_echo(int			ac,
			       char			**av,
			       t_shell			*shell)
{
  long int		i;

  if (!shell->write)
    return (EXIT_SUCCESS);
  if (ac == 1)
    {
      printf("\n");
      return (EXIT_SUCCESS);
    }
  i = 1;
  while (av[i] != NULL)
    {
      if ((i == 1 && av[i][0] != '-' ) || i != 1 ||
	  (av[i][0] == '-' &&
	   b_echo_check_param(av[1], 'n') != EXIT_SUCCESS))
	b_echo_print(av[i]);
      if ((av[i][0] == '-' &&
	   b_echo_check_param(av[1], 'n') != EXIT_SUCCESS) ||
	  (av[i][0] != '-' && av[i + 1] != NULL))
	printf(" ");
      i++;
    }
  if (av[1] != NULL && b_echo_check_param(av[1], 'n') == EXIT_FAILURE)
    printf("\n");
  return (EXIT_SUCCESS);
}
