CC 	= 	gcc-4.8
CFLAGS 	= 	-Wall -Werror -Wextra -pedantic -g

_SRC 	= 	main.c \
					signals.c \
					parse_user_input.c \
					print_error.c \
					strings/strings.c \
					strings/strings_2.c \
					strings/strings_3.c \
					strings/strings_4.c \
					utils/env.c \
					utils/utils.c \
					utils/int_utils.c \
					utils/array_utils.c \
					builtins/cd.c	\
					builtins/printenv.c \
					builtins/exit.c \
					command/command_io.c \
					command/get_exes.c \
					command/validate_commands.c \
					command/execute_command.c
SRC 	= 	$(patsubst %,$(SDIR)/%,$(_SRC))

_OBJ 	= 	$(_SRC:.c=.o)
OBJECTS 	= 	$(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS 	= 	options.h signals.h strings.h hsh.h command.h builtins.h utils.h
DEPS 	= 	$(patsubst %,$(IDIR)/%,$(_DEPS))

IDIR 	= 	./inc
SDIR 	= 	./src
ODIR 	= 	./obj
OUTPUT 	= 	hsh
#LINKS 	= 	-lm `sdl2-config --libs`

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(IDIR)

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS)
	$(CC) -o $@ $^ $(LINKS)

.PHONY : clean

clean :
	rm -f $(OUTPUT) $(OBJECTS)

re: $(OBJ)
