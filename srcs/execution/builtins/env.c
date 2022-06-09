/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:19:31 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/09 23:38:03 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_add_env(t_data *data, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	while (data->env[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (data->env[j])
	{
		new_env[j] = data->env[j];
		//free(data->env[j]);
		j++;
	}
	new_env[j] = data->inputs[i].cmds[1];
	j++;
	new_env[j] = NULL;
	return(new_env);
}

/*export NAME="valeur"*/
void	ft_export(t_data *data, int i)
{
	char	*str;
	char	*name;
	char	*str_value;
	int		j;

	str = data->inputs[i].cmds[1];
	if (str == NULL)
		fprintf(stderr, "pas d'arg je fais quoi ?\n");
	else
	{
		//check valid
		str_value = ft_strchr(str, '=');
		if (str_value == NULL)
		{
			ft_errputstr("bash: ", 0, 0, NULL);
			ft_errputstr(data->inputs[i].cmds[0], 0, 0, NULL);
			ft_errputstr(": '", 0, 0, NULL);
			ft_errputstr(data->inputs[i].cmds[1], 0, 0, NULL);
			ft_errputstr("': not a valid identifier", 0, 0, NULL);
			ft_errputstr("\n", 0, 0, NULL);
		}
		name = malloc(sizeof(char) * (str_value - str + 1));
		j = -1;
		while (++j < str_value - str)
			name[j] = str[j];
		name[j] = '\0';
		str_value = str_value + 1;
		fprintf(stderr, "str export : %s\n", str);
		fprintf(stderr, "export name : %s\n", name);
		fprintf(stderr, "export value : %s\n", str_value);
		data->env = ft_add_env(data, i);
		ft_env(data, i);
	}
}

void	ft_remove_line(t_data *data, int index_target)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (i != index_target)
			new_env[j++] = data->env[i];
		i++;
	}
	free(data->env);
	data->env = new_env;
}

void	ft_unset(t_data *data, int i)
{
	int		j;
	char	*value;
	
	value = data->inputs[i].cmds[1];
	j = 0;
	while (data->env[j])
		j++;
	if (ft_strlen(data->env[j]) == ft_strlen(value)
		&& strncmp(data->env[j], value, ft_strlen(value)) == 0)
		ft_remove_line(data, j);
}

void	ft_env(t_data *data, int i)
{
	int	j;

	(void)i;
	j = 0;
	while (data->env[j])
	{
		//printf("%d %s\n", j, data->env[j]);
		write(1, data->env[j], ft_strlen(data->env[j]));
		write(1, "\n", 1);
		j++;
	}
}
