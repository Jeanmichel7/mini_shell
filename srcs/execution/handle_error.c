/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:01:24 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/30 18:13:23 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_errputstr(char *str, int stop, int code, t_data *data)
{
	(void)data;
	if (str)
	{
		write(2, str, ft_strlen(str));
		if (stop)
			exit(code);
	}
}

int	ft_check_cmd_waiting(t_data *data, int i)
{
	int	j;

	if (i == data->nb_pipe)
	{
		j = 0;
		while (data->inputs[i].cmds && data->inputs[i].cmds[j])
			j++;
		if (j > 0)
		{
			if (((ft_strncmp(data->inputs[i].cmds[0], "cat", 3) == 0 \
				|| ft_strncmp(data->inputs[i].cmds[0], "/bin/cat", 8) == 0) \
				&& data->inputs[i].cmds[1] == NULL) \
				|| \
				((ft_strncmp(data->inputs[i].cmds[0], "grep", 4) == 0 \
				|| ft_strncmp(data->inputs[i].cmds[0], "/bin/grep", 9) == 0) \
				&& data->inputs[i].cmds[2] == NULL))
			{
				g_error_code = -1;
				return (1);
			}
		}
	}
	return (0);
}

void	ft_free_error(t_data *data, int i)
{
	if (data->inputs[i].cmds)
		ft_free_section(data, i);
	else
		free(data->inputs[i].file);
}
