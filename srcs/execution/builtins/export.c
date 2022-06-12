/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:32:33 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/12 23:55:16 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_env(t_data *data, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	while (data->env[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (data->env[j])
	{
		new_env[j] = malloc(sizeof(char) * (ft_strlen(data->env[j]) + 1));
		ft_memcpy(new_env[j], data->env[j], ft_strlen(data->env[j]) + 1);
		j++;
	}
	new_env[j] = data->inputs[i].cmds[1];
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

/*export NAME="valeur"*/
void	ft_export(t_data *data, int i)
{
	char	*str;
	char	*name;
	char	*str_value;
	int		index_value;

	str = data->inputs[i].cmds[1];
	if (str == NULL)
		fprintf(stderr, "pas d'arg je fais quoi ? (declare -x NAME=fdesfsdfsdf)\n");
	else
	{
		str_value = ft_strchr(str, '=');
		if (str_value == NULL)
			ft_export_error(data, i);
		else
		{
			name = ft_env_split_name(str_value, str);
			str_value = str_value + 1;
			//fprintf(stderr, "str export : %s\n", str);
			//fprintf(stderr, "export name : %s\n", name);
			//fprintf(stderr, "export value : %s\n", str_value);
			if (!((name[0] > 'a' && name[0] < 'z')
				|| (name[0] > 'A' && name[0] < 'Z')))
				ft_export_error(data, i);
			else
			{
				index_value = ft_already_exist(name, data);
				free(name);
				if (index_value)
					data->env[index_value] = data->inputs[i].cmds[1];
				else
					ft_add_env(data, i);
			}
		}
	}
}
