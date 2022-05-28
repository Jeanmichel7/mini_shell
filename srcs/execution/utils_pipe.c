/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:58:11 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/28 22:26:21 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_redir(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].file[j].type != 0)
	{
		//if (data->inputs[i].file[j].type == IN)
			close(data->inputs[i].file[j].fd);
		//if (data->inputs[i].file[j].type == OUT)
		//	close(data->inputs[i].file[j].fd);
		j++;
	}
}

void	ft_free_sec(t_data *data, int i)
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

int	ft_is_new_local_var(t_data *data, int i)
{
	char	*str;
	int		j;

	str = data->inputs[i].cmds[0];
	j = 0;
	while (str[j])
	{
		j++;
	}
	return (0);
}

void	ft_add_new_local_var(t_data *data, int i)
{
	(void)data;
	(void)i;
}
