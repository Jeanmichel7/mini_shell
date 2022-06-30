/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:06:34 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/30 16:28:56 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_quit(void)
{
	write(1, "Quit: 3\n", 8);
}

void	ft_close_redir(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].file[j].type != 0)
		close(data->inputs[i].file[j++].fd);
}

void	ft_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		if (g_error_code == -2)
		{
			rl_replace_line("", 0);
			rl_redisplay();
			g_error_code = 130;
			close(0);
		}
		else if (g_error_code != -1)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_error_code = 130;
	}
	if (sig == SIGQUIT && g_error_code != -1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		ft_sig_quit();
}

int	ft_init_term(t_data *data)
{
	int				rc;
	struct termios	termios;

	signal(SIGINT, &ft_handle_signal);
	signal(SIGQUIT, &ft_handle_signal);
	rc = tcgetattr(0, &data->termios_save);
	termios = data->termios_save;
	termios.c_lflag &= ~ECHOCTL;
	termios.c_cc[VMIN] = 100;
	termios.c_cc[VTIME] = 100;
	rc = tcsetattr(0, 0, &termios);
	return (rc);
}
