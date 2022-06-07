NAME = 		minitalk

SRCS = 		minitalk/utils.c \
			minitalk/utils_str.c
CLINET = 	minitalk/client.c
SERVER = 	minitalk/server.c
HEADER = 	minitalk/minitalk.h

SRCS_BONUS = 	minitalk_bonus/utils_bonus.c \
				minitalk_bonus/utils_str_bonus.c
CLINET_BONUS = 	minitalk_bonus/client_bonus.c
SERVER_BONUS = 	minitalk_bonus/server_bonus.c
HEADER_BONUS = 	minitalk_bonus/minitalk_bonus.h

OBJS = ${patsubst %.c, %.o, ${SRCS}}
CLINET_OBJ = ${patsubst %.c, %.o, ${CLINET}}
SERVER_OBJ = ${patsubst %.c, %.o, ${SERVER}}

OBJS_BONUS = ${patsubst %.c, %.o, ${SRCS_BONUS}}
CLINET_OBJ_BONUS = ${patsubst %.c, %.o, ${CLINET_BONUS}}
SERVER_OBJ_BONUS = ${patsubst %.c, %.o, ${SERVER_BONUS}}

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: client server

bonus: client_bonus server_bonus

client: ${CLINET_OBJ} ${OBJS}
	gcc ${CLINET_OBJ} ${OBJS} -o $@ -I ${HEADER}

server: ${SERVER_OBJ} ${OBJS}
	gcc ${SERVER_OBJ} ${OBJS} -o $@ -I ${HEADER}

client_bonus: ${CLINET_OBJ_BONUS} ${OBJS_BONUS}
	gcc ${CLINET_OBJ_BONUS} ${OBJS_BONUS} -o $@ -I ${HEADER_BONUS}

server_bonus: ${SERVER_OBJ_BONUS} ${OBJS_BONUS}
	gcc ${SERVER_OBJ_BONUS} ${OBJS_BONUS} -o $@ -I ${HEADER_BONUS}

%.o: %.c ${HEADER}
	gcc ${FLAGS} -c $< -o $@

clean:
	rm -f minitalk_bonus/*.o minitalk_bonus/*.g.gch minitalk/*.o minitalk/*.g.gch

fclean: clean
	rm -f client server client_bonus server_bonus

re: fclean all

.PHONY: all clean fclean re bonus