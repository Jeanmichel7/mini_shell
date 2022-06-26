/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:22:40 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/26 22:00:53 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_fill_heredoc(char *pattern)
{
	char	*ptr;
	char	*temp;
	char	*str;
	int		fd;
	int		pattern_found;

	fd = open("herdoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	str = NULL;
	ptr = NULL;
	temp = NULL;
	pattern_found = 0;
	while (pattern_found == 0)
		pattern_found = ft_extract_line(ptr, &str, temp, pattern);
	write(fd, str, ft_strlen(str));
	free(str);
	return (fd);
}
