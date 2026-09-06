/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:58:54 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 00:05:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

static inline void	print_header_start(void)
{
	printf("\n"C_BORDER
		"╔═════════════════════════════════════════"
		"══════════════════════════════════════════╗"
		C_RESET"\n");
}

static inline void	print_header_end(void)
{
	printf(C_BORDER
		"╚═════════════════════════════════════════"
		"══════════════════════════════════════════╝"
		C_RESET"\n\n");
}

static inline void	print_header_decorator(void)
{
	printf(C_BORDER"║"C_RESET
		"  ░░▒▒▓▓██                               "
		"                                ██▓▓▒▒░░  "
		C_BORDER"║"C_RESET"\n");
}

static inline void	print_header_text(char *title)
{
	printf(C_BORDER
		"║"
		C_RESET
		"     "
		C_TITLE
		"%s"
		C_RESET
		"        "
		C_BORDER
		"║"
		C_RESET"\n", title);
}

void	print_bvh_debug_header(void)
{
	print_header_start();
	print_header_decorator();
	print_header_text(
		"╔╗ ╔═╗╦ ╦╔╗╔╔╦╗╦╔╗╔╔═╗  ╦  ╦╔═╗╦  ╦"
		" ╦╔╦╗╔═╗  ╦ ╦╦╔═╗╦═╗╔═╗╦═╗╔═╗╦ ╦╦ ╦"
		);
	print_header_text(
		"╠╩╗║ ║║ ║║║║ ║║║║║║║ ╦  ╚╗╔╝║ ║║  ║"
		" ║║║║║╣   ╠═╣║║╣ ╠╦╝╠═╣╠╦╝║  ╠═╣╚╦╝"
		);
	print_header_text(
		"╚═╝╚═╝╚═╝╝╚╝═╩╝╩╝╚╝╚═╝   ╚╝ ╚═╝╩═╝╚"
		"═╝╩ ╩╚═╝  ╩ ╩╩╚═╝╩╚═╩ ╩╩╚═╚═╝╩ ╩ ╩ "
		);
	print_header_decorator();
	print_header_end();
}
