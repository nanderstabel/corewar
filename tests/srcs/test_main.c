/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 17:49:58 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/17 13:30:35 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include "asm.h"
#include<stdio.h> 
#include <fcntl.h> 
#define	ADD_TOKEN(y_axis, type, str)	ft_lstadd_back(&as->tmp, ft_lstnew_ptr((const void *)new_token(as, (y_axis), (type), ft_strdup((str))), 0))
#define TOKEN							((t_token*)temp->content)
#define NEXT_LIST						temp = temp->next;
#define REG_ENC							4
#define DIR_ENC							8
#define IND_ENC							12


static int		setup(t_project **as)
{
	t_list		*temp;
	char		enc;

	enc = 0;
	(*as)->fd = open("./valid_asm/zork.s", O_RDONLY);
	if ((*as)->fd == -1)
	{
		ft_printf("error fd\n");
		return (0);
	}
	if (!analyze_lexicon(*as))
	{
		ft_printf("error lex\n");
		return (0);
	}
	if (!analyze_syntax(*as))
	{
		ft_printf("error syn\n");
		return (0);
	}	
	if (!analyze_instructions(*as))
	{
		ft_printf("error ins\n");
		return (0);
	}
	if (!analyze_parameters(*as))
	{
		ft_printf("error ins\n");
		return (0);
	}
	temp = (*as)->token_list;
	while (TOKEN->opcode != 11)
		NEXT_LIST;
	// ft_printf("encoding byte of token %s = %i\n", TOKEN->literal_str, TOKEN->encoding);
	enc |= ((char)ft_power(2, 6));
	enc |= ((char)ft_power(2, 5));
	enc |= ((char)ft_power(2, 3));
	TOKEN->encoding = enc;
	// ft_printf("encoding byte of token %s = %i\n", TOKEN->literal_str, TOKEN->encoding);
	enc = 0;
	while (TOKEN->opcode != 6)
		NEXT_LIST;
	// ft_printf("encoding byte of token %s = %i\n", TOKEN->literal_str, TOKEN->encoding);
	enc |= ((char)ft_power(2, 6));
	enc |= ((char)ft_power(2, 5));
	enc |= ((char)ft_power(2, 2));
	TOKEN->encoding = enc;
	// ft_printf("encoding byte of token %s = %i\n", TOKEN->literal_str, TOKEN->encoding);

	return(1);
}

// static void		get_type_encoding()
// {

// 	char			enc;
// 	char			test;


// 	enc = 0;


// 	enc |= ((char)ft_power(2, 6));
// 	enc |= ((char)ft_power(2, 5));
// 	enc |= ((char)ft_power(2, 3));
// 	enc |= ((char)ft_power(2, 2));
// 	ft_printf("encoding byte origin = %i\n", enc);
// 	test = (enc >> 6);
// 	ft_printf("test [%d]\n", test);
// 	enc ^= (test << 6);
// 	ft_printf("encoding byte = %i\n", enc);
// 	test = (enc >> 4);
// 	ft_printf("test [%d]\n", test);
// 	enc ^= (test << 4);
// 	ft_printf("encoding byte = %i\n", enc);
// 	test = (enc >> 2);
// 	ft_printf("test [%d]\n", test);
// 	enc ^= (test << 2);
// 	ft_printf("encoding byte = %i\n", enc);
// }

static void			write_str_to_buf2(t_project *as, char *n, char type)
{
	long long	number;
	long long	*ptr;
	char		*str;
	int		sz;
	int fd;


	fd = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);

	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	number = ft_atoi(n);
	ptr = (long long*)ft_memalloc(sizeof(long long));
	*ptr = number;
	str = ft_strnew(type);
	ft_memcpy((void*)str, (const void*)ptr, type);
	str = ft_memrev(str, type);
	ft_printf("char %d\n type %d\n", (char)str[0], (int)type);

	
	sz = write(fd, str, type);
	ft_printf("fd = %d - sz = %d\n", fd, sz);

// 	// int num;
// 	// num = 5;
}

int		main(void)
{


	t_project		*as;
	int				index;
	t_list			*temp;

	index = 0;
	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE));
	as->index = 0;

	if (!setup(&as))
		return (-1);
	else
		// ft_printf("setup SUCCESS\n");
	temp = as->token_list;
	while (index < 4)
	{
		NEXT_LIST;
		index++;
	}
	NEXT_LIST;
	// ft_printf("%s", TOKEN->literal_str);
	TOKEN->literal_str++;
	// int fd = open("./test.cor", O_CREAT | O_RDWR, 00700);
	// long long test = ft_atoi("256");
	// long long *ptr = (long long*)ft_memalloc(sizeof(long long));
	// char *str;
	// *ptr = test;
	// str = (char*)ft_memalloc(sizeof(8));
	// ft_memcpy((void*)str, (const void*)ptr, 2);
	// str = ft_memrev(str, 2);
	write_str_to_buf2(as, "1", 8);


	

	// int		sz;
	// sz = write(fd, str, 2);
	// ft_printf("fd = %d - sz = %d\n", fd, sz);


	
	
	
	
	return (0);
}