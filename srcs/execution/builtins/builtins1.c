/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:24:18 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/27 22:07:31 by jrasser          ###   ########.fr       */
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
			write(1, data->inputs[i].cmds[j],
				ft_strlen(data->inputs[i].cmds[j]));
			if (data->inputs[i].cmds[j + 1])
				write(1, " ", 1);
		}
		else
			newline = 0;
		j++;
	}
	if (newline)
		write(1, "\n", 1);
	g_error_code = 0;
}

char	*ft_sub_cd(t_data *data, int *j, char *home)
{
	char	**temp;

	temp = ft_split(data->env[*j], '=');
	if (4 == ft_strlen(temp[0])
		&& ft_strncmp(temp[0], "HOME", 4) == 0)
	{
		home = malloc(sizeof(char) * (ft_strlen(temp[1]) + 1));
		ft_memcpy(home, temp[1], ft_strlen(temp[1]) + 1);
		ft_free_tab(temp);
		return (home);
	}
	ft_free_tab(temp);
	*j += 1;
	return (NULL);
}

void	ft_cd(t_data *data, int i)
{
	char	*home;
	int		j;

	home = NULL;
	if (data->inputs[i].cmds[1] == NULL)
	{
		j = 0;
		while (data->env && data->env[j])
		{
			home = ft_sub_cd(data, &j, home);
			if (home)
				break ;
		}
		if (data->nb_pipe == 0)
			chdir(home);
		free(home);
	}
	else if (chdir(data->inputs[i].cmds[1]) == -1)
	{
		write(1, "bash: cd: ", 11);
		write(1, data->inputs[i].cmds[1], ft_strlen(data->inputs[i].cmds[1]));
		write(1, ": No such file or directory\n", 29);
		g_error_code = 1;
	}
}

void	ft_pwd(t_data *data, int i)
{
	char	str[500];

	(void)data;
	(void)i;
	getcwd(str, 500);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}
