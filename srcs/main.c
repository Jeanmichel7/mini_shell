/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:38:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/17 12:36:03 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int main(int argc, char **argv, char **env)
{
	char			*temp;
	char			*prompt;
	int				done;
	register int	i;
	HIST_ENTRY 		**list;

	(void)argc;
	(void)argv;
	(void)env;
	prompt = "readline$ ";
	done = 0;

	while (!done)
	{
		temp = readline(prompt);
		if (!temp)
			exit(1);
		if (*temp)
		{
			printf("%s\r\n", temp);
			add_history(temp);
		}




		if (ft_strlen(temp) == 4 && strncmp(temp, "quit", 4) == 0)
			done = 1;
		if (ft_strlen(temp) == 4 && strncmp(temp, "list", 4) == 0)
		{
			list = history_list();
			if (list)
			{
				i = 0;
				while (list[i])
				{
					fprintf(stderr, "%d: %s\r\n", i, list[i]->line);
					i++;
				}
			}
		}
		free(temp);
	}
	return (0);
}
