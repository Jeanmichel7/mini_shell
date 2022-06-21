/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:32:33 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/21 02:40:28 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_env(t_data *data, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	while (data->env && data->env[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (data->env && data->env[j])
	{
		new_env[j] = malloc(sizeof(char) * (ft_strlen(data->env[j]) + 1));
		ft_memcpy(new_env[j], data->env[j], ft_strlen(data->env[j]) + 1);
		j++;
	}
	new_env[j] = malloc(sizeof(char) * \
	(ft_strlen(data->inputs[i].cmds[1]) + 1));
	ft_memcpy(new_env[j], data->inputs[i].cmds[1],
		ft_strlen(data->inputs[i].cmds[1]) + 1);
	j++;
	new_env[j] = NULL;
	ft_free_tab(data->env);
	data->env = new_env;
}

int	ft_already_exist(char *name, t_data *data)
{
	int		j;
	char	**temp;

	j = 0;
	while (data->env && data->env[j])
	{
		temp = ft_split(data->env[j], '=');
		if (ft_strlen(name) == ft_strlen(temp[0])
			&& ft_strncmp(name, temp[0], ft_strlen(name)) == 0)
		{
			ft_free_tab(temp);
			return (j);
		}
		ft_free_tab(temp);
		j++;
	}
	return (0);
}

void	ft_sub_export(t_data *data, int i, char *str, char *str_value)
{
	char	*name;
	int		index_value;

	name = ft_env_split_name(str_value, str);
	str_value = str_value + 1;
	if (!((name[0] > 'a' && name[0] < 'z')
			|| (name[0] > 'A' && name[0] < 'Z')))
		ft_export_error(data, i);
	else
	{
		index_value = ft_already_exist(name, data);
		if (index_value)
		{
			free(data->env[index_value]);
			data->env[index_value] = malloc(sizeof(char) * \
				(ft_strlen(data->inputs[i].cmds[1]) + 1));
			ft_memcpy(data->env[index_value], data->inputs[i].cmds[1], \
			ft_strlen(data->inputs[i].cmds[1]) + 1);
		}
		else
			ft_add_env(data, i);
	}
	free(name);
}

void	ft_export(t_data *data, int i)
{
	char	*str;
	char	*str_value;
	int		j;

	str = data->inputs[i].cmds[1];
	if (str == NULL)
	{
		j = 0;
		while (data->env && data->env[j])
		{
			write(1, "declare -x ", 12);
			write(1, data->env[j], ft_strlen(data->env[j]));
			write(1, "\n", 1);
			j++;
		}
	}
	else
	{
		str_value = ft_strchr(str, '=');
		if (str_value != NULL)
			ft_sub_export(data, i, str, str_value);
	}
}
