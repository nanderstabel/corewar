/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 21:05:44 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/08 08:22:11 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define TRUE				1
# define FALSE				0
# define ERROR				FALSE

# define FT_INT_MAX			2147483647
# define FT_INT_MIN			-2147483648

# define BUFF_SIZE			512
# define FD_MAX				4864
# define CONV_CHAR_START	'B'
# define CONV_CHAR_END		121

# define FORMAT_LEFT		"%-*s"
# define FORMAT_RIGHT		"%+*s"
# define BOLD				"\x1B[1m"
# define ITALICS			"\x1B[3m"
# define UNDERLINE			"\x1B[4m"
# define INVERSE			"\x1B[7m"
# define BOLD_OFF			"\x1B[22m"
# define ITALICS_OFF		"\x1B[23m"
# define UNDERLINE_OFF		"\x1B[24m"
# define INVERSE_OFF		"\x1B[27m"
# define BLACK 				"\x1B[30m"
# define RED 				"\x1B[31m"
# define GREEN 				"\x1B[32m"
# define YELLOW 			"\x1B[33m"
# define BLUE 				"\x1B[34m"
# define MAGENTA 			"\x1B[35m"
# define CYAN 				"\x1B[36m"
# define WHITE 				"\x1B[37m"
# define EOC 				"\e[0m"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
typedef struct		s_flags
{
	unsigned int	hh			: 1;
	unsigned int	h			: 1;
	unsigned int	ll			: 1;
	unsigned int	l			: 1;
	unsigned int	lll			: 1;
	unsigned int	hsh			: 1;
	unsigned int	zr			: 1;
	unsigned int	mns			: 1;
	unsigned int	pls			: 1;
	unsigned int	spc			: 1;
	unsigned int	dt			: 1;
	unsigned int	j			: 1;
	unsigned int	z			: 1;
	unsigned int	is_cap		: 1;
	unsigned int	is_signed	: 1;
	unsigned int	pdn;
	unsigned int	prcs;
	unsigned char	conv;
	unsigned int	base;
}					t_flags;

typedef struct		s_buffer
{
	char		str[BUFF_SIZE + 1];
	ssize_t		count;
	ssize_t		idx;
	char		*sprint_buf;
	int			fd;
}					t_buffer;

typedef enum
{
	FAIL,
	SUCCESS,
}	t_bool;

typedef struct s_project	t_project;
typedef t_bool				(*t_event)(t_project *);
typedef short				t_state;
typedef t_bool				(*t_f)(t_project *, char**);

typedef struct		s_machine
{
	t_state			size;
	t_state			current_state;
	t_state			last_state;
	t_bool			transition;
}					t_machine;

typedef	struct		s_adlist
{
	void			*address;
	struct s_adlist	*next;
}					t_adlist;

typedef struct		s_elem
{
	size_t			index;
	char			*name;
	size_t			hash;
	t_adlist		*body_content;
	t_list			*misc;
	void			*content;
}					t_elem;

typedef struct		s_hash_table
{
	char			*title;
	char			*format;
	t_list			*header_format;
	t_list			*header_content;
	t_list			*body_format;
	t_adlist		*width;
	size_t			size;
	char			mounted;
	t_elem			**elem;
}					t_hash_table;

typedef void		(*t_conversion_table[CONV_CHAR_END - CONV_CHAR_START])
					(va_list ap, t_buffer *buf, t_flags *flags);

long long int		ft_atoi(const char *s);
char				*ft_itoa(long long int n);
char				*ft_itoa_base_unsgnd(unsigned long long int n, int base,
					int is_cap, unsigned int len);

unsigned int		ft_nbrlen_unsigned(long long int nbr, int base);

void				ft_bzero(void *s, size_t n);

void				ft_swap_ptr(void **ptr1, void **ptr2);

