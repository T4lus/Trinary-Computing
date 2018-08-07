
##
## Made by T4lus
## Trinary Makefile
## 

NAME_ASM = bin/trasm
NAME_EMU = bin/tremu
NAME_TST = bin/trtst

SRCDIR = ./Sources/
HDDIR = ./Includes/
LIBDIR = ./Libs/

SRCS_ASM = $(wildcard ./TRASM/*.cpp)
SRCS_EMU = $(wildcard ./TREMU/*.cpp)
SRCS_TST = $(wildcard ./TRTST/*.cpp)

OBJS_ASM = $(SRCS_ASM:.cpp=.o)
OBJS_EMU = $(SRCS_EMU:.cpp=.o)
OBJS_TST = $(SRCS_TST:.cpp=.o)

CC = g++

RM = rm -f
ECHO = echo -e

CFLAGS += -std=c++11 -g
HFLAGS = -I$(HDDIR)
LDFLAGS = -L$(LIBDIR) -lpthread

all: $(NAME_ASM) $(NAME_EMU) $(NAME_TST)

%.o: %.cpp
		$(CC) $(CFLAGS) $(HFLAGS) -o $@ -c $<

$(NAME_ASM): $(OBJS_ASM)
		$(CC) $(CFLAGS) $(HFLAGS) -o $(NAME_ASM) $^ $(LDFLAGS)
		@$(ECHO) '\033[0;32m> $(NAME_ASM) Compiled Without error\033[0m'

$(NAME_EMU): $(OBJS_EMU)
		$(CC) $(CFLAGS) $(HFLAGS) -o $(NAME_EMU) $^ $(LDFLAGS)
		@$(ECHO) '\033[0;32m> $(NAME_EMU) Compiled Without error\033[0m'

$(NAME_TST): $(OBJS_TST)
		$(CC) $(CFLAGS) $(HFLAGS) -o $(NAME_TST) $^ $(LDFLAGS)
		@$(ECHO) '\033[0;32m> $(NAME_TST) Compiled Without error\033[0m'

clean:
		$(RM) $(OBJS_ASM)
		$(RM) $(OBJS_EMU)
		$(RM) $(OBJS_TST)
		@$(ECHO) '\033[0;33m> Directory cleaned\033[0m'

fclean: clean
		@$(RM) $(NAME_ASM)
		@$(RM) $(NAME_EMU)
		@$(RM) $(NAME_TST)
		@$(ECHO) '\033[0;33m> Remove executable\033[0m'

re: fclean all

SRCList:
	@$(ECHO) $(SRCS)

OBJList:
	@$(ECHO) $(OBJS)