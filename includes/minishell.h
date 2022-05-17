/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:27:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/17 13:43:31 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>

/*
exemple de char *cmds (tout le contenu entre 2 pipes)
[0] : "ls"
[1] : "-arth"
[2] : ">"
[3] : "fichier"
*/

typedef struct s_input
{
	int		redir_input;
	int		redir_output;
	int		redir_double_input;
	int		redir_double_output;
	char	*cmds;
}	t_input;

typedef struct s_inputs
{
	int		nb_pipe;
	t_input	*input;  // => tableau d'input (genre 3pipe => 4 inputs différents)
}	t_inputs;

/* si t'as une meilleur idée pour le nom des structures inputs / input (c'est un peu confu ou ca va ?) 
ou d'une autre strucutre merci de me contacter au 3615 */
#endif