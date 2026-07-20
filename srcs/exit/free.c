/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:11 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 16:23:12 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_2d(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	free_all(t_game *game)
{
	int	i;

	if (game->map.grid)
		free_2d((void **)game->map.grid);
	if (game->file.file_content)
		free_2d((void **)game->file.file_content);
	i = 0;
	while (i < 4)
	{
		if (game->tex[i].path)
			free(game->tex[i].path);
		i++;
	}
	return (0);
}
