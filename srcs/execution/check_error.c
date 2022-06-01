/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:01:24 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/29 22:02:32 by jrasser          ###   ########.fr       */
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
