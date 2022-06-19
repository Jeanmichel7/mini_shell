/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:19:31 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/20 01:12:54 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_error(t_data *data, int i)
{
	ft_errputstr("bash: ", 0, 0, NULL);
	ft_errputstr(data->inputs[i].cmds[0], 0, 0, NULL);
	ft_errputstr(": '", 0, 0, NULL);
	ft_errputstr(data->inputs[i].cmds[1], 0, 0, NULL);
	ft_errputstr("': not a valid identifier", 0, 0, NULL);
	ft_errputstr("\n", 0, 0, NULL);
	error_code = 1;
}

char	*ft_env_split_name(char *str_value, char *str)
{
	char	*name;
	int		j;
	
	name = malloc(sizeof(char) * (str_value - str + 1));
	j = -1;
	while (++j < str_value - str)
		name[j] = str[j];
	name[j] = '\0';
	return (name);
}

void	ft_env(t_data *data, int i)
{
	int	j;

	(void)i;
	j = 0;
	while (data->env[j])
	{
		//printf("%d %s\n", j, data->env[j]);
		write(1, data->env[j], ft_strlen(data->env[j]));
		write(1, "\n", 1);
		j++;
	}
}
