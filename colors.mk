# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 15:57:36 by jaubry--          #+#    #+#              #
#    Updated: 2025/04/07 16:24:13 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

# Formatting
RESET		= \\033[0m
BOLD		= \\033[1m
UNDERLINE	= \\033[4m
NOUNDERLINE	= \\033[24m
NL			= \\n

# Color palette
RED			= \\033[38;5;196m
YELLOW		= \\033[38;5;220m
GREEN		= \\033[38;5;40m
CYAN		= \\033[38;5;51m
BLUE		= \\033[38;5;33m
ORANGE		= \\033[38;5;214m
PURPLE		= \\033[38;5;129m

define color
	@echo -e "$(1)$(subst %UL%,$(UNDERLINE),$(subst %NUL%,$(NOUNDERLINE),$(2)))$(RESET)"
endef
