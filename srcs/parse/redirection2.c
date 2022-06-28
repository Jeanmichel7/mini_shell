/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:22:40 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/28 20:41:58 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct ptr
{
	char	*ptr;
	char	*temp;
	char	*str;
}		t_ptr;

void	ft_sub_fill_heredoc(t_ptr my_ptr)
{
	g_error_code = 1;
	free(my_ptr.str);
	my_ptr.str = NULL;
}

int	ft_fill_heredoc(char *pattern, t_data *data)
{
	t_ptr	my_ptr;
	int		fd;
	int		pattern_found;
	int		old_g_error_code;

	fd = open("herdoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	my_ptr.str = NULL;
	my_ptr.ptr = NULL;
	my_ptr.temp = NULL;
	old_g_error_code = g_error_code;
	g_error_code = -2;
	pattern_found = 0;
	while (pattern_found == 0 && g_error_code != 130)
		pattern_found = ft_extract_line(my_ptr.ptr,
				&my_ptr.str, my_ptr.temp, pattern);
	if (pattern_found == 2 && g_error_code == 130)
		ft_sub_fill_heredoc(my_ptr);
	else
		g_error_code = old_g_error_code;
	if (ft_check_and_replace_var(&my_ptr.str, data->env) == 1)
		return (0);
	write(fd, my_ptr.str, ft_strlen(my_ptr.str));
	free(my_ptr.str);
	return (fd);
}
