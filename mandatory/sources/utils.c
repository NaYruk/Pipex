/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:23 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/01/16 19:00:01 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all_2(t_data *data)
{
	int	i;

	i = -1;
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
	i = -1;
	if (data->envp)
	{
		while (data->envp[++i] != NULL)
			free(data->envp[i]);
		free(data->envp);
	}
	if (data)
		free(data);
}

/*
	Function for free all data malloc in the program
*/

void	free_all(t_data *data)
{
	if (data->path_line)
		free(data->path_line);
	if (data->cmd1_path)
		free(data->cmd1_path);
	if (data->cmd2_path)
		free(data->cmd2_path);
	free_all_2(data);
}

/*
	Function for report an error and leave the program.
*/

void	error(t_data *data)
{
	perror("ERROR");
	free_all(data);
	exit(EXIT_FAILURE);
}
