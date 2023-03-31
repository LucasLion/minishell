/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:45:36 by amouly            #+#    #+#             */
/*   Updated: 2023/03/31 16:46:13 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_env_var_2(char *env, t_list_to_tab *cs)
{
	cs->count++;
	while (env[cs->count])
	{
		cs->ret[cs->j] = env[cs->count];
		(cs->j)++;
		cs->count++;
	}
}

void	copy_env_var(char *string_list, char **envp, int status,
		t_list_to_tab *cs)
{
	int	debut;
	int	b;

	(cs->i)++;
	if (string_list[cs->i] == '?')
	{
		last_error(cs->ret, &(cs->j), status);
		(cs->i)++;
	}
	else
	{
		debut = (cs->i);
		cs->count = size_var(string_list, &(cs->i));
		b = 0;
		while (envp[b])
		{
			if (!ft_strncmp(envp[b], &string_list[debut], (size_t)cs->count)
				&& envp[b][cs->count] == '=')
				copy_env_var_2(envp[b], cs);
			b++;
		}
	}
}

int	count_char(char *string_list, char **envp, int status)
{
	t_list_to_tab	cc;

	init_struct_ltt(&cc);
	while (string_list[cc.i])
	{
		cc.flag1 = put_flag(string_list[cc.i], cc.flag);
		if (string_list[cc.i] == '$' && cc.flag1 != 2)
		{
			if (string_list[cc.i + 1] == '\0' || string_list[cc.i + 1] == ' '
				|| string_list[cc.i + 1] == '$')
				add_one(&(cc.count), &(cc.i));
			else
				cc.count += count_size_env(string_list, &cc.i, envp, status);
		}
		else if (string_list[cc.i] == '"' && (cc.flag1 == 1 || (cc.flag1 == 0
					&& cc.flag == 1)))
			cc.i++;
		else if (string_list[cc.i] == '\'' && (cc.flag1 == 2 || (cc.flag1 == 0
					&& cc.flag == 2)))
			cc.i++;
		else
			add_one(&(cc.count), &(cc.i));
		cc.flag = cc.flag1;
	}
	return (cc.count);
}

char	*copy_string(char *string_list, char **envp, int status)
{
	t_list_to_tab	cs;

	init_struct_ltt(&cs);
	cs.ret = ft_calloc(count_char(string_list, envp, status) + 1, sizeof(char));
	while (string_list && string_list[cs.i])
	{
		cs.flag1 = put_flag(string_list[cs.i], cs.flag);
		if (string_list[cs.i] == '$' && cs.flag1 != 2 && string_list[cs.i
				+ 1] != '\0' && string_list[cs.i + 1] != ' ' && string_list[cs.i
				+ 1] != '$')
			copy_env_var(string_list, envp, status, &cs);
		else if (string_list[cs.i] == '"' && (cs.flag1 == 1 || (cs.flag1 == 0
					&& cs.flag == 1)))
			cs.i++;
		else if (string_list[cs.i] == '\'' && (cs.flag1 == 2 || (cs.flag1 == 0
					&& cs.flag == 2)))
			cs.i++;
		else
			cs.ret[cs.j++] = string_list[cs.i++];
		cs.flag = cs.flag1;
	}
	return (cs.ret);
}

char	**list_to_tab(t_command *list, char **envp, int status)
{
	int			len;
	char		**ret;
	int			i;
	t_string	*tmp;

	tmp = list->command;
	len = length_list_string(tmp);
	i = 0;
	ret = malloc(sizeof(char *) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = copy_string(tmp->string, envp, status);
		i++;
		tmp = tmp->next;
	}
	ret[i] = 0;
	return (ret);
}
