/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:56:23 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/27 22:19:58 by jrasser          ###   ########.fr       */
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

char	*sub_check_acces(char **path_tab, int i, char *cmd)
{
	char	*str;
	char	*str2;
	
	str = ft_strjoin(path_tab[i], "/");
	str2 = ft_strjoin(str, cmd);
	free(str);
	return (str2);
}

char	*ft_check_access(char **env, char *cmd)
{
	int		i;
	int		state;
	char	*path_cmd_test;
	char	*paths;
	char	**path_tab;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = -1;
	state = 1;
	while (env[++i])
		if (strncmp(env[i], "PATH", 4) == 0)
			paths = env[i];
	paths = paths + 5;
	path_tab = ft_split(paths, ':');
	i = 0;
	while (path_tab[i] && state)
	{
		path_cmd_test = sub_check_acces(path_tab, i, cmd);
		if (access(path_cmd_test, F_OK | X_OK) == 0)
		{
			ft_free_tab(path_tab);
			return (path_cmd_test);
		}
		i++;
	}
	return (NULL);
}

void	ft_check_cmds(char *fct, char *args)
{
	if (fct == NULL)
	{
		ft_errputstr("zsh: command not found: ", 0, 0, NULL);
		ft_errputstr(args, 0, 0, NULL);
		ft_errputstr("\n", 0, 0, NULL);
	}
}

void	ft_check_fds(int fd1, int fd2, char *fct)
{
	if (fd1 == -1)
	{
		ft_errputstr("zsh: ", 0, 0, NULL);
		ft_errputstr(strerror(errno), 0, 0, NULL);
		ft_errputstr(": ", 0, 0, NULL);
		ft_errputstr(fct, 0, 0, NULL);
		ft_errputstr("\n", 0, 0, NULL);
	}
	if (fd2 == -1)
		ft_errputstr(strerror(errno), 1, 1, NULL);
}
