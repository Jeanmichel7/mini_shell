/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:02:14 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/27 21:38:00 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
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

void	ft_free(t_data *data)
{
	ft_free_tab(data->env);
	free(data->inputs);
}

void	ft_free_inputs(t_data *data)
{
	free(data->temp);
	if (data->color_prompt && !data->chang_color_prompt)
	{
		data->chang_color_prompt = 0;
		free(data->prompt);
	}
}

void	ft_free_section(t_data *data, int i)
{
	int	j;

	j = -1;
	while (data->inputs[i].cmds && data->inputs[i].cmds[++j])
	{
		if (!(ft_strlen(data->inputs[i].cmds[j]) == \
			ft_strlen(data->inputs[i].cmd_fct)
				&& ft_strncmp(data->inputs[i].cmd_fct, data->inputs[i].cmds[j],
					ft_strlen(data->inputs[i].cmds[j])) == 0))
			free(data->inputs[i].cmds[j]);
	}
	free(data->inputs[i].cmds);
	free(data->inputs[i].cmd_fct);
	j = -1;
	while (data->inputs[i].file[++j].type != 0)
	{
		if (ft_strncmp(data->inputs[i].file[j].name, "herdoc.txt", 10) != 0)
			free(data->inputs[i].file[j].name);
		else
		{
			close (data->inputs[i].file[j].fd);
			unlink("herdoc.txt");
		}
	}
	free(data->inputs[i].file);
}
