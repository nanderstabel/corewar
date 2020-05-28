/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_errors.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 18:15:55 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/25 18:15:55 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COR_ERRORS_H
# define COR_ERRORS_H

//TODO create error enum so exit_with_message can print the right message given
//its first param. 
//	0 -> usage
//	1 -> invalid option - general
//	2 -> invalid option - n flag
//	3 -> magic number incorrect
//	4 -> invalid playername
//	5 -> champion file does not exist
//	6 -> champion file too big
//	7 -> champion file too small
//	8 -> champion file incorrect format
//	9 -> champion program size too big

# define USAGE				"usage of corewar\n"
# define INV_OPT			"invalid options given\n"
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

// enum	e_errors
// {
// 	usage,
// 	inv_opt_general,
// 	inv_opt_n,
// 	some_other_error,
// 	inv_file_name,
// 	file_not_exist,
// 	file_too_big,
// 	file_too_small,
// 	file_incorrect_format,
// 	champ_too_big
// };

#endif
