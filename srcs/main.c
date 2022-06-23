/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:38:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/23 11:41:16 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	fake_init_inputs(t_data *data)
{
	data->nb_pipe = 1;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;


	data->inputs[0].file = malloc(sizeof(t_file) * 3);
	data->inputs[0].file[0].name = "fichier_input.txt";
	data->inputs[0].file[0].type = IN;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].file[1].name = "fichier_output_real.txt";
	data->inputs[0].file[1].type = OUT;
	data->inputs[0].file[1].fd = -1;

	data->inputs[0].file[2].name = "fichier_output2.txt";
	data->inputs[0].file[2].type = OUT;
	data->inputs[0].file[2].fd = -1;

	data->inputs[0].file[3].type = 0;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "grep";
	data->inputs[0].cmds[1] = "a";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].file = malloc(sizeof(t_file) * 2);
	data->inputs[1].file[0].name = "autrefichier.txt";
	data->inputs[1].file[0].type = OUT;
	data->inputs[1].file[0].fd = -1;

	data->inputs[1].file[1].type = 0;

	data->inputs[1].cmds = malloc(sizeof(char **) * 3);
	data->inputs[1].cmds[0] = "cat";
	data->inputs[1].cmds[1] = "-e";
	data->inputs[1].cmds[2] = NULL;
}
*/


void	ft_init_data(t_data *data, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	error_code = 0;
	data->temp = NULL;
	data->done = 0;
	data->env = ft_envcpy(env);
	data->fd_in_saved = dup (0);
	data->fd_out_saved = dup (1);
}

void	ft_reinit_data(t_data *data)
{
	dup2(data->fd_in_saved, STDIN_FILENO);
	dup2(data->fd_out_saved, STDOUT_FILENO);
	while (wait(0) != -1);
	data->prompt = ft_color_prompt(data);
	data->temp = readline(data->prompt);
}


int main(int argc, char **argv, char **env)
{
	t_data	data;
	int new_code; 

	new_code = 0; 
	ft_init_data(&data, argc, argv, env);
	ft_init_term(&data);
	while (!data.done)
	{
		ft_reinit_data(&data);
		if (!data.temp)
		{
			ft_free_tab(data.env);
			exit(1);
		}
		if (*data.temp)
			add_history(data.temp);
		new_code = ft_yparsing(&data); 
		if (new_code == 0)
			ft_exec_parse(&data);
		else 
			error_code = new_code;
		ft_free_inputs(&data);
	}
	ft_free(&data);
	return (0);
}

//ft_yprint_input(&data);
/*
lsof -p 88103
*/
