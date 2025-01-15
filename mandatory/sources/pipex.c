/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:08:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/15 13:05:31 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* 
	Function for check if the number of argument is good
	and for check if the input file is possible to open.
*/

void	potential_error(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("\033[31mERROR, need 5 argument\033[0m\n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror("\033[31mERROR File1 \033[0m");
		exit(EXIT_FAILURE);
	}
}

/* Function for initialize the data struct */

t_data	*initialize_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("\033[31mERROR, malloc error\033[0m\n", 2);
		exit(EXIT_FAILURE);
	}
	data->cmd1_path = NULL;
	data->cmd2_path = NULL;
	data->arg_cmd1 = NULL;
	data->arg_cmd2 = NULL;
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->fd_file = 0;
	data->pid = 0;
	data->status = 0;
	return (data);
}

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
	data->fd_file = open(argv[1], O_RDONLY);
	if (data->fd_file == -1)
		error(data);
	data->pid = fork();
	if (data->pid == 0)
	{
		dup2(data->fd_file, STDIN_FILENO);
		close (data->fd_file);
		close (data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close (data->fd[1]);
		if (execve(data->cmd1_path, data->arg_cmd1, NULL) == -1)
			error(data);
	}
	else
	{
		close (data->fd[1]);
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

void	execute_second_command(char **argv, t_data *data)
{
	data->fd_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->fd_file == -1)
		error(data);
	if (access(argv[4], W_OK | R_OK | F_OK) == -1)
		error(data);
	data->pid = fork();
	if (data->pid == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		close (data->fd[0]);
		dup2(data->fd_file, STDOUT_FILENO);
		close (data->fd_file);
		if (execve(data->cmd2_path, data->arg_cmd2, NULL) == -1)
			error(data);
	}
	else
	{
		close (data->fd_file);
		close (data->fd[0]);
		if (waitpid(data->pid, &(data->status), 0) == -1)
			error(data);
	}
}

/* 
	Principal function of Pipex project 
	- potential_error = function for detecte if argument error is present
						and check if the infile
						and outfile file are possible to open.
	- initialize_data = function for initialize all variable at 0 or NULL
	- construct_command = function for find the path for all command.
			and for created a char ** for collected the command argument.
	- execute_command = two function for execute the first and second command
						with a pipe.
*/

int	main(int argc, char **argv)
{
	t_data	*data;

	potential_error(argc, argv);
	data = initialize_data();
	construct_commands(argv, data);
	if (pipe(data->fd) == -1)
		error(data);
	execute_first_command(argv, data);
	execute_second_command(argv, data);
	free_all(data);
	return (0);
}
