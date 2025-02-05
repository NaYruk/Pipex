/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:05:46 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/02/05 12:47:14 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* 
	Function for find the environnement variable
	Search "PATH=" = environnement variable.
	Delete "PATH="
	split all path for make a char ** with each path of exec. 
*/

void	find_envp(t_data *data, char **envp)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	data->path_line = envp[i];
	while (!ft_strnstr(data->path_line, "PATH=", 5) && (envp[i] != NULL))
		data->path_line = envp[++i];
	data->path_line = ft_substr(data->path_line, 5,
			ft_strlen(data->path_line));
	data->env_var = ft_split(data->path_line, ':');
	if (!data->env_var)
		error(data);
	i = -1;
	while (data->env_var[++i] != NULL)
	{
		tmp = ft_add_back_string(data->env_var[i], "/");
		free(data->env_var[i]);
		data->env_var[i] = tmp;
	}
	return ;
}

/*
	find_command_path = function for add the name of the command
						behind each path and test with access function
						if a path is found and if it is executable.
*/

char	*find_command_path(t_data *data, char *command)
{
	int		i;
	char	*tmp;

	i = -1;
	while (data->env_var[++i] != NULL)
	{
		tmp = ft_add_back_string(data->env_var[i], command);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

/* 
	Function for construct commands :
	data->arg_cmd = command + arguments in a char **
	data->cmd_path = path for execute the command.
	
	For that, we split arguments for make a char ** command + arguments
	find_envp = function for find the path of environnement variables.
				+ cut PATH= + put a / behind each path.
	find_command_path = function for add the name of the command
						behind each path and test with access function
						if a path is found and if it is executable.
						else error.
*/

void	construct_commands(t_data *data, char **argv)
{
	int	i;

	i = -1;
	if (data->arg_cmd)
	{
		while (data->arg_cmd[++i] != NULL)
			free(data->arg_cmd[i]);
		free(data->arg_cmd);
	}
	data->arg_cmd = ft_split(argv[data->argv_index], ' ');
	if (!data->arg_cmd)
		error(data);
	if (data->cmd_path)
		free(data->cmd_path);
	data->cmd_path = find_command_path(data, data->arg_cmd[0]);
	if (!data->cmd_path)
		command_not_found(data);
	data->argv_index++;
}
