/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:08:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/18 15:30:33 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* 
	Function for check if the number of argument is good
	and for check if the input file is possible to open.
*/

void	potential_error(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("ERROR, need 5 argument", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror("ERROR");
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
		ft_putstr_fd("ERROR, malloc error\n", 2);
		exit(EXIT_FAILURE);
	}
	data->cmd_path = NULL;
	data->arg_cmd = NULL;
	data->path_line = NULL;
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->fd_file = 0;
	data->pid = 0;
	data->status = 0;
	data->argv_index = 2;
	data->number_of_command = 0;
	return (data);
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

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	potential_error(argc, argv);
	data = initialize_data();
	data->number_of_command = argc - 3;
	find_envp(data, envp);
	construct_commands(data, argv);
	data->number_of_command--;
	if (pipe(data->fd) == -1)
		error(data);
	execute_first_command(argv, data);
	while (data->number_of_command > 1)
	{
		construct_commands(data, argv);
		//execute_commands(data);
		data->number_of_command--;
	}
	construct_commands(data, argv);
	execute_last_command(argv, data);
	free_all(data);
	return (0);
}




/*  Pour gerer plusieurs pipe, il faudra traiter autant de commandes que demander. 
	Pour cela, il faut faire la creation des commandes independamment a chaque fois,
	faire commande par commande, jusqu a que argc <= argc - 1;
	Trouver le path de la commande actuelle, puis executer la commande. 
	Puis retrouver le path de la commande suivante et donner en entree la commande precedente.
	Puis quand on est a la derniere commande, rediriger dans le fichier donner en argument.



	Pour lundi, cree un systeme pour pouvoir cree plusieurs pipe, un pipe precedant et un pipe actuel.
	Le precedant aura les infos de celui d avant, le nouveau processus prendra en entree le pipe precedant
	et en sorti renverra dans son propre pipe, puis le pipe actuel devient le precedant et ainsi de suite.*/