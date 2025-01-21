/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:18:58 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/21 10:03:53 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*
	Function for execute the first command.
	- Open the infile file
	- Create a new processus with fork
	- if (data->pid == 0) = if the child process is active.
	- dup2 for redirect the standard input in the infile file.
	- dup2 for redirect the standard output in the fd[1] pipe.
	fd[1] = fd for write in the pipe.
	fd[0] = fd for read in the pipe.
	- execve for execute the first command :
		cmd1_path = path for the first command.
		arg_cmd1 = argument for the first command.
		NULL = environnement variable.
	- else = parent process.
	-waitpid = for wait the child process. the parent process is
				stop while the child process is active.
*/

void	execute_first_command(char **argv, t_data *data)
{
	if (pipe(data->curr_fd) == -1)
		error(data);
	data->pid = fork();
	if (data->pid == 0)
	{
		data->fd_file = open(argv[1], O_RDONLY);
		if (data->fd_file == -1)
			error(data);
		if (dup2(data->fd_file, STDIN_FILENO) == -1)
			error(data);
		close (data->fd_file);
		if (dup2(data->curr_fd[1], STDOUT_FILENO) == -1)
			error(data);
		close (data->curr_fd[0]);
		close (data->curr_fd[1]);
		if (execve(data->cmd_path, data->arg_cmd, NULL) == -1)
			error(data);
	}
	else
	{
		close (data->curr_fd[1]);
		if (waitpid(data->pid, &(data->status), 0) == -1)
			error(data);
	}
}

/*
	Function for execute the second command.
	- Open the outpput file, if the file exist erased the content of file
		if the file not exist, create the output file
	- Create a new processus with fork
	- if (data->pid == 0) = if the child process is active.
	- dup2 for redirect the standard input in the infile file.
	- dup2 for redirect the standard output in the fd[0] pipe.
	fd[1] = fd for write in the pipe.
	fd[0] = fd for read in the pipe.
	- execve for execute the first command :
		cmd1_path = path for the first command.
		arg_cmd1 = argument for the first command.
		NULL = environnement variable.
	- else = parent process.
	-waitpid = for wait the child process. the parent process is
				stop while the child process is active.
*/

void	execute_last_command(char **argv, t_data *data)
{
	data->pid = fork();
	if (data->pid == 0)
	{
		data->fd_file = open(argv[data->argv_index],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->fd_file == -1)
			error(data);
		if (dup2(data->curr_fd[0], STDIN_FILENO) == -1)
			error(data);
		close (data->curr_fd[0]);
		if (dup2(data->fd_file, STDOUT_FILENO) == -1)
			error(data);
		close (data->fd_file);
		close (data->curr_fd[1]);
		if (execve(data->cmd_path, data->arg_cmd, NULL) == -1)
			error(data);
	}
	else
	{
		close (data->curr_fd[0]);
		if (waitpid(data->pid, &(data->status), 0) == -1)
			error(data);
	}
}

void	execute_commands(t_data *data)
{
	if (pipe(data->curr_fd) == -1)
		error(data);
	data->pid = fork();
	if (data->pid == 0)
	{
		if (dup2(data->old_fd[0], STDIN_FILENO) == -1)
			error(data);
		close (data->old_fd[0]);
		if (dup2(data->curr_fd[1], STDOUT_FILENO) == -1)
			error(data);
		close (data->curr_fd[1]);
		close (data->curr_fd[0]);
		close (data->old_fd[1]);
		if (execve(data->cmd_path, data->arg_cmd, NULL) == -1)
			error(data);
	}
	else
	{
		close(data->old_fd[0]);
		close (data->curr_fd[1]);
		if (waitpid(data->pid, &(data->status), 0) == -1)
			error(data);
	}
}
