/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:56:23 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/28 22:27:48 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_is_builtin(t_data *data, int i)
{
	if ((ft_strlen(data->inputs[i].cmds[0]) == 4
		&& strncmp(data->inputs[i].cmds[0], "echo", 4) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 2
		&& strncmp(data->inputs[i].cmds[0], "cd", 2) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& strncmp(data->inputs[i].cmds[0], "pwd", 3) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 6
		&& strncmp(data->inputs[i].cmds[0], "export", 6) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 5
		&& strncmp(data->inputs[i].cmds[0], "unset", 5) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& strncmp(data->inputs[i].cmds[0], "env", 3) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 4
		&& strncmp(data->inputs[i].cmds[0], "exit", 4) == 0))
		return (1);
	return (0);
}

char	*sub_check_acces(char **path_tab, int i, char *cmd)
{
	char	*str;
	char	*str2;
	
	str = ft_strjoin(path_tab[i], "/");
	str2 = ft_strjoin(str, cmd);
	free(str);
	return (str2);
}

char	*ft_check_access(t_data *data, int i)
{
	int		j;
	char	*path_cmd_test;
	char	*paths;
	char	**path_tab;

	if (access(data->inputs[i].cmds[0], F_OK | X_OK) == 0
		|| ft_is_builtin(data, i))
		return (data->inputs[i].cmds[0]);
	j = -1;
	while (data->env[++j])
		if (strncmp(data->env[j], "PATH", 4) == 0)
			paths = data->env[j];
	paths = paths + 5;
	path_tab = ft_split(paths, ':');
	j = 0;
	while (path_tab[j])
	{
		path_cmd_test = sub_check_acces(path_tab, j, data->inputs[i].cmds[0]);
		if (access(path_cmd_test, F_OK | X_OK) == 0)
		{
			ft_free_tab(path_tab);
			return (path_cmd_test);
		}
		j++;
	}
	return (NULL);
}

int	ft_check_cmds(char *fct, char *fct_name)
{
	if (fct == NULL)
	{
		ft_errputstr("bash: command not found: ", 0, 0, NULL);
		ft_errputstr(fct_name, 0, 0, NULL);
		ft_errputstr("\n", 0, 0, NULL);
		return (1);
	}
	return (0);
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
			return (1);
		}
		j++;
	}
	return (0);
	//if (fd2 == -1)
	//	ft_errputstr(strerror(errno), 1, 1, NULL);
}
