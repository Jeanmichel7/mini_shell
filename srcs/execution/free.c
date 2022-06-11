/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:02:14 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/11 15:22:42 by jrasser          ###   ########.fr       */
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
	{
		while (data->inputs[i].cmds && data->inputs[i].cmds[j])
			free(data->inputs[i].cmds[j++]);
	}
	j = 0;
	while (data->inputs[i].file[j].type != 0)
		free(data->inputs[i].file[j++].name);
	free(data->inputs[i].cmds);
	free(data->inputs[i].cmd_fct);
	free(data->inputs[i].file);
}