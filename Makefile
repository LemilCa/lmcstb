CC = gcc
FILE = main
VERSION = -std=c99
LIBS = 
WARNINGS = -Wall -Wextra -Wpedantic -Werror
WARNINGS_REMOVE = # -Wno-error=type-limits -Wno-type-limits


.PHONY: valgrind cpl Cpl run Run val Val cln Cln


all: Cpl Run Cln

valgrind: Cpl Val Cln


cpl:
	$(CC) $(VERSION) -o $(FILE).exe $(FILE).c $(LIBS) $(WARNINGS) $(WARNINGS_REMOVE)
Cpl:
	@$(CC) $(VERSION) -o $(FILE).exe $(FILE).c $(LIBS) $(WARNINGS) $(WARNINGS_REMOVE)


run:
	./$(FILE).exe
Run:
	@./$(FILE).exe

val:
	valgrind ./$(FILE).exe
Val:
	@valgrind ./$(FILE).exe

cln:
	rm -f $(FILE).exe
Cln:
	@rm -f $(FILE).exe