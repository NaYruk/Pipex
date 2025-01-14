/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:08:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/14 16:20:51 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* 
	Function for check if the number of argument is good
	and for check if the 2 files are possible to open.
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
	if (access(argv[4], F_OK | W_OK) == -1)
	{
		perror("\033[31mERROR File2 \033[0m");
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

void	execute_second_command(char **argv, t_data *data)
{
	data->fd_file = open(argv[4], O_WRONLY);
	if (data->fd_file == -1)
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

/* Principal function of Pipex project */

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
