
# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
.DELETE_ON_ERROR:

# silent mode
.SILENT:

# set shell program
override SHELL := $(shell which zsh)

# set shell flags
.SHELLFLAGS := --no-rcs --no-globalrcs --errexit --no-unset -c -o pipefail



# -- C O M P I L E R  S E T T I N G S -----------------------------------------


# get compiler
GLSLC ?=

ifndef MAKECMDGOALS

# check if compiler exists
ifndef GLSLC
    $(error "glslc path not set")
else
    override RESULT := $(shell command -v $(GLSLC) 2> /dev/null)
    ifndef RESULT
        $(error "invalid glslc path")
    endif
endif

endif

# vertex shader flags
override VERT_FLAGS := -fshader-stage=vert

# fragment shader flags
override FRAG_FLAGS := -fshader-stage=frag


# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRCDIR := sources

# output directory
override OUTDIR := spirv


# -- S O U R C E S ------------------------------------------------------------

# vertex shader sources
override VERT_SRCS  := $(shell find $(SRCDIR) -type f -name '*.vert.glsl')

# fragment shader sources
override FRAG_SRCS  := $(shell find $(SRCDIR) -type f -name '*.frag.glsl')


# -- T A R G E T S ------------------------------------------------------------

# vertex shader targets
override VERT_SPIRV := $(patsubst $(SRCDIR)/%.vert.glsl, $(OUTDIR)/%.vert.spv, $(VERT_SRCS))

# fragment shader targets
override FRAG_SPIRV := $(patsubst $(SRCDIR)/%.frag.glsl, $(OUTDIR)/%.frag.spv, $(FRAG_SRCS))


# -- R U L E S ----------------------------------------------------------------

.PHONY: all clean fclean re

all: $(VERT_SPIRV) $(FRAG_SPIRV)

$(OUTDIR)/%.vert.spv: $(SRCDIR)/%.vert.glsl Makefile | $(OUTDIR)
	print -f '- %s\n' $@
	$(GLSLC) $(VERT_FLAGS) $< -o $@

$(OUTDIR)/%.frag.spv: $(SRCDIR)/%.frag.glsl Makefile | $(OUTDIR)
	print -f '- %s\n' $@
	$(GLSLC) $(FRAG_FLAGS) $< -o $@

$(OUTDIR):
	mkdir -p $@

clean:
	rm -rf $(VERT_SPIRV) $(FRAG_SPIRV) $(OUTDIR)

fclean: clean

re: fclean all


