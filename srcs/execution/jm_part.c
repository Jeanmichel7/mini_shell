/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jm_part.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:37:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/18 03:26:30 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_cmd(t_data *data)
{
	data->inputs.input[0].child = fork();
	if (data->inputs.input[0].child == -1)
		perror("Error");
	if (data->inputs.input[0].child == 0)
	{
		if (execve(data->inputs.input[0].cmd_fct, data->inputs.input[0].cmds, data->inputs.input[0].env) == -1)
		{
			if (data->inputs.input[0].cmds[0] != NULL)
				printf("error : %s\n", strerror(errno));
			exit (1);
		}
	}
	wait(NULL);
}

void	ft_display_list(t_data *data)
{
	register int	i;

	data->list = history_list();
	if (data->list)
	{
		i = 0;
		while (data->list[i])
		{
			printf("%d: %s\r\n", i, data->list[i]->line);
			i++;
		}
	}
}
void	ft_jm_part(t_data *data, char **env)
{
	(void)env;
	if (ft_strlen(data->temp) == 4 && strncmp(data->temp, "quit", 4) == 0)
		data->done = 1;
	else if (ft_strlen(data->temp) == 4 && strncmp(data->temp, "list", 4) == 0)
		ft_display_list(data);
	else if (data->inputs.nb_pipe == 0)
		ft_exec_cmd(data);
	else if (data->inputs.nb_pipe > 0)
		ft_pipe(data, env);
}
