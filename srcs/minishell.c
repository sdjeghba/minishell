/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:46:27 by sdjeghba          #+#    #+#             */
/*   Updated: 2018/01/09 13:17:42 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_func g_tab[] =
{
	{&display_env, "env"},
	{&delete_var_env, "unsetenv"},
	{&set_env, "setenv"},
	{&b_echo, "echo"},
	{&b_exit, "exit"},
	{&b_cd, "cd"},
	{NULL, "NULL"}
};

char		*verify_access(char **tab, char *arg)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	while (tab[++i])
	{
		str = ft_place_between_str(tab[i], arg, "/");
		if (access(str, R_OK) == 0)
			return (tab[i]);
	}
	return (NULL);
}

int			check_builtins(t_data *data)
{
	int		i;

	i = -1;
	while (g_tab[++i].cmd)
		if (!(ft_strcmp(g_tab[i].cmd, data->var[0])))
		{
			g_tab[i].ptrfunc(data);
			return (1);
		}
	return (0);
}

char		*get_path(t_data *data)
{
	char	*tmp;
	char	*ret;
	char	*line;
	char	**paths;
	int		i;

	tmp = NULL;
	if (access(data->var[0], R_OK) == 0)
		return (data->var[0]);
	i = search_var_env(data->env, "PATH");
	tmp = (i > 0 ? data->env[search_var_env(data->env, "PATH")] : NULL);
	if (tmp)
	{
		line = ft_strsub(tmp, 5, ft_strlen(tmp) - 5);
		paths = ft_strsplit(line, ':');
		ret = verify_access(paths, data->var[0]);
		if (!(ret))
			return (NULL);
		else
		{
			tmp = ret;
			return (ft_strjoin(tmp, "/"));
		}
	}
	return (NULL);
}

void		exec_cmd(t_data *d)
{
	pid_t	father;
	char	*path;

	path = NULL;
	if (!(father = fork()))
	{
		path = get_path(d);
		execve(d->var[0], d->var, d->env);
		execve(ft_strjoin(path, d->var[0]), d->var, d->env);
		ft_putstr("command not found: ");
		ft_putendl(d->var[0]);
		exit(EXIT_FAILURE);
	}
	else
		wait(&father);
}

int			parse_prompt(t_data *data)
{
	int		i;

	i = -1;
	if (get_next_line(0, &data->prompt) == 0)
		exit(-1);
	if (!(ft_strlen(data->prompt)))
		return (-1);
	data->var = ft_splitwhitesp(data->prompt);
	if (!data->var[0])
		return (-1);
	return (0);
}
