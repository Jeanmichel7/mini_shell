/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:05 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/28 22:12:49 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ft_check_redir(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].file[j].type != 0)
	{
		if (data->inputs[i].file[j].type == IN)
			data->inputs[i].file[j].fd = open(data->inputs[i].file[j].name, \
			O_RDONLY);
		if (data->inputs[i].file[j].type == OUT)
			data->inputs[i].file[j].fd = open(data->inputs[i].file[j].name, \
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (data->inputs[i].file[j].type == APPEND)
			data->inputs[i].file[j].fd = open(data->inputs[i].file[j].name, \
			O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		j++;
	}
}

void	ft_check_builtin(t_data *data, int i)
{
	if (ft_strlen(data->inputs[i].cmds[0]) == 4
		&& strncmp(data->inputs[i].cmds[0], "echo", 4) == 0)
		ft_echo(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 2
		&& strncmp(data->inputs[i].cmds[0], "cd", 2) == 0)
		ft_cd(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& strncmp(data->inputs[i].cmds[0], "pwd", 3) == 0)
		ft_pwd(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 6
		&& strncmp(data->inputs[i].cmds[0], "export", 6) == 0)
		ft_export(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 5
		&& strncmp(data->inputs[i].cmds[0], "unset", 5) == 0)
		ft_unset(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& strncmp(data->inputs[i].cmds[0], "env", 3) == 0)
		ft_env(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 4
		&& strncmp(data->inputs[i].cmds[0], "exit", 4) == 0)
		ft_exit(data, i);
}

void ft_exec_cmd(t_data *data, int i)
{
	int	j;

	if (i != data->nb_pipe)
	{
		dup2(data->inputs[i].tube[1], STDOUT_FILENO);
		close(data->inputs[i].tube[0]);
	}
	j = 0;
	while (data->inputs[i].file[j].type != 0)
	{
		if (data->inputs[i].file[j].type == IN && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDIN_FILENO);
		if (data->inputs[i].file[j].type == OUT && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		if (data->inputs[i].file[j].type == APPEND && data->inputs[i].file[j].fd != -1)
			dup2(data->inputs[i].file[j].fd, STDOUT_FILENO);
		j++;
	}
	//if (ft_is_new_local_var(data, i))
	//	ft_add_new_local_var(data, i);
	if (ft_is_builtin(data, i))
		ft_check_builtin(data, i);
	else
		if (execve(data->inputs[i].cmd_fct, data->inputs[i].cmds, data->env) == -1)
			if (data->inputs[i].cmd_fct != NULL)
				ft_errputstr(strerror(errno), 0, 0, data);
}

void ft_pipe(t_data *data)
{
	int i;
	int wstatus;

	i = 0;
	while (i <= data->nb_pipe)
	{
		data->inputs[i].cmd_fct = ft_check_access(data, i);
		ft_check_redir(data, i);
		if (ft_check_fds(data, i) || ft_check_cmds(data->inputs[i].cmd_fct, data->inputs[i].cmds[0]))
		{
			i++;
			fprintf(stderr, "break\n");
			break;
		}
		pipe(data->inputs[i].tube);
		if (ft_is_builtin(data, i))
			ft_exec_cmd(data, i);
		else
		{
			data->inputs[i].child = fork();
			if (data->inputs[i].child == -1)
				perror("Error");
			if (data->inputs[i].child == 0)
				ft_exec_cmd(data, i);
			else
				waitpid(data->inputs[i].child, &wstatus, WNOHANG);
				//if (i != data->nb_pipe)
		}
		dup2(data->inputs[i].tube[0], STDIN_FILENO);
		close(data->inputs[i].tube[1]);
		close(data->inputs[i].tube[0]);
		ft_close_redir(data, i);
		ft_free_sec(data, i);
		i++;
	}
	free(data->inputs);
}




/*
void ft_pipe(t_data *data, char **env)
{
	char *cmd1_fct;
	char **cmd1_args;
	char *cmd2_fct;
	char **cmd2_args;
	int i;
	int wstatus;
	int wstatus2;

	i = 0;
	while (i < data->nb_pipe)
	{
		cmd1_args = data->inputs[i].cmds;
		cmd2_args = data->inputs[i + 1].cmds;
		cmd1_fct = ft_check_access(env, data->inputs[i].cmd_fct);
		cmd2_fct = ft_check_access(env, data->inputs[i + 1].cmd_fct);
		ft_check_cmds(cmd1_fct, cmd1_args[0]);
		// var->fd1 = open(argv[1], O_RDONLY);
		// var->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

		pipe(data->inputs[i].tube);
		data->inputs[i].child = fork();
		if (data->inputs[i].child == -1)
			perror("Error");
		if (data->inputs[i].child == 0)
		{
			fprintf(stderr, "2\n");
			ft_exec_cmd1(data, i, env);
		}
		else
		{
			dup2(data->inputs[i].tube[0], STDIN_FILENO);
			close(data->inputs[i].tube[1]);
			waitpid(data->inputs[i].child, &wstatus, WUNTRACED | WCONTINUED);
			// dup2(data->inputs[i].fd, STDOUT_FILENO);

			data->inputs[i].child2 = fork();
			if (data->inputs[i].child2 == -1)
				perror("Error");
			if (data->inputs[i].child2 == 0)
			{
				fprintf(stderr, "1\n");
				if (execve(cmd2_fct, cmd2_args, env) == -1)
					ft_errputstr(strerror(errno), 1, 1, data);
			}
			else
			{
				waitpid(data->inputs[i].child2, &wstatus2, WUNTRACED | WCONTINUED);
				// dup2(data->inputs[i].tube[1], STDOUT_FILENO);
				fprintf(stderr, "tout a la fin\n");
				close(data->inputs[i].tube[0]);
				//close(data->inputs[i].tube[1]);
				// waitpid(data->inputs[i + 1].child, NULL, WCONTINUED);
			}
		}
		// close(data->inputs[1].fd);
		// ft_free(var);
		i++;
	}
}
*/



/*
void ft_pipe(t_data *data, char **env)
{
	char *cmd1_fct;
	char **cmd1_args;
	char *cmd2_fct;
	char **cmd2_args;
	int i;
	int wstatus;
	int wstatus2;

	i = 0;
	while (i < data->nb_pipe)
	{
		cmd1_args = data->inputs[i].cmds;
		cmd2_args = data->inputs[i + 1].cmds;
		cmd1_fct = ft_check_access(env, data->inputs[i].cmd_fct);
		cmd2_fct = ft_check_access(env, data->inputs[i + 1].cmd_fct);
		ft_check_cmds(cmd1_fct, cmd1_args[0]);
		// var->fd1 = open(argv[1], O_RDONLY);
		// var->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

		pipe(data->inputs[i].tube);
		data->inputs[i].child = fork();
		if (data->inputs[i].child == -1)
			perror("Error");
		if (data->inputs[i].child == 0)
		{
			printf("2\n");
			ft_exec_cmd1(data, i, env);
		}
		else
		{
			dup2(data->inputs[i].tube[0], STDIN_FILENO);
			close(data->inputs[i].tube[1]);
			waitpid(data->inputs[i].child, &wstatus, WUNTRACED | WCONTINUED);
			// dup2(data->inputs[i].fd, STDOUT_FILENO);
			if (WIFEXITED(wstatus))
			{
				printf("child exited, status=%d\n", WEXITSTATUS(wstatus));
			}
			else if (WIFSIGNALED(wstatus))
			{
				printf("child killed by signal %d (%s)",
					   WTERMSIG(wstatus), strsignal(WTERMSIG(wstatus)));
#ifdef WCOREDUMP
				if (WCOREDUMP(wstatus))
					printf(" (core dumped)");
#endif
				printf("\n");
			}
			else if (WIFSTOPPED(wstatus))
			{
				printf("child stopped by signal %d (%s)\n",
					   WSTOPSIG(wstatus), strsignal(WSTOPSIG(wstatus)));
#ifdef WIFCONTINUED
			}
			else if (WIFCONTINUED(wstatus))
			{
				printf("child continued\n");
#endif
			}
			else
			{
				printf("status=%x\n",
					   (unsigned int)wstatus);
			}




			
			data->inputs[i].child2 = fork();
			if (data->inputs[i].child2 == -1)
				perror("Error");
			if (data->inputs[i].child2 == 0)
			{
				printf("1\n");
				if (execve(cmd2_fct, cmd2_args, env) == -1)
					ft_errputstr(strerror(errno), 1, 1, data);
			}
			else
			{
				waitpid(data->inputs[i].child2, &wstatus2, WUNTRACED | WCONTINUED);
				if (WIFEXITED(wstatus))
			{
				printf("child exited, status=%d\n", WEXITSTATUS(wstatus));
			}
			else if (WIFSIGNALED(wstatus))
			{
				printf("child killed by signal %d (%s)",
					   WTERMSIG(wstatus), strsignal(WTERMSIG(wstatus)));
#ifdef WCOREDUMP
				if (WCOREDUMP(wstatus))
					printf(" (core dumped)");
#endif
				printf("\n");
			}
			else if (WIFSTOPPED(wstatus))
			{
				printf("child stopped by signal %d (%s)\n",
					   WSTOPSIG(wstatus), strsignal(WSTOPSIG(wstatus)));
#ifdef WIFCONTINUED
			}
			else if (WIFCONTINUED(wstatus))
			{
				printf("child continued\n");
#endif
			}
			else
			{
				printf("status=%x\n",
					   (unsigned int)wstatus);
			}


			
				// dup2(data->inputs[i].tube[1], STDOUT_FILENO);
				printf("tout a la fin\n");
				close(data->inputs[i].tube[0]);
				// waitpid(data->inputs[i + 1].child, NULL, WCONTINUED);
			}
		}
		// close(data->inputs[1].fd);

		// ft_free(var);
		i++;
	}
}

*/

/*
void	ft_pipe(t_data *data, char **env)
{
	char	*cmd1_fct;
	char	**cmd1_args;
	char	*cmd2_fct;
	char	**cmd2_args;
	int		i;

	i = 0;
	while (i < data->nb_pipe)
	{
		cmd1_args = data->inputs[i].cmds;
		cmd2_args = data->inputs[i + 1].cmds;
		cmd1_fct = ft_check_access(env, data->inputs[i].cmd_fct);
		cmd2_fct = ft_check_access(env, data->inputs[i + 1].cmd_fct);
		ft_check_cmds(cmd1_fct, cmd1_args[0]);
		//var->fd1 = open(argv[1], O_RDONLY);
		//var->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
 
		pipe(data->inputs[i].tube);
		data->inputs[i].child = fork();
		if (data->inputs[i].child == -1)
			perror("Error");
		if (data->inputs[i].child == 0)
			ft_exec_cmd1(data, i, env);
		else
		{
			wait(NULL);
			//waitpid(data->inputs[i].child, NULL, WNOHANG);
			dup2(data->inputs[i].tube[0], STDIN_FILENO);
			close(data->inputs[i].tube[1]);
			//dup2(data->inputs[0].fd, STDOUT_FILENO);

			if (execve(cmd2_fct, cmd2_args, env) == -1)
			{
				ft_errputstr(strerror(errno), 1, 1, data);
			}

			//close(data->inputs[1].fd);
			close(data->inputs[i].tube[0]);
		}
		//ft_free(var);
		i++;
	}
}
*/
