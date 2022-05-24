/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:01 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/24 20:47:35 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ycheck_pipe(char *temp)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (temp[i])
	{
		if (temp[i] == '|')
		{
			u++;
			i++;
			if (temp[i] == '|')
				return (-1);
			while (temp[i] == ' ')
				i++;
			if (temp[i] == '|')
				return (-1);
		}
		else 
			i++;
	}
	return (u);
}

void	*ft_freetab(char **tab)
{
	int	i;
	i = 0;

	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (NULL);
}


char **ft_envcpy(char **env)
{
	int	i;
	char **ptr;
	char *str;  	

	i = 0;
	while (env[i] != NULL)
		i++;
	ptr = ft_calloc((i + 1), sizeof(char **));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		str = ft_calloc((ft_strlen(env[i]) + 1), sizeof(char));
		if (str == NULL)
			return (ft_freetab(ptr));
		ft_strlcpy(str, env[i], (ft_strlen(env[i]) + 1));
		ptr[i] = str;
		i++;
	}
	return (ptr);
}

int	ft_strcpy_var(char **str, char *value, int length_name, int start)
{
	char *ptr;
	int i;
	int j;

	i = -1;
	j = -1;
	ptr = ft_calloc((ft_strlen(*str) - length_name) + ft_strlen(value) + 1, sizeof(char *));
	if (ptr == NULL)
		return (1);
	while (++i < start)
		ptr[i] = (*str)[i];
	while (value[++j])
		ptr[i + j] = value[j];
	i = i + length_name;
	length_name = length_name + i;
	while ((*str)[i])
	{
		ptr[length_name + j] = (*str)[i];
		i++;
		j++;
	}
	ptr[length_name + j] = 0;
	free(*str);
	*str = ptr;
	return (0);
}

int ft_checkvar(char *str, char *var, int *k)
{
	int	j; 

	j = 0;
	while (var[j])
	{
		if (var[j] == '=') 
		{
			*k = j + 1; 
			return (1);
		}
		if (var[j] != str[j])
			break ;
		j++;
	}
	return (0);
}

int	ft_replace_var(char **str, char **env)
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
				if (ft_checkvar(&(*str)[i], *env, &j) == 1)
				{
					if (ft_strcpy_var(str, &(*env)[j], j + 1, i - 1) == 1)
						return (1);
					else 
					{
						printf("\n valeur de la chaine de sortie : %s\n", *str);
						return (0);
					}
				}
				env = env + 1;
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
	if (nb == 5)
	{
		printf("Error! memory not allocated");
		return (5);
	}
	return (0);
}

void	*ft_create_inputs(t_data *data)
{
	t_input	*ptr;
	int 		i; 	

	i = 0;
	ptr = ft_calloc((data->nb_pipe + 1), sizeof(t_input));
	if (ptr == NULL)
		return (NULL);
	data->inputs = ptr; 
	return (NULL);
}

void	*ft_fulling_inputs(t_data *data)
{
	int i;
	char **cmd; 
	char **ptr;

	i = 0; 
	cmd = ft_split(data->temp, '|');
	while (i <= data->nb_pipe)
	{
		ptr = ft_split(cmd[i], ' ');	
		if (ptr == NULL)
			return (ft_freetab(cmd));
		data->inputs[i].cmds = ptr; 
		i++;
	}
	return (data);
}

int	ft_yparsing(t_data *data)
{
	int		i;

	i = 0;
	data->env = ft_envcpy(data->env);
	if (data->env == NULL)
		return(ft_yerror(5));
	data->nb_pipe =	ft_ycheck_pipe(data->temp);
	if (data->nb_pipe == -1)
		return(ft_yerror(258));
	if (ft_replace_var(&data->temp, data->env) == 1)
		return(ft_yerror(5));
	ft_create_inputs(data);
	ft_fulling_inputs(data);
	if (data->inputs == NULL)
		return(ft_yerror(5));
	ft_yprint_input(data);
	return (0);
}
