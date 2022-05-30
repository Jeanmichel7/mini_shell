/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:12:09 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/30 19:03:05 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_redirection_in(char *str)
{
	if (*str == '>')
	{
		if (*(str + 1) == '>')
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
	if (*str  == '<')
	{
		if (*(str + 1) == '<')
		{
			if (*(str + 2) == '>')
			{	
				if (*(str + 3) == '>')
					return (-3);
				return (-2);
			}
			else if (*(str + 2) == '<')
				return (-1);
			return (4);
		}
		else if (*(str + 1) == '>')
				return (-2);
			return (1);
	}
	return (0);
}


int ft_type_redirection(char **str)
{
	int rd; 
	int error;
	int i; 

	i = 0;
	error = 0;
	rd = ft_check_redirection_in(str[0]);
	if (rd == 0) 
		rd = ft_check_redirection_out(str[0]);
	if (str[1] == NULL)
		return (-5);
	error = ft_check_redirection_in(str[1]);
	if (error == 0) 
		error = ft_check_redirection_out(str[1]);
	if (str[2] == NULL || error != 0)
	{
		if (error > 0)
			error = -error;
		return (error);
	}
	error = ft_check_redirection_in(str[2]);
	if (error == 0)
		error = ft_check_redirection_out(str[2]);
	if (error != 0)
	{
		if (error > 0)
			error = -error;
		return (error);
	}
	return (rd);
}

int	print_and_rv(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
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

int	ft_update_file(char *str, t_file *files, int total, int rd)
{
	int i; 
	t_file *new_file; 

	i = 0;
	new_file = ft_calloc(total + 1, sizeof(t_file));
	if (new_file == NULL)
		return (ERROR_MEMORY);
	if (files != NULL)
		ft_memcpy(new_file, files, (sizeof(t_file) * (total + 1)));
	new_file[total].fd = 0;
	new_file[total].type = rd; 
	new_file[total].name = str; 
	return (0);
}

int	ft_fulling_redir_para(int rd, t_input *input, char *file)
{
	int	 total; 

	total = input->redir_double_output + input->redir_output + input->redir_input 
		+ input->redir_double_input ;
	if (rd == 3)
		input->redir_double_output++;
	if (rd == 2)
		input->redir_output++;
	if (rd == 1)
		input->redir_input++;
	if (rd == 4)
		input->redir_double_input++;
	if (ft_update_file(file, input->files, total, rd) != 0)
		return (ERROR_MEMORY);
	return (0);
}

int	ft_parse_input_redirection(t_input *input)
{
	int		i; 
	char	**new_cmd;
	int		rd;
	char 	*file; 

	i = 0; 
	file = NULL; 
	while (input->cmds[i])
	{
		new_cmd = ft_split_redirection(input->cmds[i]);
		if (new_cmd == NULL)
			return (ERROR_MEMORY);
		input->cmds = ft_replace_elements(input->cmds, new_cmd, &i);
	}
	i = 0; 
	while (input->cmds[i])
	{
		if (input->cmds[i][0] == '<' || input->cmds[i][0] == '>')
		{
			rd = ft_type_redirection(&input->cmds[i]);
			if (rd < 0)
				return (ft_print_error(rd));
			else if (ft_fulling_redir_para(rd, input, input->cmds[i + 1]) == 2)
				return (ERROR_MEMORY);
		}
		i++;
	}
	return (0);
}

int	ft_parse_redirection(t_data *data)
{
	int error;
	int	i;
	
	i = 0;
	error = 0;
	while (i <= data->nb_pipe)
	{
		error =	ft_parse_input_redirection(&data->inputs[i]);
		if (error != 0)
			return(ft_yerror(error));
		i++;
	}
	return (0);
}

