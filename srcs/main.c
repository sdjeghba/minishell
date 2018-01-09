/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:45:45 by sdjeghba          #+#    #+#             */
/*   Updated: 2018/01/09 12:48:53 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			minishell(char **env)
{
	t_data	data;

	data.env = ft_copy_tab(env);
	while (42)
	{
		data.prompt = NULL;
		data.var = NULL;
		ft_putstr("$> ");
		if (!(parse_prompt(&data)))
			if (!(check_builtins(&data)))
				exec_cmd(&data);
		if (data.prompt)
			ft_memdel((void**)&data.prompt);
		if (data.var)
			free_tab(&data.var);
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell(env);
	return (0);
}
