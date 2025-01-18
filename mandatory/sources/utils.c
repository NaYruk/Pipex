/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:23 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/01/18 15:37:45 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all_2(t_data *data)
{
	int	i;

	i = -1;
	if (data->arg_cmd)
	{
		while (data->arg_cmd[++i] != NULL)
			free(data->arg_cmd[i]);
		free(data->arg_cmd);
	}
	i = -1;
	if (data->env_var)
	{
		while (data->env_var[++i] != NULL)
			free(data->env_var[i]);
		free(data->env_var);
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
	if (data->cmd_path)
		free(data->cmd_path);
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
