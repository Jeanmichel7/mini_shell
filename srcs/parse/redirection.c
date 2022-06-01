/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:12:09 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/02 01:23:22 by ydumaine         ###   ########.fr       */
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
	{
		ptr = readline("heredoc>");
		pattern_found = ft_search_pattern(ptr, pattern);
		temp = str;
		if (pattern_found == 0)
			str = ft_strjoin_andadd_rt(str, ptr);
		else
			str = ft_strjoin(str, ptr);
		if (temp != 0)
			free(temp);
		free(ptr);
		if (str == 0)
			return (0);
	}
	write(fd, str, ft_strlen(str));
	return (fd);
}

int	ft_fulling_redir_para(int rd, t_input *input, char *file)
{
	int	total;
	int	fd;

	if (rd == 3)
		input->redir_double_output++;
	if (rd == 2)
		input->redir_output++;
	if (rd == 1)
		input->redir_input++;
	if (rd == 4)
	{
		fd = ft_fill_heredoc(file);
		if (fd == 0)
			return (ERROR_MEMORY);
		input->redir_double_input++;
	}
	total = input->redir_double_output + input->redir_output
		+ input->redir_input + input->redir_double_input;
	if (ft_update_file(file, &input->file, total, rd) != 0)
		return (ERROR_MEMORY);
	if (rd == 4)
	{
		input->file[total].fd = fd;
		input->file[total].name = NULL;
	}
	return (0);
}

int	ft_parse_input_redirection(t_input *input)
{
	int		i;
	char	**new_cmd;
	int		rd;
	char	*file;

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
	if (ft_update_file(NULL, &input->file, 0, 0) != 0)
		return (ERROR_MEMORY);
	while (input->cmds[i])
	{
		if (input->cmds[i][0] == '<' || input->cmds[i][0] == '>')
		{			
			rd = ft_type_redirection(&input->cmds[i]);
			if (rd < 0)
				return (ft_print_error(rd));
			else if (ft_fulling_redir_para(rd, input,
					input->cmds[i + 1]) == ERROR_MEMORY)
				return (ERROR_MEMORY);
		}
		i++;
	}
	input->cmds = ft_delete_rd(input->cmds);
	return (0);
}

int	ft_parse_redirection(t_data *data)
{
	int	error;
	int	i;

	i = 0;
	error = 0;
	while (i <= data->nb_pipe)
	{
		error = ft_parse_input_redirection(&data->inputs[i]);
		if (error != 0)
			return (error);
		i++;
	}
	return (0);
}
