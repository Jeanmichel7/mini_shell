/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:27:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/01 17:22:21 by ydumaine         ###   ########.fr       */
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
# include <errno.h>

#define ERROR_PIPE 1001
#define ERROR_MEMORY 1002
#define ERROR_REDIRECTION 1003
/*
typedef struct t_li
{
	int				content;
	struct t_li		*next;
}	t_li;
*/
typedef enum e_type
{
	IN = 1,
	OUT,
	APPPEND,
	HEREDOC,
}	t_type;

typedef struct s_file
{
	char	*name;
	t_type	type;
	int		fd;
}	t_file;

typedef struct s_input
{
	pid_t			child;
	t_file			*files;
	int				tube[2];
	int				redir_input;
	int				redir_output;
	int				redir_double_input;
	int				redir_double_output;
//	t_li			*rd_usefull;
	char			*cmd_fct;
	int				*is_a_string;
	char			**cmds;
	int				pipe;
}	t_input;

typedef struct s_data
{
	char			**env;
	int				nb_pipe;
	char			*temp;
	char			*prompt;
	int				done;
	HIST_ENTRY		**list;
	t_input			*inputs;
}	t_data;

/* PARSING */

/* EXECUTION */
void	ft_jm_part(t_data *data, char **env);

void	ft_pipe(t_data *data, char **env);
void	ft_check_cmds(char *fct, char *args);
char	*ft_check_access(char **env, char *cmd);

void	ft_errputstr(char *str, int stop, int code, t_data *data);
int		ft_yprint_input(t_data *data);
int		ft_yparsing(t_data *data);
char	**ft_split_and_omit(char const *s, char c, int keep_quotes);
int		ft_omit_quote_apostrophe(char c, unsigned int omit, unsigned int *i, int keep_quotes);
char	*ft_strjoin_andadd_rt(char const *s1, char const *s2);
int 	ft_parse_redirection(t_data *data); 
char	**ft_split_redirection(char const *s);
char	**ft_replace_elements(char **tab, char **elements, int *pos);
int		ft_freetab(char **tab);
int		ft_print_tab(char **tab);
//int		ft_which_redirection_take_on_board(const char *s, t_li **list);
int		ft_which_redirection_take_on_board(char *s);
int		ft_omit_quote_apostrophe(char c, unsigned int omit, unsigned int *i, int keep_quotes);
int		ft_freetab(char **tab);
int		ft_ycheck_pipe(char *temp);
char	*ft_if_quotes_not_closes(t_data *data);
char 	**ft_envcpy(char **env);
void	*ft_create_inputs(t_data *data);
int		ft_yerror(int nb, t_data *data);
int		ft_check_and_replace_var(char **str, char **env);
int		ft_replace_var(char **str, char **env, int *i, int *j);
int		ft_checkvar(char *str, char *var, int *k);
int		ft_strcpy_var(char **str, char *value, int length_name, int start);
int		ft_retrieve_string(int omit, t_data *data, char *temp, char *ptr);
int		ft_print_error(int rd);
int 	ft_type_redirection(char **str);
int		ft_search_pattern(char *str, char *pattern);
int		ft_update_file(char *str, t_file *files, int total, int rd);


//t_li	*ft_lsti_new_t_li(int content);


#endif
