#include "../includes/minishell.h"

int	ft_pre_parsing(t_data *data)
{
	int i; 

	i = 0;
	while (data->temp[i])
	{
		if (data->temp[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
