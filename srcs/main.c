/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:38:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/18 02:35:30 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fake_init(t_data *data, char **env)
{
	data->inputs.nb_pipe = 0;
	data->inputs.input = malloc(sizeof(t_input) * (data->inputs.nb_pipe + 1));
	data->inputs.input[0].redir_input = 0;
	data->inputs.input[0].redir_output = 0;
	data->inputs.input[0].redir_double_input = 0;
	data->inputs.input[0].redir_double_output = 0;
	data->inputs.input[0].cmds = malloc(sizeof(char **) * 10);
	data->inputs.input[0].cmd_fct = "/bin/ls";
	data->inputs.input[0].cmds[0] = "ls";
	data->inputs.input[0].cmds[1] = "-al";
	data->inputs.input[0].cmds[2] = NULL;
	data->inputs.input[0].env = env;
}






void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->inputs.nb_pipe + 1)
	{
		free(data->inputs.input[i].cmds);
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
	while (!data.done)
	{
		data.temp = readline(data.prompt);
		if (!data.temp)
			exit(1);
		if (*data.temp)
		{
			printf("input : %s\n", data.temp);
			add_history(data.temp);
		}
		fake_init(&data, env); /* remplissage des valeurs data.inputs (en gros c'est ta parti si c'était pas clair x))*/
		ft_jm_part(&data, env);
		free(data.temp);
	}
	ft_free(&data);
	return (0);
}
