/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:01:24 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/30 18:46:55 by jrasser          ###   ########.fr       */
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
			exit(code);
	}
}

void	ft_free_error(t_data *data, int i)
{
	if (data->inputs[i].cmds)
		ft_free_section(data, i);
	else
		free(data->inputs[i].file);
}
