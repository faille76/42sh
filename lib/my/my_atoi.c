/*
** my_atoi.c for atoi in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 15:20:52 2016 Frederic ODDOU
** Last update Thu May 05 15:23:08 2016 oddou_f
*/

int			my_atoi(char			*str)
{
  int			i;
  int			neg;
  int			nb;

  i = neg = nb = 0;
  while (str[i] != '\0' && !(str[i] >= '0' && str[i] <= '9'))
    {
      if (str[i] == '-')
	neg++;
      i++;
    }
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
      nb = (nb * 10) + (str[i] - '0');
      i++;
    }
  return (nb);
}
