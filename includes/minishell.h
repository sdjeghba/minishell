/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:17:11 by sdjeghba          #+#    #+#             */
/*   Updated: 2018/01/09 12:52:15 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

typedef struct	s_data
{
	char		**env;
	char		*prompt;
	char		**var;
}				t_data;

typedef	struct	s_func
{
	int			(*ptrfunc)(t_data *data);
	char		*cmd;
}				t_func;

int				minishell(char **env);

/*
** minishell.c
*/

char			*verify_access(char **tab, char *arg);
char			*get_path(t_data *data);
void			exec_cmd(t_data *d);
int				parse_prompt(t_data *data);
int				check_builtins(t_data *data);

/*
** handle_env.c
*/
int				search_var_env(char **tab, char *var);
int				delete_var_env(t_data *data);
int				del_loop(char **tmp, t_data *data, int line);
int				set_env(t_data *data);
int				add_end_of_tab(t_data *data, char *var, char *value);

/*
** cd_builtin.c
*/

int				reverse_pwds(t_data *data, char *oldpwd, char *pwd);
int				change_dir(t_data *data);
int				cd_dash(t_data *data);
int				cd_home(t_data *data);
int				b_cd(t_data *data);

/*
**	tools.c
*/

int				b_echo(t_data *data);
int				b_exit(t_data *data);
void			free_tab(char ***tab);
int				display_env(t_data *data);
int				str_upper(char *str);

#endif
