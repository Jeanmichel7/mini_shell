/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determining_type_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:34:04 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/26 21:18:25 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_redirection_in2(char *str)
{
	if (*(str + 2) == '>')
	{
		if (*(str + 3) == '>')
			return (-3);
		return (-2);
	}
	else if (*(str + 2) == '<')
	{
		if (*(str + 3) == '>')
			return (-1);
		if (*(str + 3) == '<')
			return (-1);
		return (-4);
	}
	else
		return (3);
}

int	ft_check_redirection_in(char *str)
{
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (ft_check_redirection_in2(str));
		else if (*(str + 1) == '<')
		{
			if (*(str + 2) == '<')
				return (-4);
			return (-1);
		}
		else
			return (2);
	}
	return (0);
}

int	ft_check_redirection_out(char *str)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			if (*(str + 2) == '>')
			{	
				if (*(str + 3) == '>')
					return (-3);
				return (-2);
			}
			else if (*(str + 2) == '<' && *(str + 3) != '<')
				return (-1);
			else if (*(str + 2) == '<' && *(str + 3) == '<')
				return (-4);
			return (4);
		}
		else if (*(str + 1) == '>')
			return (-2);
		return (1);
	}
	return (0);
}

int	ft_type_redirection_part2(char **str, int error, int rd)
{
	error = ft_check_redirection_in(str[2]);
	if (error == 0)
		error = ft_check_redirection_out(str[2]);
	if (error != 0)
	{
		if (error > 0 && str[3] == NULL)
			error = -error;
		if (error < 0)
			return (error);
	}
	return (rd);
}

int	ft_type_redirection(char **str)
{
	int	rd;
	int	error;

	error = 0;
	rd = ft_check_redirection_in(str[0]);
	if (rd == 0)
		rd = ft_check_redirection_out(str[0]);
	if (rd < 0)
		return (rd);
	if (str[1] == NULL)
		return (-5);
	error = ft_check_redirection_in(str[1]);
	if (error == 0)
		error = ft_check_redirection_out(str[1]);
	if (error != 0)
	{
		if (error > 0)
			error = -error;
		return (error);
	}
	if (str[2] == NULL)
		return (rd);
	return (ft_type_redirection_part2(str, error, rd));
}
