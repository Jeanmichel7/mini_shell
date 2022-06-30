/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:11:49 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/30 15:28:29 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_sub_if_quotes_not_closes(int old_error, int omit)
{
	if (omit == -501)
	{
		g_error_code = old_error;
		return (258);
	}
	if (omit == -502)
	{
		g_error_code = 1;
		return (1);
	}
	g_error_code = old_error;
	return (0);
}

int	ft_sub_retrieve_string(int omit, char *ptr)
{
	if (ptr == NULL && omit == 1 && g_error_code != 130)
		write(2,
			"minishell: unexpected EOF while looking for matching `\"'\n", 58);
	if (ptr == NULL && omit == 2 && g_error_code != 130)
		write(2,
			"minishell: unexpected EOF while looking for matching `''\n", 57);
	if (ptr == NULL && g_error_code == 130)
		return (-502);
	if (ptr == NULL && g_error_code != 130)
		return (-501);
	return (0);
}

int	ft_sub_if_not_cmd_after_last_pipe(char *ptr, int old_error)
{
	if (ptr == NULL && g_error_code != 130)
	{
		g_error_code = old_error;
		write(2, "minishell: syntax error: unexpected end of file\n", 48);
		return (258);
	}
	if (ptr == NULL && g_error_code == 130)
	{
		g_error_code = 1;
		return (1);
	}
	return (0);
}
