/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 02:51:43 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/21 02:51:59 by jrasser          ###   ########.fr       */
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

void	ft_exit(t_data *data, int i)
{
	char	*str_code;
	int		code;

	code = 2;
	if (data->inputs[i].cmds && data->inputs[i].cmds[1])
	{
		str_code = data->inputs[i].cmds[1];
		if (str_code[0] >= '0' && str_code[0] <= '9')
			code = ft_atoi(str_code);
		else
		{
			str_code[0] = '2';
			str_code[1] = '\0';
		}
		ft_sub_exit(code, str_code);
		free(str_code);
	}
	data->done = 1;
}
