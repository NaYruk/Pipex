/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:05:46 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/01/16 18:58:39 by marcmilliot      ###   ########.fr       */
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
	data->envp = ft_split(data->path_line, ':');
	if (!data->envp)
		error(data);
	i = -1;
	while (data->envp[++i] != NULL)
	{
		tmp = ft_add_back_string(data->envp[i], "/");
		free(data->envp[i]);
		data->envp[i] = tmp;
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
	while (data->envp[++i] != NULL)
	{
		tmp = ft_add_back_string(data->envp[i], command);
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

void	construct_commands(t_data *data, char **argv, char **envp)
{
	data->arg_cmd1 = ft_split(argv[2], ' ');
	if (!data->arg_cmd1)
		error(data);
	data->arg_cmd2 = ft_split(argv[3], ' ');
	if (!data->arg_cmd2)
		error(data);
	find_envp(data, envp);
	data->cmd1_path = find_command_path(data, data->arg_cmd1[0]);
	if (!data->cmd1_path)
		error(data);
	data->cmd2_path = find_command_path(data, data->arg_cmd2[0]);
	if (!data->cmd2_path)
		error(data);
}
