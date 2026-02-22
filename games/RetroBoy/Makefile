SHELL := /bin/bash

ifndef GBDK_HOME
GBDK_HOME = ../../gbdk/
endif
LCC = $(GBDK_HOME)bin/lcc

TARGETS = gb

LCCFLAGS_gb      = -Wl-yt0x19 -Wm-yC -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_pocket  = -Wl-yt0x19 -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_sms     =
LCCFLAGS_gg      =
LCCFLAGS_nes     = -Wb-min=0

LCCFLAGS += $(LCCFLAGS_$(EXT))
LCCFLAGS += -Wl-j -Wm-yoA -autobank -Wb-ext=.rel
LCCFLAGS += -Wl-j -Wl-w -Wm-yS
# LCCFLAGS += -debug      # Uncomment to enable debug output
# LCCFLAGS += -v -Wb-v    # Uncomment for verbose output

CFLAGS   = -Wf-Iinclude -Wf-MMD

# ---- Set your project name here ----
PROJECTNAME = retroboy

SRCDIR      = src
SRCPLAT     = src/$(PORT)
OBJDIR      = obj/$(EXT)
RESDIR      = res
BINDIR      = build/$(EXT)
MKDIRS      = $(OBJDIR) $(BINDIR)

BINS	    = $(OBJDIR)/$(PROJECTNAME).$(EXT)
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(SRCPLAT),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s))) $(foreach dir,$(SRCPLAT),$(notdir $(wildcard $(dir)/*.s)))
OBJS        = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

DEPS = $(OBJS:%.o=%.d)
-include $(DEPS)

all: $(TARGETS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(SRCPLAT)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(SRCPLAT)/%.s
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) $(CFLAGS) -o $(BINDIR)/$(PROJECTNAME).$(EXT) $(OBJS)

clean:
	@echo Cleaning
	@for target in $(TARGETS); do \
		$(MAKE) $$target-clean; \
	done

include Makefile.targets

ifneq ($(strip $(EXT)),)
$(info $(shell mkdir -p $(MKDIRS)))
endif
