/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:12:09 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/20 23:05:24 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		input->file[total - 1].fd = fd;
	if (rd == 4)
		input->file[total - 1].name = "herdoc.txt";
	return (0);
}

int	ft_check_cmd_redirection(int i, t_input *input)
{
	int	rd;

	if (input->cmds[i][0] == '<' || input->cmds[i][0] == '>')
	{			
		rd = ft_type_redirection(&input->cmds[i]);
		if (rd < 0)
			return (ft_print_error(rd));
		else if (ft_fulling_redir_para(rd, input,
				input->cmds[i + 1]) == ERROR_MEMORY)
			return (ERROR_MEMORY);
		input->cmds = ft_delete_files_name(input->cmds, i + 1, rd);
	}	
	return (0);
}

int	ft_split_redir_and_update_cmds(t_input *input)
{
	char	**new_cmd;
	char	**new_tab;
	int		i;

	i = 0;
	new_cmd = NULL;
	while (input->cmds[i] != NULL)
	{
		new_cmd = ft_split_redirection(input->cmds[i]);
		if (new_cmd == NULL && input->cmds != NULL)
			return (ERROR_MEMORY);
		new_tab = ft_replace_elements(input->cmds, new_cmd, &i);
		free(input->cmds);
		input->cmds = new_tab;
	}
	return (0);
}

int	ft_parse_input_redirection(t_input *input)
{
	int		i;
	int		rc;	

	rc = 0;
	if (input->cmds != NULL)
	{
		rc = ft_split_redir_and_update_cmds(input);
		if (rc != 0)
			return (rc);
	}
	i = -1;
	if (ft_update_file(NULL, &input->file, 0, 0) != 0)
		return (ERROR_MEMORY);
	while (input->cmds && input->cmds[++i])
	{
		rc = ft_check_cmd_redirection(i, input);
		if (rc != 0)
			return (rc);
		if (input->cmds[i] == NULL)
			break ;
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
