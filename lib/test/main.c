/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:17:42 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/17 23:06:48 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "font_renderer.h"

int		init_ttf(const char *path, t_ttf_font **ptr);
void	start_mainloop(t_rast_env *env, t_ttf_font *font);
void	free_ttf(t_ttf_font *font);

int	main(int argc, char **argv)
{
	t_ttf_font	*font;
	t_rast_env	env;
	int			ret;

	font = NULL;
	if (argc == 2)
	{
		printf("'%s'\n", argv[1]);
		ret = init_ttf(argv[1], &font);
		if (ret)
			return (ret);
		ft_bzero(&env, sizeof(t_rast_env));
		start_mainloop(&env, font);
		free_ttf(font);
	}
	else
		return (error(ERR_ARG_NUM, ": %d", argc - 1));
	return (0);
}
