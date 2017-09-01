CC 	= 	gcc-4.8
CFLAGS 	= 	-Wall -Werror -Wextra -pedantic -g

_SRC 	= 	main.c \
					handle_signals.c \
					utils/string_utils/strings.c \
					utils/string_utils/strings_2.c \
					utils/string_utils/strings_3.c \
					utils/string_utils/strings_4.c \
					utils/string_utils/strings_5.c \
					utils/string_utils/strings_6.c \
					utils/env_utils.c \
					utils/path_utils.c \
					utils/int_utils.c \
					utils/array_utils.c \
					shell/shell.c \
					print/print_error.c \
					print/print_prompt.c \
					command/command_io.c \
					command/command_lexer.c \
					command/get_exes.c \
					command/execute_commands.c \
					command/get_exes.c \
					command/handle_builtins.c \
					command/handle_redirections.c \
					command/builtins/cd.c	\
					command/builtins/printenv.c \
					command/builtins/setenv.c \
					command/builtins/unsetenv.c \
					command/builtins/exit.c
SRC 	= 	$(patsubst %,$(SDIR)/%,$(_SRC))

_OBJ 	= 	$(_SRC:.c=.o)
OBJECTS 	= 	$(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS 	= 	options.h signals.h string_utils.h hsh.h command.h builtins.h utils.h
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
