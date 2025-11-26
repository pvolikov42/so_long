SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = libs
INCL = includes
CC = cc
# CFLAGS = -Wall -Wextra -I $(INCL)
# CFLAGS = -Wall -Wextra -Werror -I $(INCL)
CFLAGS = -Wall -Wextra -Werror -I $(INCL)

TGT = so_long

# MODS = push_swap 
MODS = map_parser

# VPATH = srcs
# NAMEOBJS = ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o
# NAMEOBJS = $(addprefix ft_,$(FUNCS))
# vpath %.c $(SRC)
# vpath %.h $(INCL)
# vpath %goal test
# OBJS = $(addprefix $(SRC)/,$(NAMEOBJS))
SRCS = $(shell find $(SRC_DIR) -name "*.c")
#OBJS = $(addsuffix .o,$(MODS))
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
#LIBS = $(shell find $(LIB_DIR) -maxdepth 1 -mindepth 1 -type d)
LIBS = $(LIB_DIR)/ft
LIBS += $(LIB_DIR)/ftprintf
LIBS += $(LIB_DIR)/mlx

# LIBFT_DIR = libft
# LIBFT_A = $(LIBFT_DIR)/libft.a
# FT_PRINTF_DIR = ft_printf
# FT_PRINTF_A = $(FT_PRINTF_DIR)/ft_printf.a
LFLAGS += -L$(LIB_DIR) -l

LIB_NAMES = $(notdir $(LIBS))
LIBS_A = $(join $(addsuffix /,$(LIBS)),\
$(addsuffix .a,$(addprefix lib,$(LIB_NAMES))))

.PHONY:	all clean fclean re test
all :	$(TGT)

check: 
	@echo LIBS = $(LIBS)
	@echo LIBS_A = $(LIBS_A)

$(LIBS_A) : 
	$(MAKE) -C $(dir $@)

# $(TGT): $(OBJS) $(LIBS_A)
$(TGT): $(LIBS_A) $(OBJS)
#	$(CC) $(CFLAGS) -c $@.c -o $@ $< -Llibft -lft
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)
	
%.o: %.c 
#	cd libft; make
#	$(CC) $(CFLAGS) -c $@.c -o $@ $< -Llibft -lft
	$(CC) $(CFLAGS) -c $< -Llibft -lft

# libft.a :	$(OBJS)
#	ar rcs libft.a $(OBJS)

# %.o: %.c $(INCL)/ft.h
#	$(CC) -c $(CFLAGS) -o $@ $<

# ($OBJS) : $(INCL)/ft.h
#	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -f $(TGT)

fclean : clean
	rm -f *.o

re : fclean all

test: $(OBJS)
	$(CC) $(CFLAGS) -o test test.c $(OBJS) -Llibft -lft
	./test
