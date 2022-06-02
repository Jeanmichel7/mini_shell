/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:38:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/02 21:59:35 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
void	fake_init_inputs(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "ls";
	data->inputs[0].cmds[1] = "-al";
	data->inputs[0].cmds[2] = NULL;
}
*/
void	fake_init_inputs2(t_data *data)
{
	data->nb_pipe = 1;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "ls";
	data->inputs[0].cmds[1] = "-al";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].child = -1;

	data->inputs[1].file = malloc(sizeof(t_file) * 1);
	data->inputs[1].file[0].name = NULL;
	data->inputs[1].file[0].type = 0;
	data->inputs[1].file[0].fd = -1;

	data->inputs[1].cmds = malloc(sizeof(char **) * 3);
	data->inputs[1].cmds[0] = "cat";
	data->inputs[1].cmds[1] = "-e";
	data->inputs[1].cmds[2] = NULL;
}
/*
void	fake_init_inputs3(t_data *data)
{
	data->nb_pipe = 2;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "ls";
	data->inputs[0].cmds[1] = "-al";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].file = malloc(sizeof(t_file) * 1);
	data->inputs[1].file[0].name = NULL;
	data->inputs[1].file[0].type = 0;
	data->inputs[1].file[0].fd = -1;

	data->inputs[1].cmds = malloc(sizeof(char **) * 6);
	data->inputs[1].cmds[0] = "cut";
	data->inputs[1].cmds[1] = "-d";
	data->inputs[1].cmds[2] = "M";
	data->inputs[1].cmds[3] = "-f";
	data->inputs[1].cmds[4] = "2";
	data->inputs[1].cmds[5] = NULL;
	

	data->inputs[2].file = malloc(sizeof(t_file) * 1);
	data->inputs[2].file[0].name = NULL;
	data->inputs[2].file[0].type = 0;
	data->inputs[2].file[0].fd = -1;

	data->inputs[2].cmds = malloc(sizeof(char **) * 3);
	data->inputs[2].cmds[0] = "cat";
	data->inputs[2].cmds[1] = "-e";
	data->inputs[2].cmds[2] = NULL;
}

void	fake_init_inputs4(t_data *data)
{
	data->nb_pipe = 1;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "cat";
	data->inputs[0].cmds[1] = NULL;


	data->inputs[1].file = malloc(sizeof(t_file) * 1);
	data->inputs[1].file[0].name = NULL;
	data->inputs[1].file[0].type = 0;
	data->inputs[1].file[0].fd = -1;

	data->inputs[1].cmds = malloc(sizeof(char **) * 6);
	data->inputs[1].cmds[0] = "ls";
	data->inputs[1].cmds[1] = NULL;
}




 ************************************************ 




void	fake_init_inputs10(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));


	data->inputs[0].file = malloc(sizeof(t_file) * 3);
	data->inputs[0].file[0].name = "fichier_input.txt"; 
	data->inputs[0].file[0].type = IN;
	data->inputs[0].file[0].fd = -1; 

	data->inputs[0].file[1].name = "fichier_output.txt"; 
	data->inputs[0].file[1].type = OUT;
	data->inputs[0].file[1].fd = -1; 

	data->inputs[0].file[2].type = 0;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "cat";
	data->inputs[0].cmds[1] = "-e";
	data->inputs[0].cmds[2] = NULL;
}

void	fake_init_inputs20(t_data *data)
{
	data->nb_pipe = 1;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;
	data->inputs[0].file = malloc(sizeof(t_file) * 2);
	data->inputs[0].file[0].name = "fichier_input.txt";
	data->inputs[0].file[0].type = IN;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].file[1].type = 0;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "grep";
	data->inputs[0].cmds[1] = "a";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].child = -1;
	data->inputs[1].file = malloc(sizeof(t_file) * 2);
	data->inputs[1].file[0].name = "fichier_output.txt"; 
	data->inputs[1].file[0].type = APPEND;
	data->inputs[1].file[0].fd = -1;
	
	data->inputs[1].file[1].type = 0;

	data->inputs[1].cmds = malloc(sizeof(char **) * 3);
	data->inputs[1].cmds[0] = "cat";
	data->inputs[1].cmds[1] = "-e";
	data->inputs[1].cmds[2] = NULL;
}

void	fake_init_inputs30(t_data *data)
{
	data->nb_pipe = 2;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;
	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = "fichier_input.txt";
	data->inputs[0].file[0].type = IN;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "grep";
	data->inputs[0].cmds[1] = "a";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].file = malloc(sizeof(t_file) * 1);
	data->inputs[1].file[0].name = NULL;
	data->inputs[1].file[0].type = 0;
	data->inputs[1].file[0].fd = -1;

	data->inputs[1].cmds = malloc(sizeof(char **) * 6);
	data->inputs[1].cmds[0] = "cut";
	data->inputs[1].cmds[1] = "-d";
	data->inputs[1].cmds[2] = "l";
	data->inputs[1].cmds[3] = "-f";
	data->inputs[1].cmds[4] = "2";
	data->inputs[1].cmds[5] = NULL;
	

	data->inputs[2].file = malloc(sizeof(t_file) * 1);
	data->inputs[2].file[0].name = NULL;
	data->inputs[2].file[0].type = 0;
	data->inputs[2].file[0].fd = -1;

	data->inputs[2].cmds = malloc(sizeof(char **) * 3);
	data->inputs[2].cmds[0] = "cat";
	data->inputs[2].cmds[1] = "-e";
	data->inputs[2].cmds[2] = NULL;
}
*/

