#
# Copyright (c) 2016 Mieszko Mazurek
#

PROJ	= minisumo
SRC	= ${shell find . -name '*.c' -or -name '*.cxx'}
OBJ	= ${SRC:./%=obj/%.o}
DEP	= ${OBJ:%.o=%.d}

ELF	= ${PROJ}.elf
HEX	= ${PROJ}.hex

CC	= avr-gcc -c
LD	= avr-gcc
CFLAGS	= -mmcu=atmega32 -DF_CPU=14745600UL -Ilib/inc/core
LDFLAGS	= -mmcu=atmega32 lib/libavrmeos.a -Tldscripts/avr5.xn

elf: ${ELF}

clean:
	rm -fr obj/ ${ELF} ${HEX}

flash: ${HEX}
	sudo avrdude -c usbasp -p m32 -U flash:w:$<

${HEX}: ${ELF}
	avr-objcopy -j .text -j .data -O ihex $< $@

${ELF}: ${OBJ}
	${LD} $^ -o $@ ${LDFLAGS}

obj/%.c.o: %.c
	@mkdir -p ${dir $@}
	${CC} -MMD $< -o $@ ${CFLAGS}

-include ${DEP}
