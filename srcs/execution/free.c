/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:02:14 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/30 01:55:10 by jrasser          ###   ########.fr       */
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

void	*ft_freetab(char **tab)
{
	int	i;
	i = 0;

	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

void	ft_free(t_data *data)
{
	int	i;

	free(data->inputs);
	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	rl_clear_history();
}

void	ft_free_section(t_data *data)
{
	/*
	int	i;

	i = 0;
	while (i <= data->nb_pipe)
	{
		free(data->inputs[i].file);
		free(data->inputs[i].cmds);
		i++;
	}
	*/
	free(data->temp);
	free(data->prompt);
}

void	ft_free_sec_pipe(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].cmds[j])
	{
		//free(data->inputs[i].cmds[j]);
		j++;
	}
	if (!ft_is_builtin(data, i))
	{
		free(data->inputs[i].cmd_fct);
		free(data->inputs[i].cmds);
		free(data->inputs[i].file);
	}
}