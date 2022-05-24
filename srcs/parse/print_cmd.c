/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:34:35 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/24 21:55:19 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	ft_yprint_input(t_data *data)
{
	int	i;
	int	u;
	t_input *ptr; 

	i = 0;
	ptr = data->inputs;	
	printf(" data->nb_pipe : %d \n", data->nb_pipe);
	while (i <= data->nb_pipe)
	{
			u = 0;
		printf("-----------------------------------\n");
		printf("| redir_data->inputs : %d                 \n", ptr[i].redir_input);
		printf("| redit_output: %d                 \n", ptr[i].redir_output);
		printf("| redir_double_data->input : %d          \n", ptr[i].redir_double_input);
		printf("| redir_double_output: %d          \n", ptr[i].redir_double_output);
		printf("| cmds :");
		if (ptr[i].cmds != NULL)
		{
			while (ptr[i].cmds[u] != NULL)
			{
				printf("[%s] ", (ptr[i].cmds[u]));
				u++;
			}
		}
		printf("\n-----------------------------------\n");
		i++;
	}
}

