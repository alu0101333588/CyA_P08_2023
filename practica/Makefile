# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Computabilidad y Algoritmia
#
# @author Andrés Hernández O.
# @date 01 octubre 2022


# The name of the target program
TARGET  = dfa2grammar

# Select Compiler and flags
CC=g++
CFLAGS=-std=c++2a -g -Wall   # Compiler options (C++14, preserve debug symbols and warn all)


SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)

# Special include directories
INCLUDE = -I.

# Special libraries (none for now)
LIB =

$(TARGET): dfa2grammar.o Cadena.o Alfabeto.o Simbolo.o DFA.o Estado.o Gramatica.o
	$(CC) -o $@ $^ $(LIB)

dfa2grammar.o: dfa2grammar.cc
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Cadena.o: Cadena.cc Cadena.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Estado.o: Estado.cc Estado.h 
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Simbolo.o: Simbolo.cc Simbolo.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

DFA.o: DFA.cc DFA.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Alfabeto.o: Alfabeto.cc Alfabeto.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Gramatica.o: Gramatica.cc Gramatica.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
	rm -f *~