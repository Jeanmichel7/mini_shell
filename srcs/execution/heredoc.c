/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:30:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/26 22:51:30 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_dup_heredoc(t_data *data, int i, int j, int fd_heredoc)
{
	char	*str;

	str = get_next_line(fd_heredoc);
	while (str)
	{
		write(data->inputs[i].file[j].fd, str, ft_strlen(str));
		write(data->inputs[i].file[j].fd, "\n", 1);
		free(str);
		str = get_next_line(fd_heredoc);
	}
}

int	ft_heredoc(t_data *data, int i, int j, int *type)
{
	close(data->inputs[i].file[j].fd);
	data->inputs[i].file[j].fd = open(data->inputs[i].file[j].name, \
	O_RDONLY);
	*type = IN;
	return (data->inputs[i].file[j].fd);
}
