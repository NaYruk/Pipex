/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:05:46 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/01/14 16:25:34 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmd1_path)
		free(data->cmd1_path);
	if (data->cmd2_path)
		free(data->cmd2_path);
	if (data->arg_cmd1)
	{
		while (data->arg_cmd1[++i] != NULL)
			free(data->arg_cmd1[i]);
		free(data->arg_cmd1);
	}
	i = -1;
	if (data->arg_cmd2)
	{
		while (data->arg_cmd2[++i] != NULL)
			free(data->arg_cmd2[i]);
		free(data->arg_cmd2);
	}
	if (data)
		free(data);
}

void	error(t_data *data)
{
	perror("\033[31mERROR");
	free_all(data);
	exit(EXIT_FAILURE);
}

char	*exec_find_path_command(char **arg_which, char *cmd_path, t_data *data)
{
	if (data->pid == 0)
	{
		close (data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close (data->fd[1]);
		if (execve("/usr/bin/which", arg_which, NULL) == -1)
			error(data);
	}
	else
	{
		close(data->fd[1]);
		if (waitpid(data->pid, &(data->status), 0) == -1)
			error(data);
		cmd_path = get_next_line(data->fd[0]);
		if (!cmd_path)
		{
			ft_putstr_fd
				("\033[31mERROR, command path is not found !\033[0m\n", 2);
			free_all(data);
			exit(EXIT_FAILURE);
		}
		cmd_path[ft_strlen(cmd_path) - 1] = '\0';
		close (data->fd[0]);
	}
	return (cmd_path);
}

char	*find_path_command(char *cmd, t_data *data)
{
	char	*cmd_path;
	char	*arg_which[3];

	arg_which[0] = "which";
	arg_which[1] = cmd;
	arg_which[2] = NULL;
	cmd_path = NULL;
	if (pipe(data->fd) == -1)
		error(data);
	data->pid = fork();
	cmd_path = exec_find_path_command(arg_which, cmd_path, data);
	return (cmd_path);
}

void	construct_commands(char **argv, t_data *data)
{
	data->arg_cmd1 = ft_split(argv[2], ' ');
	data->cmd1_path = find_path_command(data->arg_cmd1[0], data);
	data->arg_cmd2 = ft_split(argv[3], ' ');
	data->cmd2_path = find_path_command(data->arg_cmd2[0], data);
	return ;
}
