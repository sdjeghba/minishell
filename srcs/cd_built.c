/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salemdjeghbala <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 02:32:57 by salemdjeg         #+#    #+#             */
/*   Updated: 2018/01/09 12:53:58 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			reverse_pwds(t_data *data, char *oldpwd, char *pwd)
{
	int		p;
	int		o;

	p = search_var_env(data->env, "PWD");
	o = search_var_env(data->env, "OLDPWD");
	if (p < 0)
		add_end_of_tab(data, "PWD", pwd);
	else
	{
		ft_strdel(&data->env[p]);
		data->env[p] = ft_place_between_str("PWD", pwd, "=");
	}
	if (o < 0)
		add_end_of_tab(data, "OLDPWD", oldpwd);
	else
	{
		ft_strdel(&data->env[o]);
		data->env[o] = ft_place_between_str("OLDPWD", oldpwd, "=");
	}
	return (0);
}

int			change_dir(t_data *data)
{
	char	pwd[4096];
	char	oldpwd[4096];

	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(data->var[1]))
	{
		ft_putendl("error: wrong path");
		return (-1);
	}
	if (!(getcwd(pwd, sizeof(pwd))))
	{
		ft_putendl("error: can't open the directory");
		return (-1);
	}
	reverse_pwds(data, oldpwd, pwd);
	return (0);
}

int			cd_dash(t_data *data)
{
	int		line;
	char	*tmp;
	char	oldpwd[4096];

	line = search_var_env(data->env, "OLDPWD");
	if (line < 0)
	{
		ft_putendl("error: variable OLDPWD not set");
		return (-1);
	}
	getcwd(oldpwd, sizeof(oldpwd));
	tmp = ft_strsub(data->env[line], 7, (ft_strlen(data->env[line]) - 7));
	if (chdir(tmp))
	{
		ft_putendl("error: can't open the directory, check your OLDPWD");
		return (-1);
	}
	reverse_pwds(data, oldpwd, tmp);
	ft_strlen(tmp) ? ft_strdel(&tmp) : 0;
	return (0);
}

int			cd_home(t_data *data)
{
	int		line;
	char	*home;
	char	oldpwd[4096];

	line = search_var_env(data->env, "HOME");
	if (line < 0)
	{
		ft_putendl("error: please set your variable HOME");
		return (-1);
	}
	getcwd(oldpwd, sizeof(oldpwd));
	home = ft_strsub(data->env[line], 5, (ft_strlen(data->env[line]) - 5));
	if (chdir(home))
		ft_putendl("error: please check you HOME environemment variable");
	else
		reverse_pwds(data, oldpwd, home);
	ft_strlen(home) ? ft_strdel(&home) : 0;
	return (0);
}

int			b_cd(t_data *data)
{
	if (!(data->var[1]))
		cd_home(data);
	else if (ft_get_tab_height(data->var) > 2)
		ft_putendl("usage: cd /tape/your/path/here");
	else if (!(ft_strcmp("-", data->var[1])))
		cd_dash(data);
	else
		change_dir(data);
	return (0);
}
