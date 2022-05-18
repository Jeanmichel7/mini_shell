/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:05 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/17 23:24:47 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_var	*ft_init_var(char **argv, char **env)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	var->cmd1_args = ft_split(argv[2], ' ');
	var->cmd1_fct = ft_checkacces(env, var->cmd1_args[0]);
	var->cmd2_args = ft_split(argv[3], ' ');
	var->cmd2_fct = ft_checkacces(env, var->cmd2_args[0]);
	var->fd1 = open(argv[1], O_RDONLY);
	var->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	return (var);
}

void	ft_exec_cmd1(t_var *var, char **env)
{
	dup2(var->tube[1], STDOUT_FILENO);
	close(var->tube[0]);
	dup2(var->fd1, STDIN_FILENO);
	if (var->fd1 != -1)
	{
		if (execve(var->cmd1_fct, var->cmd1_args, env) == -1)
		{
			if (var->cmd1_fct != NULL)
				ft_errputstr(strerror(errno), 0, 0, var);
			exit (1);
		}
		close(var->fd1);
	}
}

void	ft_one_pipe(t_data *data)
{
	t_var	*var;

	ft_check_fds(var->fd1, var->fd2, argv[1]);
	ft_check_cmds(var->cmd1_fct, var->cmd1_args[0], \
	var->cmd2_fct, var->cmd2_args[0]);
	pipe(var->tube);
	var->child = fork();
	if (var->child == -1)
		perror("Error");
	if (var->child == 0)
		ft_exec_cmd1(var, env);
	else
	{
		waitpid(var->child, NULL, WNOHANG);
		dup2(var->tube[0], STDIN_FILENO);
		close(var->tube[1]);
		dup2(var->fd2, STDOUT_FILENO);
		if (execve(var->cmd2_fct, var->cmd2_args, env) == -1)
			ft_errputstr(strerror(errno), 1, 1, var);
		close(var->fd2);
	}
	ft_free(var);
	return (0);
}