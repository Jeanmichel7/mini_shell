/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:01 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/13 00:55:07 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_convert_redi(t_data *data)
{
	int	i;
	int	u;
	int	j;

	i = 0;
	while (i <= data->nb_pipe)
	{
		j = 0;
		while (data->inputs[i].cmds && data->inputs[i].cmds[j])
		{
			u = 0;
			while (data->inputs[i].cmds[j][u])
			{
				if (data->inputs[i].cmds[j][u] == -1)
					data->inputs[i].cmds[j][u] = '>';
				if (data->inputs[i].cmds[j][u] == -2)
					data->inputs[i].cmds[j][u] = '<';
				u++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_fulling_inputs_cmds(t_data *data)
{
	int		i;
	char	**cmd;
	char	**ptr;
	int		error;

	error = 0;
	i = 0;
	cmd = ft_split_and_omit(data->temp, '|', 1);
	if (cmd == NULL)
		return (ERROR_MEMORY);
	i = 0;
	while (i <= data->nb_pipe)
	{
		if (cmd[i] != NULL)
			error = ft_which_redirection_take_on_board(cmd[i]);
		if (error != 0)
			return (error);
		ptr = ft_split_and_omit(cmd[i], ' ', 0);
		if (ptr == NULL)
		{
			ft_free_tab(cmd);
			return (0);
		}
		data->inputs[i].cmds = ptr;
		i++;
	}
	ft_free_tab(cmd);
	return (0);
}

int	ft_if_not_cmd_after_last_pipe(t_data *data)
{
	char	*ptr;
	char	**cmd;

	ptr = NULL;
	if (data->inputs->cmds != NULL && data->inputs[data->nb_pipe].cmds == NULL )
	{
		ptr = readline(">");
		while (*ptr == 0)
			ptr = readline(">");
		cmd = ft_split_and_omit(ptr, ' ', 0);
		free(ptr);
		if (cmd == NULL)
			return (1);
		data->inputs[data->nb_pipe].cmds = cmd;
	}
	return (0);
}

int	ft_yparsing(t_data *data)
{
	int		error;

	if (ft_pre_parsing(data) == 1) 
		return (0);
	data->nb_pipe = ft_ycheck_pipe(data->temp);
	if (data->nb_pipe == -1)
		return (ft_yerror(ERROR_PIPE, data));
	if (ft_if_quotes_not_closes(data) == NULL)
		return (ft_yerror(ERROR_MEMORY, data));
	if (ft_check_and_replace_var(&data->temp, data->env) == 1)
		return (ft_yerror(ERROR_MEMORY, data));
	ft_create_inputs(data);
	error = ft_fulling_inputs_cmds(data);
	if (error != 0)
		return (ft_yerror(error, data));
	error = ft_parse_redirection(data);
	if (error != 0)
		return (ft_yerror(error, data));
	if (ft_if_not_cmd_after_last_pipe(data) == 1)
		return (ft_yerror(ERROR_MEMORY, data));
	if (data->inputs == NULL)
		return (ft_yerror(5, data));
	ft_convert_redi(data);
	return (0);
}
