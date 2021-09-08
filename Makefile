CC=cc
CFLAGS=-Wall -Wextra -std=gnu89 $(OPT) -fpie
LDFLAGS=
SRC=$(wildcard src/*.c)
INC=$(wildcard src/*.h)
OBJ=$(patsubst src/%.c,%.o,$(SRC))

.PHONY: release
release: stc
release: OPT:=-O3

.PHONY: debug
debug: stc
debug: OPT:=-O0 -ggdb3

.PHONY: sanitize
sanitize: stc
sanitize: OPT:=-O0 -ggdb3 \
	-fsanitize=address \
	-fsanitize=leak \
	-fsanitize=undefined

.PHONY: install
install: release
	cp stc ~/bin/.

stc: $(OBJ)
	$(CC) -o stc $(CFLAGS) $(OBJ) $(LDFLAGS)

%.o: src/%.c $(INC) $(SRC)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f *.o
	rm -f stc
