/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:38:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/23 15:45:22 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipe + 1)
	{
		free(data->inputs[i].cmds);
		i++;
	}
	free(data->inputs);
	//rl_clear_history();	leaks de readline
}

int main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.temp = NULL;
	data.prompt = "minishell$ ";
	data.done = 0;
	data.env = env; 
	int fd_in_saved = dup (0);
	int fd_out_saved = dup (1);
	while (!data.done)
	{
		dup2(fd_in_saved, STDIN_FILENO);
		dup2(fd_out_saved, STDOUT_FILENO);
		data.temp = readline(data.prompt);
		if (!data.temp)
		{
			fprintf(stderr,"temp : %s\n", data.temp);
			fprintf(stderr,"lui la ????\n");
			exit(1);
		}
		if (*data.temp)
		{
			add_history(data.temp);
		}
		ft_yparsing(&data);
	//	ft_jm_part(&data, env);

		free(data.temp);
	}
	ft_free(&data);
	return (0);
}
