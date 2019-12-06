# Target Library
CC := g++


ifneq ($(V), 1)
Q = @
endif


runpriv: runpriv.o
	$(Q)$(CC) runpriv.o -o runpriv

runpriv.o: runpriv.cpp
	$(Q)$(CC) -c runpriv.cpp

clean:
	@echo "CLEAN"
	$(Q)rm -rf *.o runpriv
