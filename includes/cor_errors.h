/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_errors.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 18:15:55 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/26 16:59:16 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COR_ERRORS_H
# define COR_ERRORS_H

# define USAGE				"Usage: ./corewar [-d N -n N | -v ] <champion1.cor> <...>\n\t-d N\t\t: Dumps memory after N cycles then exits\n"
# define INV_OPT			"invalid option\n"
# define INV_OPT_N			"-n option invalid\n"
# define FILE_INV_MAGIC		"invalid magic\n"
# define FILE_MIS_COR		"invalid file (missing .cor extension)\n"
# define FILE_NOT_EXIST		"file does not exist\n"
# define FILE_TOO_BIG		"file too big\n"
# define FILE_TOO_SMALL		"file too small\n"
# define FILE_INV_FORMAT	"file invalid format\n"
# define FILE_MIS_TRAIL_ZER	"file no trailing zeros after name or comment\n"
# define FILE_CHAMP_TOO_BIG	"exec code too big\n"
# define TOO_MANY_CHAMPS	"amount of players > MAX_PLAYERS\n"

#endif
// "
// Usage: ./corewar [-d N -n N | -v ] <champion1.cor> <...>
// 	-d N		: Dumps memory after N cycles then exits
// 	-n N		: Defines next champion number
// 	-v			: Visualizer output mode

// "