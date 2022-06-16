/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:34:35 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/09 21:53:03 by jrasser          ###   ########.fr       */
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
	fprintf(stderr," data->nb_pipe : %d \n", data->nb_pipe);
	while (i <= data->nb_pipe)
	{
		fprintf(stderr,"-----------------------------------\n");
		u = 0;
		fprintf(stderr,"| file redir: \n");
		while (ptr[i].file[u].type != 0)
		{
			fprintf(stderr,"| name: %s          \n", ptr[i].file[u].name);
			fprintf(stderr,"| type: %d          \n", ptr[i].file[u].type);
			fprintf(stderr,"| fd: %d          \n", ptr[i].file[u].fd);
			u++;
		}
		fprintf(stderr,"| child: %d          \n", ptr[i].child);
		fprintf(stderr,"| redir_data->inputs : %d                 \n", ptr[i].redir_input);
		fprintf(stderr,"| redit_output: %d                 \n", ptr[i].redir_output);
		fprintf(stderr,"| redir_double_data->input : %d          \n", ptr[i].redir_double_input);
		fprintf(stderr,"| redir_double_output: %d          \n", ptr[i].redir_double_output);

		//fprintf(stderr,"| cmd fonction: %s          \n", ptr[i].cmd_fct);
		fprintf(stderr,"| cmds :");
		u = 0;
		if (ptr[i].cmds != NULL)
		{
			while (ptr[i].cmds[u] != NULL)
			{
				fprintf(stderr,"[%s] ", (ptr[i].cmds[u]));
				u++;
			}
		}
		fprintf(stderr,"\n-----------------------------------\n");
		i++;
	}
	return (0);
}

int	ft_print_tab(char **tab)
{
	int	i; 

	i = 0;
	if (tab != NULL)
	{
		while(tab[i])
		{
			fprintf(stderr,"\n addresse tab[%d] : %p", i, &tab[i]);
			fprintf(stderr,"\n valeur de tab[%d] : %s", i, tab[i]);
			i++;
		}
	}
	fprintf(stderr,"\n end of tab");
	return (0);
}
