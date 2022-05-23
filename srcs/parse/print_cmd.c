/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:34:35 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/19 16:22:29 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	ft_yprint_cmds(t_input *input)
{
	char **cmd;

	cmd = input->cmds; 

	while (cmd)
	{
		printf("[%s] ", *cmd);
		cmd = cmd + 1;
	}
}

void	ft_yprint_input(t_input *input)
{
	while (input)
	{
		printf("-----------------------------------\n");
		printf("| redir_input : %d                 \n", input->redir_input);
		printf("| redit_output: %d                 \n", input->redir_output);
		printf("| redir_double_input : %d          \n", input->redir_double_input);
		printf("| redir_double_output: %d          \n", input->redir_double_output);
		printf("| input->cmds : ");
		ft_yprint_cmds(input);
		printf("\n-----------------------------------\n");
		input++;
	}
}

