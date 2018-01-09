/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 17:29:45 by sdjeghba          #+#    #+#             */
/*   Updated: 2018/01/07 19:24:08 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			search_var_env(char **tab, char *var)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (tab[i])
	{
		while (tab[i][j] && tab[i][j] != '=')
			j++;
		tmp = ft_strsub(tab[i], 0, j);
		if (ft_strcmp(tmp, var) == 0)
		{
			tmp ? ft_memdel((void**)&tmp) : 0;
			return (i);
		}
		i++;
		j = 0;
		tmp ? ft_memdel((void**)&tmp) : 0;
	}
	return (-1);
}

int			add_end_of_tab(t_data *data, char *var, char *value)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	j = 0;
	if (!(env = malloc(sizeof(char *) * (ft_get_tab_height(data->env) + 2))))
		return (-1);
	while (data->env[i])
		env[j++] = ft_strdup(data->env[i++]);
	if (value)
		env[j++] = ft_place_between_str(var, value, "=");
	else
		env[j++] = ft_strjoin(var, "=");
	env[j] = NULL;
	free_tab(&data->env);
	data->env = ft_copy_tab(env);
	free_tab(&env);
	return (0);
}

int			set_env(t_data *data)
{
	int		line;
	char	*var;

	line = 0;
	var = NULL;
	if (data->var[1] && (ft_get_tab_height(data->var) < 4) &&
			(str_upper(data->var[1]) == 0))
	{
		line = search_var_env(data->env, data->var[1]);
		if (line >= 0)
		{
			ft_strlen(data->env[line]) ? ft_strdel(&data->env[line]) : 0;
			data->env[line] = (!data->var[2] ? ft_strjoin(data->var[1], "=") :
				ft_place_between_str(data->var[1], data->var[2], "="));
		}
		else
			!data->var[2] ? add_end_of_tab(data, data->var[1], NULL) :
				add_end_of_tab(data, data->var[1], data->var[2]);
	}
	else
		ft_putendl("usage : setenv VARIABLE value");
	return (0);
}

int			del_loop(char **tmp, t_data *data, int line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(tmp = malloc(sizeof(char *) * ft_get_tab_height(data->env))))
		return (-1);
	while (i < line)
		tmp[i++] = ft_strdup(data->env[j++]);
	j = line + 1;
	while (data->env[j])
		tmp[i++] = ft_strdup(data->env[j++]);
	tmp[i] = NULL;
	free_tab(&data->env);
	data->env = ft_copy_tab(tmp);
	free_tab(&tmp);
	return (0);
}

int			delete_var_env(t_data *data)
{
	int		line;
	char	**tmp;

	line = 0;
	tmp = NULL;
	if (data->var[1] && (ft_get_tab_height(data->var) == 2))
	{
		line = search_var_env(data->env, data->var[1]);
		if (line >= 0)
			del_loop(tmp, data, line);
		else
			ft_putendl("environnement variable not found");
	}
	else
		ft_putendl("usage : unsetenv VARIABLE");
	return (0);
}
