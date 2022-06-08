/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:50:06 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/08 14:12:03 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_extract_line(char *ptr, char **str, char *temp, char *pattern)
{
	int	pattern_found;

	pattern_found = 0;
	ptr = readline(">");
	pattern_found = ft_search_pattern(ptr, pattern);
	if (pattern_found != 0)
	{
		free (ptr);
		return (pattern_found);
	}
	temp = *str;
	if (pattern_found == 0)
		*str = ft_strjoin_andadd_rt(*str, ptr);
	else
		*str = ft_strjoin(*str, ptr);
	if (temp != 0)
		free(temp);
	free(ptr);
	if (*str == 0)
		return (0);
	return (pattern_found);
}

int	ft_update_file(char *str, t_file **files, int total, int rd)
{
	int		i;
	t_file	*new_file;

	i = 0;
	new_file = ft_calloc(total + 1, sizeof(t_file));
	if (new_file == NULL)
		return (ERROR_MEMORY);
	if (*files != NULL)
		ft_memcpy(new_file, *files, (sizeof(t_file) * (total)));
	if (total != 0)
	{
		new_file[total - 1].fd = -1;
		new_file[total - 1].type = rd;
		new_file[total - 1].name = str;
	}
	new_file[total].fd = -1;
	*files = new_file;
	return (0);
}

int	ft_search_pattern(char *str, char *pattern)
{
	int	i;

	i = 0;
	if (str[i] == pattern[i])
	{
		while (str[i] == pattern[i])
		{
			if (pattern[i] == '\0')
				return (1);
			i++;
		}
	}
	return (0);
}

int	print_and_rv(char *str)
{
	fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", str);
	return (258);
}

int	ft_print_error(int rd)
{
	if (rd == -2)
		return (print_and_rv(">"));
	if (rd == -1)
		return (print_and_rv("<"));
	if (rd == -3)
		return (print_and_rv(">>"));
	if (rd == -4)
		return (print_and_rv("<<"));
	if (rd == -5)
		return (print_and_rv("new_line"));
	return (1);
}
