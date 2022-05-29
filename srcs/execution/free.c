/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:02:14 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/29 22:04:17 by jrasser          ###   ########.fr       */
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

	i = 0;
	while (i <= data->nb_pipe)
	{
		free(data->inputs[i].file);
		free(data->inputs[i].cmds);
		i++;
	}
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
