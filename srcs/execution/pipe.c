/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:05 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/18 03:37:03 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	ft_free(t_var *var)
{
	if (var != NULL)
	{
		if (var->fd1 != -1)
			free(var->cmd1_fct);
		free(var->cmd1_args);
		free(var->cmd2_fct);
		free(var->cmd2_args);
	}
}
*/

void	ft_errputstr(char *str, int stop, int code, t_data *data)
{
	(void)data;
	if (str)
	{
		write(2, str, ft_strlen(str));
		if (stop)
		{
			//ft_free(var);
			exit(code);
		}
	}
}

void	ft_exec_cmd1(t_data *data, char **env)
{
	dup2(data->inputs.input[0].tube[1], STDOUT_FILENO);
	close(data->inputs.input[0].tube[0]);
	//dup2(data->inputs.input[0].fd, STDIN_FILENO);
	//if (data->inputs.input[0].fd != -1)
	//{
		if (execve(data->inputs.input[0].cmd_fct, \
		data->inputs.input[0].cmds, env) == -1)
		{

			if (data->inputs.input[0].cmd_fct != NULL)
				ft_errputstr(strerror(errno), 0, 0, data);
			printf("test\n\n");

			exit (1);
		}
		printf("test\n\n");
		//close(data->inputs.input[0].fd);
	//}
}

void	ft_pipe(t_data *data, char **env)
{
	char	*cmd1_fct;
	char	**cmd1_args;
	char	*cmd2_fct;
	char	**cmd2_args;

	cmd1_args = data->inputs.input[0].cmds;
	cmd2_args = data->inputs.input[1].cmds;
	cmd1_fct = ft_check_access(env, data->inputs.input[0].cmd_fct);
	cmd2_fct = ft_check_access(env, data->inputs.input[1].cmd_fct);
	ft_check_cmds(cmd1_fct, cmd1_args[0], cmd2_fct, cmd2_args[0]);
	//var->fd1 = open(argv[1], O_RDONLY);
	//var->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

	pipe(data->inputs.input->tube);
	data->inputs.input[0].child = fork();
	if (data->inputs.input[0].child == -1)
		perror("Error");
	if (data->inputs.input[0].child == 0)
		ft_exec_cmd1(data, env);
	else
	{
		wait(NULL);
		dup2(data->inputs.input[0].tube[0], STDIN_FILENO);
		close(data->inputs.input[0].tube[1]);
		//dup2(data->inputs.input[0].fd, STDOUT_FILENO);
		if (execve(data->inputs.input[1].cmd_fct, \
		data->inputs.input[1].cmds, env) == -1)
			ft_errputstr(strerror(errno), 1, 1, data);


		//close(data->inputs.input[1].fd);
	}
	//ft_free(var);
}
