/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:56:23 by jeulliot          #+#    #+#             */
/*   Updated: 2022/06/27 21:50:38 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(t_data *data, int i)
{
	if ((ft_strlen(data->inputs[i].cmds[0]) == 4
			&& strncmp(data->inputs[i].cmds[0], "echo", 4) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 2
			&& strncmp(data->inputs[i].cmds[0], "cd", 2) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 3
			&& strncmp(data->inputs[i].cmds[0], "pwd", 3) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 6
			&& strncmp(data->inputs[i].cmds[0], "export", 6) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 5
			&& strncmp(data->inputs[i].cmds[0], "unset", 5) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 3
			&& strncmp(data->inputs[i].cmds[0], "env", 3) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 4
			&& strncmp(data->inputs[i].cmds[0], "exit", 4) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 11
			&& strncmp(data->inputs[i].cmds[0], "whiteprompt", 11) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 11
			&& strncmp(data->inputs[i].cmds[0], "colorprompt", 11) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 11
			&& strncmp(data->inputs[i].cmds[0], "./minishell", 11) == 0))
		return (1);
	return (0);
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
				&& data->inputs[i].cmds[1] == NULL) || \
				((ft_strncmp(data->inputs[i].cmds[0], "grep", 4) == 0 \
				|| ft_strncmp(data->inputs[i].cmds[0], "/bin/grep", 9) == 0) \
				&& data->inputs[i].cmds[2] == NULL) || \
				((ft_strncmp(data->inputs[i].cmds[0], "as", 2) == 0 \
				|| ft_strncmp(data->inputs[i].cmds[0], "/usr/bin/as", 11) == 0) \
				&& data->inputs[i].cmds[1] == NULL))
			{
				g_error_code = -1;
				return (1);
			}
		}
	}
	return (0);
}

int	ft_check_minishell(t_data *data, int i)
{
	if (ft_strlen(data->inputs[i].cmds[0]) == 11
		&& ft_strncmp(data->inputs[i].cmds[0], "./minishell", 11) == 0)
		return (1);
	return (0);
}

int	ft_no_need_child(t_data *data, int i)
{
	ft_check_cmd_waiting(data, i);
	if (ft_check_minishell(data, i) || (ft_strlen(data->inputs[i].cmds[0]) == 2
			&& ft_strncmp(data->inputs[i].cmds[0], "cd", 2) == 0))
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 6
		&& ft_strncmp(data->inputs[i].cmds[0], "export", 6) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& ft_strncmp(data->inputs[i].cmds[0], "env", 3) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 5
		&& ft_strncmp(data->inputs[i].cmds[0], "unset", 5) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 4
		&& ft_strncmp(data->inputs[i].cmds[0], "exit", 4) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 11
		&& strncmp(data->inputs[i].cmds[0], "whiteprompt", 11) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 11
		&& strncmp(data->inputs[i].cmds[0], "colorprompt", 11) == 0)
		return (1);
	else if (data->inputs[i].cmds[0] == NULL)
		return (1);
	return (0);
}
