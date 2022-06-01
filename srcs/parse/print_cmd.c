/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:34:35 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/01 20:32:52 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_yprint_input(t_data *data)
{
	int	i;
	int	u;
	t_input *ptr; 

	i = 0;
	ptr = data->inputs;
	printf(" data->nb_pipe : %d \n", data->nb_pipe);
	while (i <= data->nb_pipe)
	{
		printf("-----------------------------------\n");
		u = 0;
		printf("| file redir: \n");
		while (ptr[i].file[u].type != 0)
		{
			printf("| name: %s          \n", ptr[i].file[u].name);
			printf("| type: %d          \n", ptr[i].file[u].type);
			printf("| fd: %d          \n", ptr[i].file[u].fd);
			u++;
		}
		printf("| child: %d          \n", ptr[i].child);
		printf("| redir_data->inputs : %d                 \n", ptr[i].redir_input);
		printf("| redit_output: %d                 \n", ptr[i].redir_output);
		printf("| redir_double_data->input : %d          \n", ptr[i].redir_double_input);
		printf("| redir_double_output: %d          \n", ptr[i].redir_double_output);

		//printf("| cmd fonction: %s          \n", ptr[i].cmd_fct);
		printf("| cmds :");
		u = 0;
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
	return (0);
}

int	ft_print_tab(char **tab)
{
	int	i; 
	int j;

	i = 0;
	j = 0;
	if (tab != NULL)
	{
		while(tab[i])
		{
			ft_printf("\n addresse tab[%d] : %p", i, &tab[i]);
			ft_printf("\n valeur de tab[%d] : %s", i, tab[i]);
			i++;
		}
	}
	ft_printf("\n end of tab");
	return (0);
}
