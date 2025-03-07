#Colors
GREEN				= \033[0;92m
RED					= \033[0;91m
DEF_COLOR			= \033[0;39m

SRCS =	client.c\
		server.c

# Object files
OBJS = ${SRCS:.c=.o}

# Target binary name
NAME = minitalk
CC = cc
CFLAGS = -Wall -Werror -Wextra -I -g -fsanitize=address
RM = rm -f

HEADER = minitalk.h

CLIENT = client
SERVER = server

LIBFTDIR = libft/
LIBFT_LIB = $(LIBFTDIR)/libft.a

# Build everything
all: make_libft $(CLIENT) $(SERVER)
	@echo "$(GREEN)minitalk compilado con éxito.$(DEF_COLOR)"

make_libft:	
	@make -C $(LIBFTDIR)
	@echo "$(GREEN)Libft Done$(DEF_COLOR)"

$(CLIENT): client.o $(LIBFT_LIB)
	@${CC} ${CFLAGS} client.o -o ${CLIENT} -L$(LIBFTDIR) -lft

$(SERVER): server.o $(LIBFT_LIB)
	@${CC} ${CFLAGS} server.o -o ${SERVER} -L$(LIBFTDIR) -lft

# Compile .c to .o
%.o: %.c $(HEADER)
	@${CC} ${CFLAGS} -c $< -o $@

# Build the program
$(NAME): $(OBJS) Makefile $(HEADER)
	@${CC} ${CFLAGS} $(OBJS) -o ${NAME}

# Clean objects
clean:
	@${RM} ${OBJS}
	@cd $(LIBFTDIR) && $(MAKE) clean
	@echo "$(RED)Objetos eliminados.$(DEF_COLOR)"

# Clean all files
fclean: clean
	@${RM} ${CLIENT} ${SERVER}
	@cd $(LIBFTDIR) && $(MAKE) fclean
	@echo "$(RED)Ejecutables eliminados.$(DEF_COLOR)"

# Rebuild project
re: fclean all
	@echo "$(GREEN)Proyecto reconstruido.$(DEF_COLOR)"

.PHONY: all clean fclean re
