/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:01:57 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/27 21:05:35 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_check_access_bad_exec(t_data *data, int i)
{
	if ((access(data->inputs[i].cmds[0], F_OK | X_OK) == 0
			&& (data->inputs[i].cmds[0][0] == '/'
			|| data->inputs[i].cmds[0][0] == '.'))
		|| ft_is_builtin(data, i))
		return (1);
	return (0);
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
	if (ft_check_access_bad_exec(data, i))
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
