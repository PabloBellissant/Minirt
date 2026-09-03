/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:49:11 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/19 17:55:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

typedef struct s_data	t_data;

void	write_base(t_data *data, int fd);
void	write_materials(t_data *data, int fd);
void	write_lights(t_data *data, int fd);
void	write_primitives(t_data *data, int fd);
void	write_objects(t_data *data, int fd);

#endif
