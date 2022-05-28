/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:19:31 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/28 22:42:52 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*export NAME="valeur"*/
void	ft_export(t_data *data, int i)
{
	char	*str;
	char	*name;
	char	*str_value;
	int		j;

	str = data->inputs[i].cmds[1];
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

}

void	ft_unset(t_data *data, int i)
{
	(void)data;
	(void)i;

	printf("blablablablabalbala\n");
}

void	ft_env(t_data *data, int i)
{
	int	j;

	(void)i;
	j = 0;
	while (data->env[j])
	{
		write(1, data->env[j], ft_strlen(data->env[j]));
		write(1, "\n", 1);
		j++;
	}
}
