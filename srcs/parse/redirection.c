/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:12:09 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/01 17:23:54 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_fill_heredoc(char *pattern)
{
    char *ptr;
	char *temp; 	
	char *str; 
	int	fd;
	int pattern_found;

	fd = open("herdoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	str = NULL;
	ptr = NULL; 
	temp = NULL;
	pattern_found = 0;
	while (pattern_found == 0)
	{
		ptr = readline("heredoc>");
		pattern_found = ft_search_pattern(ptr, pattern);
		temp = str; 
		if (pattern_found == 0)
			str = ft_strjoin_andadd_rt(str, ptr);
		else 
			str = ft_strjoin(str, ptr);
		if (temp != NULL)
			free(temp);
		free(ptr);
		if (str == NULL)
			return (NULL);
	}
	write(fd, str, ft_strlen(str));
	return (ft_itoa(fd));
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
	{
		file = ft_fill_heredoc(file);		
		if (file == NULL)
			return  (ERROR_MEMORY);
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
			else if (ft_fulling_redir_para(rd, input, input->cmds[i + 1]) == ERROR_MEMORY)
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
			return(error);
		i++;
	}
	return (0);
}

