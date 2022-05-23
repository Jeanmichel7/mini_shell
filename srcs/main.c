/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:38:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/19 16:56:37 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->inputs.nb_pipe + 1)
	{
		i++;
	}
	free(data->inputs.input);
	//rl_clear_history();	leaks de readline
}

int main(int argc, char **argv, char **env)
{
	t_data			data;

	(void)argc;
	(void)argv;
	data.temp = NULL;
	data.prompt = "readline$ ";
	data.done = 0;
	data.env = env; 
	while (!data.done)
	{
		data.temp = readline(data.prompt);
		if (!data.temp)
			exit(1);
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
