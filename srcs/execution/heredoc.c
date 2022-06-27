/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:30:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/27 21:52:18 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
ZSH Version
*/

void	ft_dup_heredoc(t_data *data, int i, int j, int fd_heredoc)
{
	char	*str;
	int		ret;

	str = malloc(sizeof(char) * (BUFFER_SIZE));
	ret = read(fd_heredoc, str, BUFFER_SIZE);
	str[ret] = '\0';
	if (str[0] == '\0')
	{
		close(data->inputs[i].file[j].fd);
		open(data->inputs[i].file[j].name, \
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		write(data->inputs[i].file[j].fd, "", 1);
	}
	else
		write(data->inputs[i].file[j].fd, str, ft_strlen(str));
	free(str);
}

int	ft_heredoc(t_data *data, int i, int j, int *type)
{
	close(data->inputs[i].file[j].fd);
	data->inputs[i].file[j].fd = open(data->inputs[i].file[j].name, \
	O_RDONLY);
	*type = IN;
	return (data->inputs[i].file[j].fd);
}
