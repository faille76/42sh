/*
** my_count_char.c for count char in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 29 23:03:26 2016 Frederic ODDOU
** Last update Fri Apr 29 23:09:29 2016 oddou_f
*/

unsigned int	my_count_char(char		*str,
			      char		c)
{
  unsigned int	nb;

  nb = 0;
  while (*str)
    {
      if (*str == c)
	nb++;
      str = str + 1;
    }
  return (nb);
}
