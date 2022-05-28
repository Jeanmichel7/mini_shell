/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:12:09 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/28 14:47:15 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_redirection_in(char *str)
{
	if (*str == '>')
	{
		if (*str + 1 == '>')
		{
			if (*str + 2 == '>')
				return (-1);
			else if (*str + 2 == '<')
				return (-2);
			else 
				return (3);
		}
		else if (*str + 1 == '<')
			return (-2);
		else 
			return (2);
	}
	return (0);
}

int	ft_check_redirection_out(char *str)
{
	if (*str  == '<')
	{
		if (*str + 1 == '<')
		{
			if (*str + 2 == '>')
				return (-1);
			else if (*str + 2 == '<')
				return (-2);
			else 
				return (4);
		}
		else if (*str + 1 == '>')
				return (-2);
		else 
				return (1);
	}
	return (0);
}


int ft_type_redirection(char *str)
{
	int rd; 

	rd = ft_check_redirection_in(str);
	if (rd == 0) 
		rd = ft_check_redirection_out(str);
	return (rd);
}

int	ft_print_error(int rd)
{
	if (rd == -1)
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return (1);
	}
	if (rd == -2)
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (1);
	}	
	if (rd == 5)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
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
	ft_memcpy(new_file, files, (sizeof(t_file) * (total + 1)));
	files[total].fd = 0;
	files[total].type = rd; 
	files[total].name = str; 
	return (0);
}

int	ft_fulling_redir_para(int rd, t_input *input, char *file)
{
	int	 total; 

	total = input->redir_double_output + input->redir_output + input->redir_input 
		+ input->redir_double_input ;
	if (rd == 1)
		input->redir_double_output++;
	if (rd == 2)
		input->redir_output++;
	if (rd == 3)
		input->redir_input++;
	if (rd == 4)
	{
		input->redir_double_input++;
	}
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
		input->cmds = ft_replace_elements(input->cmds, new_cmd, i);
		i++;
	}
	i = 0; 
	while (input->cmds[i])
	{
		if (input->cmds[i][0] == '<' || input->cmds[i][0] == '>')
		{
			rd = ft_type_redirection(input->cmds[i]);
			if (rd > 0 && input->cmds[i + 1] == NULL)
				return (ft_print_error(5));
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

