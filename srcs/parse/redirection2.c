/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:22:40 by ydumaine          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/28 16:00:23 by ydumaine         ###   ########.fr       */
=======
/*   Updated: 2022/06/26 22:00:53 by jrasser          ###   ########.fr       */
>>>>>>> d1f830b3592ea67b794abcc56c39d0f519fcb277
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_fill_heredoc(char *pattern, t_data *data)
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
	if (pattern_found == 2)
	{
		free(str);
		str = NULL;
	}
	if (ft_check_and_replace_var(&str, data->env) == 1)
		return (0);
	write(fd, str, ft_strlen(str));
	free(str);
	return (fd);
}
