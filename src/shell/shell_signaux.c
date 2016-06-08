/*
** shell_signal.c for signaux in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  1 22:28:17 2016 Frederic ODDOU
** Last update Sun May 22 16:44:56 2016 oddou_f
*/

#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

void		shell_signal(bool	ign)
{
  signal(SIGQUIT, (ign) ? SIG_IGN : SIG_DFL);
  if (isatty(STDIN_FILENO))
    {
      signal(SIGINT, (ign) ? SIG_IGN : SIG_DFL);
      signal(SIGTSTP, (ign) ? SIG_IGN : SIG_DFL);
      signal(SIGTTIN, (ign) ? SIG_IGN : SIG_DFL);
      signal(SIGTTOU, (ign) ? SIG_IGN : SIG_DFL);
      signal(SIGTERM, (ign) ? SIG_IGN : SIG_DFL);
    }
}
