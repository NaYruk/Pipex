/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:03:50 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/16 17:38:20 by marcmilliot      ###   ########.fr       */
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
	int		fd[2];
	int		fd_file;
	int		status;
	int		pid;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**arg_cmd1;
	char	**arg_cmd2;
	char	*path_line;
	char	**envp;
}	t_data;

/* Function called in the project */

void	free_all(t_data *data);
void	error(t_data *data);
void	construct_commands(t_data *data, char **argv, char **envp);

#endif