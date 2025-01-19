/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:03:50 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/19 13:17:35 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* Header includes for the project */

# include "../../Libft/includes/ft_printf.h"
# include "../../Libft/includes/get_next_line.h"
# include "../../Libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

/* Definiton of data structure */

typedef struct s_data
{
	int		old_fd[2];
	int		curr_fd[2];
	int		fd_file;
	int		status;
	int		pid;
	int		argv_index;
	int		number_of_command;
	char	*cmd_path;
	char	**arg_cmd;
	char	*path_line;
	char	**env_var;
}	t_data;

/* Function called in the project */

void	free_all(t_data *data);
void	error(t_data *data);
void	construct_commands(t_data *data, char **argv);
void	find_envp(t_data *data, char **envp);
void	execute_first_command(char **argv, t_data *data);
void	execute_last_command(char **argv, t_data *data);
void	execute_commands(t_data *data);

#endif