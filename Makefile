################################################################################
#                               BOLD COLORS                                    #
################################################################################

END = \033[m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CIAN = \033[36m

################################################################################
#  FONT                                                                        #
################################################################################

LIGTH = \033[1m
DARK = \033[2m
ITALIC = \033[3m

################################################################################
#                               VARIABLES                                      #
################################################################################

VALID_HOST1 := x86_64
VALID_HOST2 := x86_64_Linux
ifeq ($(filter $(HOSTTYPE),$(VALID_HOST1) $(VALID_HOST2)),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
$(info [WARNING] HOSTTYPE is missing or invalid. Using detected value: $(HOSTTYPE))
endif
LIBNAME = libft_malloc_$(HOSTTYPE).so
SYMLINK = libft_malloc.so

RMV = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
LDFLAGS = -shared #-pthread
TOTAL_FILES = $(words $(SOURCES))

DIRECTORY_OBJ = .obj
DIRECTORY_DEP = .dep
DIRECTORY_SRC = src

SUB_DIRECTORIES = free malloc realloc
SOURCES = \
	free/free.c \
	malloc/malloc.c \
	realloc/realloc.c

INCLUDES = $(addprefix -I, ./include)
OBJECTS = $(addprefix $(DIRECTORY_OBJ)/, $(SOURCES:.c=.o))
DEPENDENCIES = $(addprefix $(DIRECTORY_DEP)/, $(SOURCES:.c=.d))
DIRS_TO_CREATE = $(DIRECTORY_OBJ) $(DIRECTORY_DEP)

################################################################################
#                               MAKE RULES                                     #
################################################################################

all: dir $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)
	echo "\n✅ ==== $(BLUE)$(LIGTH)Project $(NAME) compiled!$(END) ==== ✅"

$(DIRECTORY_OBJ)/%.o:$(DIRECTORY_SRC)/%.c Makefile
	@printf "  $(LIGTH)Compiling $(BLUE)$<$(END)      "
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MF $(DIRECTORY_DEP)/$*.d -c $< -o $@
	@$(call progress,$<)

symlink: $(LIBNAME)
	ln -sf $(LIBNAME) $(SYMLINK)

dir:
	@for DIR in $(DIRS_TO_CREATE); do \
		if [ ! -d $$DIR ]; then \
			mkdir -p $$DIR; \
			$(foreach SUB, $(SUB_DIRECTORIES), mkdir -p $$DIR/$(SUB);) \
			printf "$(BLUE)$(LIGTH)Creating directory:$(END) $$DIR\n"; \
		else \
			printf "$(BLUE)$(LIGTH)Directory already exists:$(END) $$DIR\n"; \
		fi \
	done

define progress
	@$(eval COMPILED_FILES=$(shell expr $(COMPILED_FILES) + 1))
	@bash -c 'PROG_BAR_WIDTH=50; \
	PROGRESS=$$(($(COMPILED_FILES) * $$PROG_BAR_WIDTH / $(TOTAL_FILES))); \
	EMPTY=$$(($$PROG_BAR_WIDTH - $$PROGRESS)); \
	PROGRESS=$$((PROGRESS < 0 ? 0 : PROGRESS)); \
	EMPTY=$$((EMPTY < 0 ? 0 : EMPTY)); \
	printf "\r$(ligth)[$(GREEN)"; \
	for ((i = 0; i < $$PROGRESS; i++)); do echo -n "█"; done; \
	for ((i = 0; i < $$EMPTY; i++)); do echo -n " "; done; \
	printf "$(END)$(ligth)] "; \
	printf "%d%%$(END)" $$((100 * $(COMPILED_FILES) / $(TOTAL_FILES)));'
endef

clean:
	@for DIR in $(DIRS_TO_CREATE); do \
		if [ -d $$DIR ]; then \
			$(RMV) $$DIR; \
			printf "$(BLUE)$(LIGTH)Directory$(END) $$DIR $(BLUE)$(LIGTH)removed$(END)\n"; \
		else \
			printf "$(LIGTH)The directory does not exist:$(END) $$DIR\n"; \
		fi \
	done
	echo "✅ ==== $(PURPLE)$(LIGTH)$(NAME) object files cleaned!$(END) ==== ✅"

fclean: clean
	@$(RMV) $(LIBNAME)
	echo "✅ ==== $(PURPLE)$(LIGTH)$(NAME) executable files and name cleaned!$(END) ==== ✅"

-include $(DEPENDENCIES)
re: fclean all
.PHONY: all symlink dir progress clean fclean
.SILENT: