/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:57:22 by jrasser           #+#    #+#             */
/*   Updated: 2022/07/07 15:11:15 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_line(t_data *data, int index_target)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (data->env && data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (data->env && data->env[i])
	{
		if (i != index_target)
		{
			new_env[j] = malloc(sizeof(char) * (ft_strlen(data->env[i]) + 1));
			ft_memcpy(new_env[j], data->env[i], ft_strlen(data->env[i]) + 1);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
    ft_free_tab(data->env);
	data->env = new_env;
}

void	ft_unset(t_data *data, int i)
{
	int		j;
	char	*str;
	char	**temp;

	str = data->inputs[i].cmds[1];
	j = 0;
	while (data->env && data->env[j])
	{
		temp = ft_split(data->env[j], '=');
		if (ft_strlen(str) == ft_strlen(temp[0])
			&& ft_strncmp(str, temp[0], ft_strlen(str)) == 0)
		{
			ft_free_tab(temp);
			ft_remove_line(data, j);
			break ;
		}
		ft_free_tab(temp);
		j++;
	}
}
