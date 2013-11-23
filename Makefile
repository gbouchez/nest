PROJDIRS := src
BINDIR   := bin

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.s")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.c")

OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) 
ASMOBJFILES := $(patsubst %.s,%.oa,$(ASMFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

BINARY   := $(BINDIR)/nest.bin
ISOFILE  := nest.iso
LDFILE   := $(shell find $(PROJDIRS) -type f -name "*.ld")

.PHONY:     all iso clean

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wconversion -Wstrict-prototypes

GCCBIN   := i586-elf-gcc
ASBIN    := i586-elf-as
LDFLAGS  := -T $(LDFILE) -o $(BINARY) -ffreestanding -O2 -nostdlib -lgcc
CFLAGS   := -g -std=gnu99 -ffreestanding -O2 $(WARNINGS)

all:		$(BINARY)

$(BINARY):	$(OBJFILES) $(ASMOBJFILES)
		@$(GCCBIN) $(LDFLAGS) $(ASMOBJFILES) $(OBJFILES)

%.oa:		%.s Makefile
		$(ASBIN) $< -o $@

%.o:		%.c Makefile
		@$(GCCBIN) $(CFLAGS) -MMD -MP -c $< -o $@
		
$(ISOFILE):	$(BINARY)
		@cp $(BINARY) isodir/boot/nest.bin
		@grub-mkrescue -o nest.iso isodir
		
iso:		$(ISOFILE)

clean:
		@find -name *.o -delete
		@find -name *.d -delete
		@find -name *.oa -delete
