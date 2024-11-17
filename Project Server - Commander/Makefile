CC = gcc
CFLAGS = -Wall -I./include
OBJDIR = obj
BINDIR = build
SRCDIR = src

OBJS = $(OBJDIR)/jobExecutorServer.o $(OBJDIR)/jobCommander.o $(OBJDIR)/progDelay.o
TARGETS = $(BINDIR)/jobExecutorServer $(BINDIR)/jobCommander $(BINDIR)/progDelay

all: $(TARGETS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/jobExecutorServer: $(OBJDIR)/jobExecutorServer.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR)/jobCommander: $(OBJDIR)/jobCommander.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR)/progDelay: $(OBJDIR)/progDelay.o
	$(CC) $(CFLAGS) -o $@ $^

	mkfifo /tmp/jobExecutorServer_pipe

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/* /tmp/jobExecutorServer_pipe jobExecutorServer.txt

.PHONY: all clean
