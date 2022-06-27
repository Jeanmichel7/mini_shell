/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:05 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/27 22:10:07 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ZSH version
void	ft_dup2(t_data *data, int i)
{
	int	j;
	int	type;
	int	fd_heredoc;

	j = 0;
	fd_heredoc = -1;
	while (data->inputs[i].file[j].type != 0)
	{
		type = data->inputs[i].file[j].type;
		if (type == HEREDOC && data->inputs[i].file[j].fd != -1)
			fd_heredoc = ft_heredoc(data, i, j, &type);
		if (type == IN && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDIN_FILENO);
		if (type == OUT && data->inputs[i].file[j].fd != -1)
		{
			if (fd_heredoc != -1)
				ft_dup_heredoc(data, i, j, fd_heredoc);
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		}
		if (type == APPEND && data->inputs[i].file[j].fd != -1)
		{
			if (fd_heredoc != -1)
				ft_dup_heredoc(data, i, j, fd_heredoc);
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		}
		j++;
	}
}
*/

void	ft_dup2(t_data *data, int i)
{
	int	j;
	int	type;

	j = 0;
	while (data->inputs[i].file[j].type != 0)
	{
		type = data->inputs[i].file[j].type;
		if (type == HEREDOC && data->inputs[i].file[j].fd != -1)
			ft_heredoc(data, i, j, &type);
		if (type == IN && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDIN_FILENO);
		if (type == OUT && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		if (type == APPEND && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		j++;
	}
}

void	ft_exec_cmd(t_data *data, int i)
{
	if (i != data->nb_pipe && !ft_no_need_child(data, i))
	{
		dup2(data->inputs[i].tube[1], STDOUT_FILENO);
		close(data->inputs[i].tube[0]);
	}
	ft_dup2(data, i);
	if (ft_is_builtin(data, i))
	{
		ft_exec_builtin(data, i);
		if (!ft_no_need_child(data, i))
			exit(0);
	}
	else if (data->inputs[0].cmds[0])
	{
		if (execve(data->inputs[i].cmd_fct, data->inputs[i].cmds, data->env)
			== -1)
		{
			if (data->inputs[i].cmd_fct != NULL)
			{
				g_error_code = errno;
				ft_errputstr(strerror(errno), 1, g_error_code, NULL);
			}
		}
	}
}

void	ft_fork(t_data *data, int i)
{
	int	wstatus;
	int	j;

	data->inputs[i].child = fork();
	if (data->inputs[i].child == -1)
		perror("Error Creat Child");
	if (data->inputs[i].child == 0)
		ft_exec_cmd(data, i);
	else
	{
		j = 0;
		while (j < 20000000)
			j++;
		if (ft_check_cmd_waiting(data, i))
			waitpid(data->inputs[i].child, &wstatus, 0);
		else
		{
			waitpid(data->inputs[i].child, &wstatus, WNOHANG);
			if (WIFEXITED(wstatus))
				g_error_code = WEXITSTATUS(wstatus);
			else
				g_error_code = 0;
		}
	}
}

void	ft_close_and_free(t_data *data, int i)
{
	dup2(data->inputs[i].tube[0], STDIN_FILENO);
	close(data->inputs[i].tube[1]);
	close(data->inputs[i].tube[0]);
	ft_close_redir(data, i);
	ft_free_section(data, i);
}

void	ft_exec_parse(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->nb_pipe)
	{
		data->inputs[i].cmd_fct = ft_check_access(data, i);
		ft_check_redir(data, i);
		if (ft_check_fds(data, i) || ft_check_cmds(data, i))
			ft_free_error(data, i);
		else
		{
			pipe(data->inputs[i].tube);
			if (ft_no_need_child(data, i))
				ft_exec_cmd(data, i);
			else
				ft_fork(data, i);
			ft_close_and_free(data, i);
		}
		i++;
	}
	if (data->done == 0)
		free(data->inputs);
}
