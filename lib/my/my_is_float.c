/*
** my_str_to_float.c for my in /home/josso/rendu/psu/PSU_2015_42sh
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed May 25 14:04:03 2016 Arthur Josso
** Last update Wed May 25 14:36:17 2016 Arthur Josso
*/

#include <stdbool.h>

bool	is_float(char const	*str)
{
  int  	nb_dot;
  int  	i;

  nb_dot = 0;
  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	{
	  if (str[i] == '.')
	    nb_dot++;
	  else if (i != 0)
	    return (false);
	  else if (str[i] != '-')
	    return (false);
	}
      i++;
    }
  if (nb_dot > 1)
    return (false);
  return (true);
}
