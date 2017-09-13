SOURCE_FILES = src/example.asm
OUTFILE = myOutput
ASM_ARGS = -elf
OBJCONV_ARGS=-fmacho32
CC_ARGS = -m32
#OBJCONV_ARGS=-fmasm

# Targets that don't actually depend on any files
.PHONY: run

# Helper function to run the app by default
run: link
	./$(OUTFILE)
# Use UASM as the assembler -- Free, Open Source
assemble: lib/io.asm $(SOURCE_FILES)
	./tools/uasm $(ASM_ARGS) lib/io.asm
	./tools/uasm $(ASM_ARGS) $(SOURCE_FILES)
	./tools/objconv $(OBJCONV_ARGS) io.o io.obj
	./tools/objconv $(OBJCONV_ARGS) example.o example.obj

# Build the framework that the book provided
framework: lib/framework.cc
	g++ -m32 -o framework.obj -c lib/framework.cc

# Using GCC to do the linking -- See rule number 1
link: assemble framework
	g++ -m32 -framework Cocoa -Wl,-no_pie -o $(OUTFILE) *.obj

clean:
	rm -f $(wildcard *.obj)
	rm -f $(wildcard *.o)
	rm -f $(OUTFILE)
