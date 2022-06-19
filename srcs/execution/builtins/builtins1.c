/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:24:18 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/20 01:44:42 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_data *data, int i)
{
	int	j;
	int	newline;

	newline = 1;
	j = 1;
	while (data->inputs[i].cmds[j])
	{
		if (ft_strlen(data->inputs[i].cmds[j]) != 2
		|| strncmp(data->inputs[i].cmds[j], "-n", 2) != 0)
		{
			write(1, data->inputs[i].cmds[j], ft_strlen(data->inputs[i].cmds[j]));
			if (data->inputs[i].cmds[j + 1])
				write(1, " ", 1);
		}
		else
			newline = 0;
		j++;
	}
	if (newline)
		write(1, "\n", 1);
}

void	ft_cd(t_data *data, int i)
{
	char	*home;
	char	**temp;
	int		j;

	if (data->inputs[i].cmds[1] == NULL)
	{
		j = 0;
		while (data->env && data->env[j])
		{
			temp = ft_split(data->env[j], '=');
			if (4 == ft_strlen(temp[0])
				&& ft_strncmp(temp[0], "HOME", 4) == 0)
			{
				home = malloc(sizeof(char) * (ft_strlen(temp[1]) + 1));
				ft_memcpy(home, temp[1], ft_strlen(temp[1]) + 1);
				ft_free_tab(temp);
				break;
			}
			ft_free_tab(temp);
			j++;
		}
		chdir(home);
		free(home);
	}
	else
		chdir(data->inputs[i].cmds[1]);
}

void	ft_pwd(t_data *data, int i)
{
	char	str[500];
	
	(void)data;
	(void)i;
	getcwd(str, 500);
	//printf("%s", str);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	ft_sub_exit(int code, char *str_code)
{
	char				*code_ptr;
	long unsigned int	j;

	code_ptr = ft_putunbr_base(code, "0123456789abcdef");
	write(1, "[processus terminé avec le code " , 33);
	write(1, str_code, ft_strlen(str_code));
	write(1, " (0x", 5);
	j = 0;
	while (j < 8 - ft_strlen(str_code))
	{
		write(1, "0", 1);
		j++;
	}
	write(1, code_ptr, ft_strlen(code_ptr));
	write(1, ")]\n" , 4);
	error_code = code;
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
}
