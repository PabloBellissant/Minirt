# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    includes.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 13:46:13 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:32:32 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCDIR			= include \
				  include/bvh \
				  include/bvh/shape \
				  include/bvh/splitting \
				  include/ui \
				  include/ui/logic \
				  include/ui/edit_pannel
INCDIRS_MINIRT	:= $(INCDIR)
