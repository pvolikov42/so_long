SRC = src
INCL = -I includes 
CC = cc
# CFLAGS = -Wall -Wextra -I $(INCL)
# CFLAGS = -Wall -Wextra -Werror -I $(INCL)
MODS = ft_printf \
		ft_conversion \
		ft_printf_utils
# VPATH = srcs
# NAMEOBJS = ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o
# NAMEOBJS = $(addprefix ft_,$(FUNCS))
NAMEOBJS = $(MODS)
# vpath %.c $(SRC)
# vpath %.h $(INCL)
# vpath %goal test
# OBJS = $(addprefix $(SRC)/,$(NAMEOBJS))
OBJS = $(addsuffix .o,$(NAMEOBJS))
TGTLIB = libftprintf.a
LIBFT_DIR = ../libft
LIBFT_A = libft.a
LFLAGS += -L$(LIBFT_DIR) -lft
INCL += -I $(LIBFT_DIR)

CFLAGS = -Wall -Wextra -Werror $(INCL)

.PHONY:	all clean fclean re test
all :	$(TGTLIB)

$(TGTLIB) :	$(OBJS) $(LIBFT_DIR)/$(LIBFT_A)
#	ar rcs $(TGTLIB) $(OBJS) 
#	cp libft/libft.a $(TGTLIB)
	ar rcs $(TGTLIB) $(OBJS)

%.o: %.c *.h
	$(CC) -c $(CFLAGS) -o $@ $<

#%.o: libft/libft.a

$(LIBFT_DIR)/$(LIBFT_A):
	cd $(LIBFT_DIR); make $(LIBFT_A)

#	$(CC) $(CFLAGS) ft_printf.c -c -o $@ 

# libft.a :	$(OBJS)
#	ar rcs libft.a $(OBJS)

# %.o: %.c $(INCL)/ft.h
#	$(CC) -c $(CFLAGS) -o $@ $<

# ($OBJS) : $(INCL)/ft.h
# $(CC) -c $(CFLAGS) $< -o $@

clean :
#	cd libft; make clean
	rm -f $(OBJS)

fclean : clean
	rm -f $(TGTLIB)
	rm -f a.out

re : fclean all

test: $(TGTLIB)
#	$(CC) $(CFLAGS) main.c -o runtest -L. -Llibft -lftprintf -lft
	$(CC) $(CFLAGS) test.c -o runtest -L. -lftprintf $(LFLAGS)
	./runtest
#	cd dir; touch tt
#	touch ttt
