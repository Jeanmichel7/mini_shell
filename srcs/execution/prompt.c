/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:37:47 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/30 19:56:41 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_replace_pwd(char *pwd, char *home)
{
	char	*new_pwd;
	int		i;
	int		j;

	new_pwd = malloc(sizeof(char) * (ft_strlen(pwd) + 1 - 5));
	new_pwd[0] = '~';
	i = 1;
	j = ft_strlen(home);
	while (pwd && pwd[j])
	{
		new_pwd[i] = pwd[j];
		i++;
		j++;
	}
	new_pwd[i] = '\0';
	return (new_pwd);
}

char	*ft_home(t_data *data)
{
	int		i;
	char	**temp;
	char	*home;

	i = 0;
	while (data->env && data->env[i])
	{
		temp = ft_split(data->env[i], '=');
		if (ft_strlen(temp[0]) == 4
			&& ft_strncmp(temp[0], "HOME", 4) == 0)
		{
			home = malloc(sizeof(char) * (ft_strlen(temp[1]) + 1));
			ft_memcpy(home, temp[1], ft_strlen(temp[1]) + 1);
			ft_free_tab(temp);
			return (home);
		}
		ft_free_tab(temp);
		i++;
	}
	return (NULL);
}

char	*ft_sub_color_prompt(char *home, char *pwd)
{
	char	*pwd_home;
	char	*pwd_color;

	pwd_home = ft_replace_pwd(pwd, home);
	pwd_color = ft_strjoin("\001\e[01;34m\002", pwd_home);
	free(home);
	free(pwd_home);
	return (pwd_color);
}

char	*ft_color_prompt(t_data *data)
{
	char	pwd[500];
	char	*new_str;
	char	*pwd_color;
	char	*prompt_color;
	char	*home;

	home = ft_home(data);
	getcwd(pwd, 500);
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
		pwd_color = ft_sub_color_prompt(home, pwd);
	else
		pwd_color = ft_strjoin("\001\e[01;32m\002", pwd);
	prompt_color = ft_strjoin("\001\e[01;32m\002minishell\001\e[01;37m\002:",
			pwd_color);
	free(pwd_color);
	new_str = ft_strjoin(prompt_color, "\001\e[00;37m\002$ ");
	free(prompt_color);
	return (new_str);
}

int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
