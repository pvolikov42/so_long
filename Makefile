SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = libs
INCL = includes
CC = cc
# CFLAGS = -Wall -Wextra -I $(INCL)
# CFLAGS = -Wall -Wextra -Werror -I $(INCL)
CFLAGS = -Wall -Wextra -Werror -I $(INCL)

TGT = so_long

#MODS = map_parser

# VPATH = srcs
# NAMEOBJS = ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o
# NAMEOBJS = $(addprefix ft_,$(FUNCS))
# vpath %.c $(SRC)
# vpath %.h $(INCL)
# vpath %goal test
# OBJS = $(addprefix $(SRC)/,$(NAMEOBJS))
# auto approach is probably to be replaced by manual 
SRCS = $(shell find $(SRC_DIR) -name "*.c")  
#OBJS = $(addsuffix .o,$(MODS))
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
#LIBS = $(shell find $(LIB_DIR) -maxdepth 1 -mindepth 1 -type d)
LIBS += $(LIB_DIR)/ftprintf
LIBS += $(LIB_DIR)/ft
LIBS += $(LIB_DIR)/mlx

LIB_NAMES = $(notdir $(LIBS))

CFLAGS += -I $(LIB_DIR)/ftprintf
CFLAGS += -I $(LIB_DIR)/ft
CFLAGS += -I $(LIB_DIR)/mlx
LDFLAGS += $(addprefix -L,$(LIBS)) 
LDLIBS += $(addprefix -l,$(LIB_NAMES)) 
LDLIBS += -lXext -lX11

LIBS_A = $(join $(addsuffix /,$(LIBS)),\
 $(addsuffix .a,$(addprefix lib,$(LIB_NAMES))))
 
HEADERS = $(wildcard $(INCL)/*.h)

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
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

#$(OBJS): $(@:$(OBJ_DIR)%.o=$(SRC_DIR)%.c)
#	@echo Making $@ with $<
#	mkdir -p $(dir $@)
#	@echo Doing $(CC) $(CFLAGS) -c $< -o $@ -Llibft -lft

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
#	cd libft; make
#	$(CC) $(CFLAGS) -c $@.c -o $@ $< -Llibft -lft
#	echo bulk_rule: 
	@mkdir -p $(dir $@)	
#	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)
	$(CC) $(CFLAGS) -c $< -o $@ 

# libft.a :	$(OBJS)
#	ar rcs libft.a $(OBJS)

# %.o: %.c $(INCL)/ft.h
#	$(CC) -c $(CFLAGS) -o $@ $<

# ($OBJS) : $(INCL)/ft.h
#	$(CC) -c $(CFLAGS) $< -o $@

show :
	@echo SRCS: $(SRCS)
	@echo OBJS: $(OBJS)
	@echo INCL: $(INCL)
	@echo CFLAGS: $(CFLAGS)
	@echo LDFLAGS: $(LDFLAGS)
	@echo LDLIBS: $(LDLIBS)

clean :
	rm -f *.o
	for dir in $(LIBS); do $(MAKE) -C $$dir clean; done

fclean : clean
	rm -rf $(OBJ_DIR)
	rm -f $(TGT)

re : fclean all

test: $(OBJS)
	$(CC) $(CFLAGS) -o test test.c $(OBJS) -Llibft -lft
	./test
