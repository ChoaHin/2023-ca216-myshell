SRCDIR := src
SRCS := $(wildcard $(SRCDIR)/*.c)

myshell: myshell.c myshell.h $(SRCS)
	gcc -Wall myshell.c $(SRCS) -o myshell
