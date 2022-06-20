/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:05 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/20 03:31:52 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void printWaitStatus(int status)
{
	if (WIFEXITED(status))
	{
		fprintf(stderr, "child exited, status=%d\n", WEXITSTATUS(status));
		error_code = WIFEXITED(status);
	}
	else if (WIFSIGNALED(status))
	{
		fprintf(stderr, "child killed by signal %d (%s)",
			WTERMSIG(status), strsignal(WTERMSIG(status)));
#ifdef WCOREDUMP
		if (WCOREDUMP(status))
			fprintf(stderr, " (core dumped)");
#endif
		fprintf(stderr, "\n");
		error_code = WTERMSIG(status);
	}
	else if (WIFSTOPPED(status))
	{
		fprintf(stderr, "child stopped by signal %d (%s)\n",
			   WSTOPSIG(status), strsignal(WSTOPSIG(status)));
		error_code = WSTOPSIG(status);
#ifdef WIFCONTINUED
	}
	else if (WIFCONTINUED(status))
	{
		fprintf(stderr, "child continued\n");
		//error_code = status;
#endif
	}
	else
	{
		fprintf(stderr, "status=%d, errno : %d\n", (unsigned int) status, errno);
		//error_code = 0;
	}
}
*/

void	ft_dup2(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].file[j].type != 0)
	{
		if (data->inputs[i].file[j].type == HEREDOC && data->inputs[i].file[j].fd != -1)
		{
			//fprintf(stderr, "dans heredoc fd : %d\nname : %s\n", data->inputs[i].file[j].fd
			//, data->inputs[i].file[j].name);
			data->inputs[i].file[j].fd = open(data->inputs[i].file[j].name, \
			O_RDONLY);
			data->inputs[i].file[j].type = IN;
		}
		if (data->inputs[i].file[j].type == IN && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDIN_FILENO);
		if (data->inputs[i].file[j].type == OUT && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		if (data->inputs[i].file[j].type == APPEND && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		j++;
	}
}

void ft_exec_cmd(t_data *data, int i)
{

	//fprintf(stderr, "enfant : %d\n", getpid());
	if (i != data->nb_pipe)
	{
		dup2(data->inputs[i].tube[1], STDOUT_FILENO);
		close(data->inputs[i].tube[0]);
	}
	ft_dup2(data, i);
	if (ft_is_builtin(data, i))
	{
		if (ft_exec_builtin(data, i))
			kill(0, SIGKILL);
		if (!ft_no_need_child(data, i))
			exit(error_code);
	}
	else
	{
		if (execve(data->inputs[i].cmd_fct, data->inputs[i].cmds, data->env) == -1)
		{
			if (data->inputs[i].cmd_fct != NULL)
			{
				ft_errputstr(strerror(errno), 0, 0, NULL);
				error_code = errno;
			}
		}
	}
}

void	ft_fork(t_data *data, int i)
{
	int wstatus;
	int	ret;
	int j;

	data->inputs[i].child = fork();
	if (data->inputs[i].child == -1)
		perror("Error");
	if (data->inputs[i].child == 0)
		ft_exec_cmd(data, i);
	else
	{
		j = 0;
		while (j < 10000000)
			j++;
		//printWaitStatus(wstatus);
		ret = waitpid(data->inputs[i].child, &wstatus, WNOHANG);
		if (WIFEXITED(wstatus))
			error_code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			error_code = WTERMSIG(wstatus);
		else
			error_code = 0;
		while (ret < 0)
			ret = waitpid(data->inputs[i].child, &wstatus, WNOHANG);
		//fprintf(stderr, "retour waitpid : %d\n", ret);
		//fprintf(stderr, "errno: %d\n", errno);
	}
}

void	ft_close_and_free(t_data *data, int *i)
{
	dup2(data->inputs[*i].tube[0], STDIN_FILENO);
	close(data->inputs[*i].tube[1]);
	close(data->inputs[*i].tube[0]);
	ft_close_redir(data, *i);
	ft_free_section(data, *i);
	*i += 1;
}

void	ft_exec_parse(t_data *data)
{
	int i;

	i = 0;
	while (i <= data->nb_pipe)
	{
		//fprintf(stderr, "boucle %d\n", i);
		data->inputs[i].cmd_fct = ft_check_access(data, i);
		ft_check_redir(data, i);
		if (ft_check_fds(data, i)
			|| ft_check_cmds(data, i))
		{
			if (data->inputs[i].cmds)
				ft_free_section(data, i);
			else
				free(data->inputs[i].file);
			i++;
			break;
		}
		pipe(data->inputs[i].tube);
		if (ft_no_need_child(data, i))
			ft_exec_cmd(data, i);
		else
			ft_fork(data, i);
		ft_close_and_free(data, &i);
	}
	if (data->done == 0)
		free(data->inputs);
}