int					ft_isint(char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

void				ft_lstadd(t_list **alst, t_list *item);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd_back(t_list **alst, t_list *item);
void				ft_lstfold(t_list **alst, t_list *start, t_list *end);
void				ft_lstadd_behind(t_list **alst, t_list *node,
					t_list *new_nd);
void				ft_lstadd_before(t_list **alst, t_list *node,
					t_list *new_nd);
size_t				ft_lstcount(t_list *lst);

void				ft_delete(void *ptr, size_t size);
t_list				*ft_lstnew_ptr(void const *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memdup(void *ptr, size_t size);

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl(const char *s);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putstr(const char *s);
void				ft_putstr_fd(const char *s, int fd);
ssize_t				ft_putnstr_fd(const char *str, size_t len, int fd);

char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
void				ft_strarrdel(char ***arr);
char				*ft_strdup(const char *s);
int					ft_strequ(const char *s1, const char *s2);
void				ft_striter(char *s, void(*f)(char*));
void				ft_striteri(char *s, void(*f)(unsigned int, char*));
char				*ft_strjoin(const char *s1, const char *s2);
size_t				ft_strlcat(char *s1, const char *s2, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmap(const char *s, char(*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *hay, const char *needle, size_t n);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(const char *s, char c);
char				*ft_strstr(const char *hay, const char *needle);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s);
char				*ft_strrev(char *s);

long long int		ft_absolute(long long int nbr);
unsigned int		ft_absolute_doublelen(long double ld, unsigned int prcs);
unsigned int		ft_absolute_nbrlen(long long int nbr, int base);
int					ft_power(int base, unsigned int exp);
double				ft_double_power(double base, int exp);
long double			ft_ldouble_power(long double base, int exp);

int					get_next_line(const int fd, char **line);

int					ft_printf(const char *format, ...);
int					ft_dprintf(const int fd, const char *format, ...);

void				buff_push(t_buffer *buf, char *str, size_t n);
void				buff_filler(t_buffer *buf, char c, unsigned int n);
void				buff_print_dump(t_buffer *buf);
char				*save_wildcard(va_list ap, char *pos, t_flags *flags);
char				*save_flags(va_list ap, char *pos, t_flags *flags);
void				format_int_unsgnd(long long unsigned d, t_flags *flags,
					t_buffer *buf);
void				format_int(long long d, t_flags *flags, t_buffer *buf);
void				print_number_sign(int is_positive, t_flags *flags,
					t_buffer *buf);
void				format_prepend(int is_positive, unsigned int nbrlen,
					t_flags *flags, t_buffer *buf);
void				format_append(unsigned int nbrlen, t_flags *flags,
					t_buffer *buf);
int					ft_dprintf(const int fd, const char *format, ...);
long double			rounder(int precision);
void				ftobuf(long double f, unsigned int prcs, t_buffer *buf);
void				longftobuf(long double ldb, unsigned int prcs,
					unsigned int len, t_buffer *buf);
void				absolute_itobuf(long long nb, unsigned int base,
					t_buffer *buf, int is_cap);
void				unsigned_itobuf(long long unsigned nb, unsigned int base,
					t_buffer *buf, int is_cap);
void				launch_double(va_list ap, t_buffer *buf, t_flags *flags);
void				launch_int10(va_list ap, t_buffer *buf, t_flags *flags);
void				launch_int10_unsgnd(va_list ap, t_buffer *buf,
					t_flags *flags);
void				launch_int8(va_list ap, t_buffer *buf, t_flags *flags);
void				launch_int16(va_list ap, t_buffer *buf, t_flags *flags);
void				launch_int2(va_list ap, t_buffer *buf, t_flags *flags);
void				launch_n(va_list ap, t_buffer *buf, t_flags *flags);
void				launch_c(va_list ap, t_buffer *buf, t_flags *flags);
void				launch_s(va_list ap, t_buffer *buf, t_flags *flags);
void				handler_sc(char *s, t_buffer *buf, t_flags *flags,
					char is_char);
void				handle_char(char c, t_buffer *buf, t_flags *flags);

t_bool				install_machine(t_machine **machine, t_state end);
void				run_machine(t_machine *machine, t_project *project, \
					t_state g_transitions[][2], t_event g_events[]);
t_bool				uninstall_machine(t_machine **machine);
void				ft_freezero(void *mem, size_t size);
void				ft_free_hash_table(t_hash_table **table, \
					void (*free_cont)(void *));
t_hash_table		*ft_malloc_hash_table(size_t size, char *title, \
					char *format);
size_t				ft_hash(char *key);
t_elem				*ft_hash_table_add(t_hash_table *hash_table, char *key, \
					void *content);
void				*ft_hash_table_append(t_hash_table *table, \
					void *(*columns)(t_hash_table *table));
void				*ft_hash_table_drop(t_hash_table *table, size_t cutoff);
t_elem				*ft_hash_table_get(t_hash_table *hash_table, char *key);
void				*ft_hash_table_print(t_hash_table *table, \
					void *(*columns)(t_hash_table *table));
void				*ft_hash_table_update(t_hash_table *table, \
					void *(*columns)(t_hash_table *table));
void				*ft_hash_table_naive_resize(t_hash_table *table, \
					size_t add);
void				ft_puttbl(t_hash_table *table);
void				ft_addr_lstadd(t_adlist **alst, t_adlist *newlst);
void				ft_addr_lstapp(t_adlist **alst, t_adlist *newlst);
void				ft_addr_lstdel(t_adlist **alst);
void				ft_addr_lstdelone(t_adlist **alst);
void				ft_addr_lstiter(t_adlist *lst, void (*f)(t_adlist *elem));
t_adlist			*ft_addr_lstnew(void *address);
t_adlist			*ft_addr_lstrev(t_adlist *alst);
void				ft_addr_lstsrt(t_adlist **alst, \
					int (*method)(void *, void *));
char				*ft_itoa_base(unsigned long long value, int base);
size_t				ft_ndigits(long long nbr);
int					ft_strequ_wspace_delim(const char *s1, const char *s2);
int					ft_nchar(const char *str, int c);
char				*ft_strndup(const char *src, size_t len);
t_list				*ft_list_last_elem(t_list *head);
int					get_next_endline(const int fd, char **line);
char				*ft_strrev(char *str);
void				*ft_memrev(void *src, size_t len);
char				*ft_catprintf(char *old_str, const char *format, ...);

#endif
