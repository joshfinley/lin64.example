AS=yasm 						# assembler
ASFLAGS=-f elf64 	 			# assembler flags
LD=ld 							# linker
LDFLAGS=-m elf_x86_64 -z noseparate-code			
								# linker flags
SOURCES=$(wildcard ./src/*.asm) # sources
OBJECTS=$(SOURCES:%.asm=%.o) 	# object files
EXECUTABLE=test 				# program name

# check version
all: $(SOURCES) $(EXECUTABLE)
	
# assemble program
$(OBJECTS): $(SOURCES)
	@$(AS) $(ASFLAGS) $(SOURCES) -o $@
	@echo "assemble $<"

# create executable
$(EXECUTABLE): $(OBJECTS)
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@.bin
	@echo "link $<"

# clean folder
clean:
	rm -rf src/*o *.bin