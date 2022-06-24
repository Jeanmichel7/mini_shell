/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:56:23 by jeulliot          #+#    #+#             */
/*   Updated: 2022/06/24 20:28:03 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			&& strncmp(data->inputs[i].cmds[0], "exit", 4) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 11
			&& strncmp(data->inputs[i].cmds[0], "whiteprompt", 11) == 0)
		|| (ft_strlen(data->inputs[i].cmds[0]) == 11
			&& strncmp(data->inputs[i].cmds[0], "colorprompt", 11) == 0))
		return (1);
	return (0);
}

int	ft_no_need_child(t_data *data, int i)
{
	ft_check_cmd_waiting(data, i);
	if (ft_strlen(data->inputs[i].cmds[0]) == 2
		&& ft_strncmp(data->inputs[i].cmds[0], "cd", 2) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 6
		&& ft_strncmp(data->inputs[i].cmds[0], "export", 6) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 3
		&& ft_strncmp(data->inputs[i].cmds[0], "env", 3) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 5
		&& ft_strncmp(data->inputs[i].cmds[0], "unset", 5) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 4
		&& ft_strncmp(data->inputs[i].cmds[0], "exit", 4) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 11
		&& strncmp(data->inputs[i].cmds[0], "whiteprompt", 11) == 0)
		return (1);
	else if (ft_strlen(data->inputs[i].cmds[0]) == 11
		&& strncmp(data->inputs[i].cmds[0], "colorprompt", 11) == 0)
		return (1);
	return (0);
}

char	*ft_sub_check_access(int *j, t_data *data, char **path_tab, int i)
{
	char	*path_cmd_test;
	char	*str;

	str = ft_strjoin(path_tab[*j], "/");
	path_cmd_test = ft_strjoin(str, data->inputs[i].cmds[0]);
	if (access(path_cmd_test, F_OK | X_OK) == 0)
	{
		ft_free_tab(path_tab);
		return (path_cmd_test);
	}
	free(path_cmd_test);
	*j += 1;
	return (NULL);
}

char	*ft_sub_check_access2(t_data *data)
{
	char	*paths;
	int		j;

	j = -1;
	while (data->env[++j])
	{	
		if (strncmp(data->env[j], "PATH", 4) == 0)
		{
			paths = data->env[j];
			return (paths);
		}
	}
	return (NULL);
}

char	*ft_check_access(t_data *data, int i)
{
	int		j;
	char	*paths;
	char	**path_tab;
	char	*path_cmd_test;

	paths = NULL;
	if (data->inputs[i].cmds == NULL)
		return (NULL);
	if (access(data->inputs[i].cmds[0], F_OK | X_OK) == 0
		|| ft_is_builtin(data, i))
		return (data->inputs[i].cmds[0]);
	paths = ft_sub_check_access2(data);
	if (paths == NULL)
		return (NULL);
	paths = paths + 5;
	path_tab = ft_split(paths, ':');
	j = 0;
	while (path_tab[j])
	{
		path_cmd_test = ft_sub_check_access(&j, data, path_tab, i);
		if (path_cmd_test)
			return (path_cmd_test);
	}
	ft_free_tab(path_tab);
	return (NULL);
}
