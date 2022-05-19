/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:05 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/19 05:01:36 by jrasser          ###   ########.fr       */
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

void	ft_exec_cmd1(t_data *data, int i, char **env)
{
	dup2(data->inputs.input[i].tube[1], STDOUT_FILENO);
	close(data->inputs.input[i].tube[0]);
	//dup2(data->inputs.input[i].fd, STDIN_FILENO);
	//if (data->inputs.input[i].fd != -1)
	//{
		if (execve(data->inputs.input[i].cmd_fct, \
		data->inputs.input[i].cmds, env) == -1)
		{
			if (data->inputs.input[i].cmd_fct != NULL)
				ft_errputstr(strerror(errno), 0, 0, data);
			exit (1);
		}
		//close(data->inputs.input[i].fd);
	//}
}


void	ft_pipe(t_data *data, char **env)
{
	char	*cmd1_fct;
	char	**cmd1_args;
	char	*cmd2_fct;
	char	**cmd2_args;
	int		i;

	i = 0;
	while (i < data->inputs.nb_pipe)
	{
		cmd1_args = data->inputs.input[i].cmds;
		cmd2_args = data->inputs.input[i + 1].cmds;
		cmd1_fct = ft_check_access(env, data->inputs.input[i].cmd_fct);
		cmd2_fct = ft_check_access(env, data->inputs.input[i + 1].cmd_fct);
		ft_check_cmds(cmd1_fct, cmd1_args[0]);
		//var->fd1 = open(argv[1], O_RDONLY);
		//var->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

		pipe(data->inputs.input[i].tube);
		data->inputs.input[i].child = fork();
		if (data->inputs.input[i].child == -1)
			perror("Error");
		if (data->inputs.input[i].child == 0)
		{
			printf("2\n");
			ft_exec_cmd1(data, i, env);
		}
		
		dup2(data->inputs.input[i].tube[0], STDIN_FILENO);
		close(data->inputs.input[i].tube[1]);
		wait(NULL);
		//dup2(data->inputs.input[i].fd, STDOUT_FILENO);

		data->inputs.input[i].child = fork();
		if (data->inputs.input[i].child == -1)
			perror("Error");
		if (data->inputs.input[i].child == 0)
		{
			printf("1\n");
			if (execve(cmd2_fct, cmd2_args, env) == -1)
				ft_errputstr(strerror(errno), 1, 1, data);
		}
		else
		{
			//waitpid(data->inputs.input[i].child2, NULL, WNOHANG);
			//dup2(data->inputs.input[i].tube[1], STDOUT_FILENO);
			printf("tout a la fin\n");
			close(data->inputs.input[i].tube[0]);
			//waitpid(data->inputs.input[i + 1].child, NULL, WCONTINUED);
		}
		//close(data->inputs.input[1].fd);
		
		
		//ft_free(var);
		i++;
	}
}


/*
void	ft_pipe(t_data *data, char **env)
{
	char	*cmd1_fct;
	char	**cmd1_args;
	char	*cmd2_fct;
	char	**cmd2_args;
	int		i;

	i = 0;
	while (i < data->inputs.nb_pipe)
	{
		cmd1_args = data->inputs.input[i].cmds;
		cmd2_args = data->inputs.input[i + 1].cmds;
		cmd1_fct = ft_check_access(env, data->inputs.input[i].cmd_fct);
		cmd2_fct = ft_check_access(env, data->inputs.input[i + 1].cmd_fct);
		ft_check_cmds(cmd1_fct, cmd1_args[0]);
		//var->fd1 = open(argv[1], O_RDONLY);
		//var->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

		pipe(data->inputs.input[i].tube);
		data->inputs.input[i].child = fork();
		if (data->inputs.input[i].child == -1)
			perror("Error");
		if (data->inputs.input[i].child == 0)
			ft_exec_cmd1(data, i, env);
		else
		{
			wait(NULL);
			//waitpid(data->inputs.input[i].child, NULL, WNOHANG);
			dup2(data->inputs.input[i].tube[0], STDIN_FILENO);
			close(data->inputs.input[i].tube[1]);
			//dup2(data->inputs.input[0].fd, STDOUT_FILENO);

			if (execve(cmd2_fct, cmd2_args, env) == -1)
			{
				ft_errputstr(strerror(errno), 1, 1, data);
			}
			
			//close(data->inputs.input[1].fd);
			close(data->inputs.input[i].tube[0]);
		}
		//ft_free(var);
		i++;
	}
}
*/
