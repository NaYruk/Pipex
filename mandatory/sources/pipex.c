/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:08:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/13 13:05:45 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	potential_error(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error, wrong number of argument, need 5 argument\n", 2);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror("Error File1 !");
		exit(EXIT_FAILURE);
	}
	if (access(argv[4], F_OK | W_OK) == -1)
	{
		perror("Error File2 !");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	pid_t	pid;
	int		*status_t = NULL;
	char 	*arg[] = {"grep", "Faire", "plan.txt", NULL};
	
	(void)argc;
	(void)argv;
	//potential_error(argc, argv);
	pid = fork();
	if (pid == 0)
	{
		if (execve("/bin/grep", arg, NULL) == -1)
		{
			perror("execve");
			return (1);
		}
	}
	else
		waitpid(pid, status_t, 0);
	return (0);
}
