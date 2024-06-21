CC=gcc
CFLAGS=-Wall -Wextra -I./include
OBJDIR=./obj
SRCDIR=./src
BUILDDIR=./build

# Source files for each algorithm
DIJKSTRA_SRC=$(SRCDIR)/dijkstra.c $(SRCDIR)/graph.c
PRIM_SRC=$(SRCDIR)/prim.c $(SRCDIR)/graph.c
KRUSKAL_SRC=$(SRCDIR)/kruskal.c $(SRCDIR)/graph.c $(SRCDIR)/union_find.c
DIAL_SRC=$(SRCDIR)/dial.c $(SRCDIR)/graph.c
BORUVKA_SRC=$(SRCDIR)/boruvka.c $(SRCDIR)/graph.c $(SRCDIR)/union_find.c

# Object files
DIJKSTRA_OBJ=$(OBJDIR)/dijkstra.o $(OBJDIR)/graph.o
PRIM_OBJ=$(OBJDIR)/prim.o $(OBJDIR)/graph.o
KRUSKAL_OBJ=$(OBJDIR)/kruskal.o $(OBJDIR)/graph.o $(OBJDIR)/union_find.o
DIAL_OBJ=$(OBJDIR)/dial.o $(OBJDIR)/graph.o
BORUVKA_OBJ=$(OBJDIR)/boruvka.o $(OBJDIR)/graph.o $(OBJDIR)/union_find.o

# Executables
DIJKSTRA=$(BUILDDIR)/dijkstra
PRIM=$(BUILDDIR)/prim
KRUSKAL=$(BUILDDIR)/kruskal
DIAL=$(BUILDDIR)/dial
BORUVKA=$(BUILDDIR)/boruvka

all: dijkstra prim kruskal dial boruvka

# Rule to compile objects
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

dijkstra: $(DIJKSTRA_OBJ) | $(BUILDDIR)
	@echo "Compiling dijkstra..."
	$(CC) $(CFLAGS) $^ -o $(DIJKSTRA)

prim: $(PRIM_OBJ) | $(BUILDDIR)
	@echo "Compiling prim..."
	$(CC) $(CFLAGS) $^ -o $(PRIM)

kruskal: $(KRUSKAL_OBJ) | $(BUILDDIR)
	@echo "Compiling kruskal..."
	$(CC) $(CFLAGS) $^ -o $(KRUSKAL)

dial: $(DIAL_OBJ) | $(BUILDDIR)
	@echo "Compiling dial..."
	$(CC) $(CFLAGS) $^ -o $(DIAL)

boruvka: $(BORUVKA_OBJ) | $(BUILDDIR)
	@echo "Compiling boruvka..."
	$(CC) $(CFLAGS) $^ -o $(BORUVKA)

clean:
	rm -rf $(OBJDIR)/* $(BUILDDIR)/*


.PHONY: all dijkstra prim kruskal dial boruvka clean
