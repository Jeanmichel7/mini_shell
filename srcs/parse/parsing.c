/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:01 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/23 14:29:12 by ydumaine         ###   ########.fr       */
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
	return (ptr);
}
int	ft_replace_var(char **str, char *value, int length_name, int start)
{
	char *ptr;
	int i;
	int j;

	i = -1;
	j = -1;
	ptr = malloc(sizeof(char) * ((ft_strlen(*str) - length_name) + ft_strlen(value) + 1));
	if (ptr == NULL)
		return (1);
	while (++i < start)
		ptr[i] = (*str)[i];
	while (value[++j])
		ptr[i + j] = value[j];
	i = i + length_name;
	while ((*str)[i])
	{
		ptr[i + j] = (*str)[i];
		i++;
		j++;
	}
	free(*str);
	*str = ptr;
	return (0);
}
int	ft_ycheckandreplace_var(char **str, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*str)[i] != 0)
	{
		if ((*str)[i] == '$')
		{
			i++;
			while (*env != NULL)
			{
				j = 0;
				while ((*env)[j] != '=')
				{
					if ((*env)[j] != (*str)[i + j])
						break ;
					if ((*env)[j] == '=') 
					{
						if (ft_replace_var(str, &(*env)[j + 1], j, i) == 1)
							return (1);
						else 
							return (0);
					}

					j++;
				}
				(*env)++; 
			}
		}
		i++;
	}
	return (0);
}


int	ft_yerror(int nb)
{
	if (nb == 258)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (258);
	}
	return (0);
}

int	ft_yparsing(t_data *data)
{
	int		i;
	char	**cmd;

	i = 0;
	if (ft_ycheck_pipe(data->temp) == -1)
		return(ft_yerror(258));
	if (ft_ycheckandreplace_var(&data->temp, data->env) == 1)
		return(ft_yerror(258));
	cmd = ft_split(data->temp, '|');
	if (cmd == NULL)
		return (1);
//	data->inputs.input->cmds = ft_split(*cmd);
	ft_yprint_input(data->inputs);
	return (0);
}
