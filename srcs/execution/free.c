/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:02:14 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/20 17:05:28 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_content_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

/*
void	*ft_freetab(char **tab)
{
	int	i;
	i = 0;

	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (NULL);
}
*/

void	ft_free(t_data *data)
{
	ft_free_tab(data->env);
	free(data->inputs);
	//rl_clear_history();
}

void	ft_free_inputs(t_data *data)
{
	free(data->temp);
	free(data->prompt);
}

void	ft_free_section(t_data *data, int i)
{
	int	j;

	j = 0;
	if (!ft_is_builtin(data, i))
		while (data->inputs[i].cmds && data->inputs[i].cmds[j])
		{
			//fprintf(stderr, "%d %d %s same : %d %p %p\n", i, j, data->inputs[i].cmds[j], same_cmd, data->inputs[i].cmds[0], data->inputs[i].cmd_fct);
			if (!(ft_strlen(data->inputs[i].cmds[j]) == ft_strlen(data->inputs[i].cmd_fct)
				&& ft_strncmp(data->inputs[i].cmd_fct, data->inputs[i].cmds[j],
				ft_strlen(data->inputs[i].cmds[j])) == 0))
				free(data->inputs[i].cmds[j]);
			j++;
		}
	free(data->inputs[i].cmds);
	free(data->inputs[i].cmd_fct);
	j = 0;
	while (data->inputs[i].file[j].type != 0)
		free(data->inputs[i].file[j++].name);
	free(data->inputs[i].file);
}