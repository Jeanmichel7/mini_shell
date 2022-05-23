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

void	fake_init_inputs(t_data *data, char **env)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].env = env;
	data->inputs[0].redir_input = 0;
	data->inputs[0].redir_output = 0;
	data->inputs[0].redir_double_input = 0;
	data->inputs[0].redir_double_output = 0;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmd_fct = "/bin/ls";
	data->inputs[0].cmds[0] = "ls";
	data->inputs[0].cmds[1] = "-al";
	data->inputs[0].cmds[2] = NULL;
}

void	fake_init_inputs2(t_data *data, char **env)
{
	data->nb_pipe = 1;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].env = env;
	data->inputs[0].child = -1;
	data->inputs[0].redir_input = 0;
	data->inputs[0].redir_output = 0;
	data->inputs[0].redir_double_input = 0;
	data->inputs[0].redir_double_output = 0;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmd_fct = "/bin/ls";
	data->inputs[0].cmds[0] = "ls";
	data->inputs[0].cmds[1] = "-al";
	data->inputs[0].cmds[2] = NULL;

	data->inputs[1].env = env;
	data->inputs[1].child = -1;
	data->inputs[1].redir_input = 0;
	data->inputs[1].redir_output = 0;
	data->inputs[1].redir_double_input = 0;
	data->inputs[1].redir_double_output = 0;

	data->inputs[1].cmds = malloc(sizeof(char **) * 3);
	data->inputs[1].cmd_fct = "/bin/cat";
	data->inputs[1].cmds[0] = "cat";
	data->inputs[1].cmds[1] = "-e";
	data->inputs[1].cmds[2] = NULL;
}

void	fake_init_inputs3(t_data *data, char **env)
{
	data->nb_pipe = 2;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;
	data->inputs[0].env = env;
	data->inputs[0].redir_input = 0;
	data->inputs[0].redir_output = 0;
	data->inputs[0].redir_double_input = 0;
	data->inputs[0].redir_double_output = 0;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmd_fct = "/bin/ls";
	data->inputs[0].cmds[0] = "ls";
	data->inputs[0].cmds[1] = "-al";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].env = env;
	data->inputs[1].redir_input = 0;
	data->inputs[1].redir_output = 0;
	data->inputs[1].redir_double_input = 0;
	data->inputs[1].redir_double_output = 0;

	data->inputs[1].cmds = malloc(sizeof(char **) * 6);
	data->inputs[1].cmd_fct = "/usr/bin/cut";
	data->inputs[1].cmds[0] = "cut";
	data->inputs[1].cmds[1] = "-d";
	data->inputs[1].cmds[2] = "M";
	data->inputs[1].cmds[3] = "-f";
	data->inputs[1].cmds[4] = "2";
	data->inputs[1].cmds[5] = NULL;
	


	data->inputs[2].env = env;
	data->inputs[2].redir_input = 0;
	data->inputs[2].redir_output = 0;
	data->inputs[2].redir_double_input = 0;
	data->inputs[2].redir_double_output = 0;

	data->inputs[2].cmds = malloc(sizeof(char **) * 3);
	data->inputs[2].cmd_fct = "/bin/cat";
	data->inputs[2].cmds[0] = "cat";
	data->inputs[2].cmds[1] = "-e";
	data->inputs[2].cmds[2] = NULL;
}


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
			fprintf(stderr,"input : %s\n", data.temp);
			add_history(data.temp);
		}
		fake_init_inputs3(&data, env); /* remplissage des valeurs data.inputs*/
		ft_jm_part(&data, env);
		free(data.temp);
	}
	ft_free(&data);
	return (0);
}