void	fake_init_inputs40(t_data *data)
{
	data->nb_pipe = 1;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;


	data->inputs[0].file = malloc(sizeof(t_file) * 3);
	data->inputs[0].file[0].name = "fichier_input.txt";
	data->inputs[0].file[0].type = IN;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].file[1].name = "fichier_output_real.txt";
	data->inputs[0].file[1].type = OUT;
	data->inputs[0].file[1].fd = -1;

	data->inputs[0].file[2].name = "fichier_output2.txt";
	data->inputs[0].file[2].type = OUT;
	data->inputs[0].file[2].fd = -1;

	data->inputs[0].file[3].type = 0;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "grep";
	data->inputs[0].cmds[1] = "a";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].file = malloc(sizeof(t_file) * 2);
	data->inputs[1].file[0].name = "autrefichier.txt";
	data->inputs[1].file[0].type = OUT;
	data->inputs[1].file[0].fd = -1;

	data->inputs[1].file[1].type = 0;

	data->inputs[1].cmds = malloc(sizeof(char **) * 3);
	data->inputs[1].cmds[0] = "cat";
	data->inputs[1].cmds[1] = "-e";
	data->inputs[1].cmds[2] = NULL;
}

/*
 ********************** BUILTINS ************************* 

void	fake_init_inputs100(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 4);
	data->inputs[0].cmds[0] = "echo";
	data->inputs[0].cmds[1] = "-n";
	data->inputs[0].cmds[2] = "testecho";
	data->inputs[0].cmds[3] = NULL;
}

void	fake_init_inputs101(t_data *data)
{
	data->nb_pipe = 1;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "cd";
	data->inputs[0].cmds[1] = "/";
	data->inputs[0].cmds[2] = NULL;


	data->inputs[1].file = malloc(sizeof(t_file) * 1);
	data->inputs[1].file[0].name = NULL;
	data->inputs[1].file[0].type = 0;
	data->inputs[1].file[0].fd = -1;

	data->inputs[1].cmds = malloc(sizeof(char **) * 3);
	data->inputs[1].cmds[0] = "ls";
	data->inputs[1].cmds[1] = "-l";
	data->inputs[1].cmds[2] = NULL;
}

void	fake_init_inputs102(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 2);
	data->inputs[0].cmds[0] = "env";
	data->inputs[0].cmds[1] = NULL;
}

void	fake_init_inputs103(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 2);
	data->inputs[0].file[0].name = "sorti_env.txt";
	data->inputs[0].file[0].type = OUT;
	data->inputs[0].file[0].fd = -1;
	data->inputs[0].file[1].type = 0;


	data->inputs[0].cmds = malloc(sizeof(char **) * 2);
	data->inputs[0].cmds[0] = "env";
	data->inputs[0].cmds[1] = NULL;
}

void	fake_init_inputs104(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 2);
	data->inputs[0].cmds[0] = "export";
	data->inputs[0].cmds[1] = "TEST=valeur";
	data->inputs[0].cmds[2] = NULL;
}



********************** ENV *************************

void	fake_init_inputs200(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "export";
	data->inputs[0].cmds[1] = "TEST=blabla";
	data->inputs[0].cmds[2] = NULL;
}

void	fake_init_inputs201(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 3);
	data->inputs[0].cmds[0] = "unset";
	data->inputs[0].cmds[1] = "USER";
	data->inputs[0].cmds[2] = NULL;
}

 ********************** ^C *************************

void	fake_init_inputs300(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 2);
	data->inputs[0].cmds[0] = "^C";
	data->inputs[0].cmds[1] = NULL;
}

char **ft_envcpy(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strlcpy(new_env[i], env[i], (ft_strlen(env[i]) + 1));
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ft_parse(t_data *data)
{
	data->nb_pipe = 0;
	data->inputs = malloc(sizeof(t_input) * (data->nb_pipe + 1));

	data->inputs[0].child = -1;

	data->inputs[0].file = malloc(sizeof(t_file) * 1);
	data->inputs[0].file[0].name = NULL;
	data->inputs[0].file[0].type = 0;
	data->inputs[0].file[0].fd = -1;

	data->inputs[0].cmds = malloc(sizeof(char **) * 2);
	data->inputs[0].cmds[0] = data->temp;
	data->inputs[0].cmds[1] = NULL;
}
*/


















char	*ft_color_prompt(void)
{
	char	pwd[500];
	char	*new_str;
	char	*pwd_color;
	char	*prompt_color;

	getcwd(pwd, 500);
	pwd_color = ft_strjoin("\033[0;34m", pwd);
	prompt_color = ft_strjoin("\033[0;32mminishell\033[0;37m:", pwd_color);
	free(pwd_color);
	new_str = ft_strjoin(prompt_color, "\033[0;37m$ ");
	free(prompt_color);
	return (new_str);
}

void	ft_init_data(t_data *data, char **env)
{
	data->temp = NULL;
	data->done = 0;
	data->env = ft_envcpy(env);
	data->fd_in_saved = dup (0);
	data->fd_out_saved = dup (1);
}

int main(int argc, char **argv, char **env)
{
	t_data	data;
	int		error; 

	(void)argc;
	(void)argv;
	error = 0;
	ft_init_data(&data, env);
	while (!data.done)
	{
		dup2(data.fd_in_saved, STDIN_FILENO);
		dup2(data.fd_out_saved, STDOUT_FILENO);
		while (wait(0) != -1);
		data.prompt = ft_color_prompt();
		data.temp = readline(data.prompt);
		if (!data.temp)
			exit(1);
		if (*data.temp)
			add_history(data.temp);
		//fake_init_inputs201(&data);
		error = ft_yparsing(&data);
		if (error == 0)
		{
			ft_yprint_input(&data);
			ft_exec_parse(&data);
			ft_free_section(&data);
		}
	}
	ft_free(&data);
	return (0);
}


/*
lsof -p 88103
*/
