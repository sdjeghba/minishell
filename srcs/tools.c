/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 17:11:37 by sdjeghba          #+#    #+#             */
/*   Updated: 2018/01/09 12:48:46 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			b_echo(t_data *data)
{
	int		i;

	i = 0;
	!data->var[1] ? write(1, "\n", 1) : 0;
	while (data->var[++i])
	{
		ft_putstr(data->var[i]);
		data->var[i + 1] == '\0' ? ft_putchar('\n') : ft_putchar(' ');
	}
	return (0);
}

int			b_exit(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int			str_upper(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_isupper(str[i])))
			return (-1);
	}
	return (0);
}

int			display_env(t_data *data)
{
	int		i;

	i = -1;
	while (data->env[++i])
		ft_putendl(data->env[i]);
	return (0);
}

void		free_tab(char ***tab)
{
	ft_free_tab(*tab);
	free(*tab);
}
