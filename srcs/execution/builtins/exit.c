/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 02:51:43 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/30 17:17:18 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sub_exit(int code, char *str_code)
{
	char				*code_ptr;
	long unsigned int	j;

	code_ptr = ft_putunbr_base(code, "0123456789abcdef");
	write(1, "[processus terminé avec le code ", 33);
	write(1, str_code, ft_strlen(str_code));
	write(1, " (0x", 5);
	j = 0;
	while (j < 8 - ft_strlen(str_code))
	{
		write(1, "0", 1);
		j++;
	}
	write(1, code_ptr, ft_strlen(code_ptr));
	write(1, ")]\n", 4);
	g_error_code = code;
	free(code_ptr);
}

int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_exit_error(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].cmds && data->inputs[i].cmds[j])
		j++;
	if (j > 2)
	{
		if (ft_check_num(data->inputs[i].cmds[1])
			&& !ft_check_num(data->inputs[i].cmds[2]))
		{
			ft_errputstr("minishell: exit: too many arguments\n", 0, 0, NULL);
			write(1, "exit\n", 5);
			g_error_code = 1;
			return (0);
		}
		else if (!ft_check_num(data->inputs[i].cmds[1]))
		{
			ft_errputstr("minishell: exit: ", 0, 0, NULL);
			ft_errputstr(data->inputs[i].cmds[1], 0, 0, NULL);
			ft_errputstr(": numeric argument required\n", 0, 0, NULL);
			g_error_code = 255;
		}
	}
	return (1);
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
				code = ft_atoi(str_code);
			else
			{
				str_code[0] = '2';
				str_code[1] = '\0';
			}
			ft_sub_exit(code, str_code);
		}
		if (data->nb_pipe == 0)
		{
			write(1, "exit\n", 5);
			data->done = 1;
		}
	}
}
