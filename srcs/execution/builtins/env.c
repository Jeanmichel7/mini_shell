/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:19:31 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/24 20:10:13 by jrasser          ###   ########.fr       */
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
	g_error_code = 1;
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
	while (data->env && data->env[j])
	{
		write(1, data->env[j], ft_strlen(data->env[j]));
		write(1, "\n", 1);
		j++;
	}
}

void	ft_display_export(t_data *data, int *j)
{
	write(1, "declare -x ", 12);
	write(1, data->env[*j], ft_strlen(data->env[*j]));
	write(1, "\n", 1);
	*j += 1;
}
