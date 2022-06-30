/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 02:51:43 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/30 19:59:31 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_sub_check(void)
{
	write(1, "minishell: exit: too many arguments\n", 36);
	write(1, "exit\n", 5);
	g_error_code = 1;
	return (0);
}

int	ft_check_exit_error(t_data *data, int i)
{
	int	j;
	int	k;

	k = 1;
	j = 0;
	while (data->inputs[i].cmds && data->inputs[i].cmds[j])
		j++;
	if (j > 2)
	{
		while (data->inputs[i].cmds && data->inputs[i].cmds[k])
		{
			if (!ft_check_num(data->inputs[i].cmds[k]))
			{
				ft_errputstr("minishell: exit: ", 0, 0, NULL);
				ft_errputstr(data->inputs[i].cmds[k], 0, 0, NULL);
				ft_errputstr(": numeric argument required\n", 0, 0, NULL);
				g_error_code = 255;
				break ;
			}
			else if (ft_check_num(data->inputs[i].cmds[k]))
				return (ft_sub_check());
			k++;
		}
	}
	return (1);
}

int	ft_sub_exit(char *str_code)
{
	int	code;

	code = ft_atoi(str_code);
	g_error_code = code;
	return (code);
}

void	ft_sub_exit2(t_data *data, int i)
{
	ft_errputstr("minishell: exit: ", 0, 0, NULL);
	ft_errputstr(data->inputs[i].cmds[1], 0, 0, NULL);
	ft_errputstr(": numeric argument required\n", 0, 0, NULL);
	g_error_code = 255;
}

void	ft_exit(t_data *data, int i)
{
	char	*str_code;
	int		code;

	if (ft_check_exit_error(data, i))
	{
		code = 2;
		if (data->inputs[i].cmds && data->inputs[i].cmds[1])
		{
			str_code = data->inputs[i].cmds[1];
			if (ft_check_num(str_code))
				g_error_code = ft_sub_exit(str_code);
			else if (g_error_code != 255)
				ft_sub_exit2(data, i);
		}
		if (data->nb_pipe == 0)
		{
			write(1, "exit\n", 5);
			tcsetattr(0, 0, &(data->termios_save));
			data->done = 1;
		}
	}
}
