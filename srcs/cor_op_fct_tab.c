/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_fct_tab.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 16:26:15 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/20 16:26:15 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op_fct    op_fct_tab[18] = 
{
	{0, 0},
	{(*op_live), &(op_tab[0])},
	{(*op_ld), &(op_tab[1])},
	{(*op_st), &(op_tab[2])},
	{(*op_add), &(op_tab[3])},
	{(*op_sub), &(op_tab[4])},
	{(*op_and), &(op_tab[5])},
	{(*op_or), &(op_tab[6])},
	{(*op_xor), &(op_tab[7])},
	{(*op_zjmp), &(op_tab[8])},
	{(*op_ldi), &(op_tab[9])},
	{(*op_sti), &(op_tab[10])},
	{(*op_fork), &(op_tab[11])},
	{(*op_lld), &(op_tab[12])},
	{(*op_lldi), &(op_tab[13])},
	{(*op_lfork), &(op_tab[14])},
	{(*op_aff), &(op_tab[15])},
};
