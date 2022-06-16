/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:58:11 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/17 00:48:11 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_redir(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].file[j].type != 0)
	{
		//if (data->inputs[i].file[j].type == IN)
			close(data->inputs[i].file[j].fd);
		//if (data->inputs[i].file[j].type == OUT)
		//	close(data->inputs[i].file[j].fd);
		j++;
	}
}

int	ft_check_cmds(char *fct, char *fct_name)
{
	if (fct == NULL)
	{
		ft_errputstr("bash: command not found: ", 0, 0, NULL);
		ft_errputstr(fct_name, 0, 0, NULL);
		ft_errputstr("\n", 0, 0, NULL);
		error_code = 127;
		return (1);
	}
	return (0);
}

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

void	ft_display_error(void)
{
	fprintf(stderr, "%d\n", error_code);
}

void	ft_check_builtin(t_data *data, int i)
{
	if (ft_strlen(data->inputs[i].cmds[0]) == 4
		&& ft_strncmp(data->inputs[i].cmds[0], "echo", 4) == 0)
		ft_echo(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 2
		&& ft_strncmp(data->inputs[i].cmds[0], "cd", 2) == 0)
		ft_cd(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& ft_strncmp(data->inputs[i].cmds[0], "pwd", 3) == 0)
		ft_pwd(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 6
		&& ft_strncmp(data->inputs[i].cmds[0], "export", 6) == 0)
		ft_export(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 5
		&& ft_strncmp(data->inputs[i].cmds[0], "unset", 5) == 0)
		ft_unset(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& ft_strncmp(data->inputs[i].cmds[0], "env", 3) == 0)
		ft_env(data, i);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 4
		&& ft_strncmp(data->inputs[i].cmds[0], "exit", 4) == 0)
		ft_exit(data, i);
	//else if (ft_strlen(data->inputs[i].cmds[0]) == 2
	//	&& ft_strncmp(data->inputs[i].cmds[0], "$?", 2) == 0)
	//	ft_display_error();
}

int	ft_check_fds(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->inputs[i].file[j].type != 0)
	{
		if (data->inputs[i].file[j].fd == -1)
		{
			ft_errputstr("bash: ", 0, 0, NULL);
			ft_errputstr(data->inputs[i].file[j].name, 0, 0, NULL);
			ft_errputstr(": ", 0, 0, NULL);
			ft_errputstr(strerror(errno), 0, 0, NULL);
			ft_errputstr("\n", 0, 0, NULL);
			error_code = 2;
			return (1);
		}
		j++;
	}
	return (0);
}
