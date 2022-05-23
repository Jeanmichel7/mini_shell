/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:01 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/23 11:44:58 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ycheck_pipe(char *temp)
{
	int	i;
	int	u;

	i = 0;
	u = 1;
	while (temp[i])
	{
		if (temp[i] == '|')
		{
			u++;
			if (temp[i + 1] == '|')
				return (-1);
			while (temp[i] == ' ')
				i++;
			if (temp[i] == '|')
				return (-1);
			else if (temp[i] != 0) 
				i++;
		}
		else 
			i++;
	}
	return (u);
}

// creat an input list 
t_input	*ft_inputnew(void)
{
	t_input	*ptr;

	ptr = malloc(sizeof(t_input));
	if (ptr == NULL)
		return (NULL);
	ptr->child = 0;
	ptr->tab_fd= NULL;
	ptr->tube[0] = 0;
	ptr->tube[1] = 0;
	ptr->redir_input = 0;
	ptr->redir_output = 0;
	ptr->redir_double_input= 0;
	ptr->redir_double_output= 0;
	ptr->cmd_fct = NULL;
	ptr->cmds = NULL;
	ptr->pipe = 0;
	ptr->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

ft_replace_variable(char *, char ** env)
{

}

t_input	*ft_inputlast(t_input *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}


int	ft_yerror(int nb)
{
	if (nb == 258)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (258);
	}
}

int	ft_yparsing(t_data *data)
{
	int		i;
	char	**cmd;

	i = 0;
	if (ft_ycheck_pipe(data->temp) == -1)
		return(ft_yerror(258));
	if (ft_ycheck_pipe(data->temp) == -1)
		return(ft_yerror(258));
	printf("pipe number value : %d \n", nb_table);
	cmd = ft_split(data->temp, '|');
	if (cmd == NULL)
		return (1);
//	data->inputs.input->cmds = ft_split(*cmd);
	ft_yprint_input(data->inputs.input);
	return (0);
}
