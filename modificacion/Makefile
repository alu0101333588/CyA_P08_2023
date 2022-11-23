# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Computabilidad y Algoritmia
#
# @author Andrés Hernández O.
# @date 01 octubre 2022


# The name of the target program
TARGET  = Grammar2CNF

# Select Compiler and flags
CC=g++
CFLAGS=-std=c++2a -g -Wall   # Compiler options (C++14, preserve debug symbols and warn all)


SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)

# Special include directories
INCLUDE = -I.

# Special libraries (none for now)
LIB =

$(TARGET): Grammar2CNF.o Alfabeto.o Simbolo.o Gramatica.o
	$(CC) -o $@ $^ $(LIB)

Grammar2CNF.o: Grammar2CNF.cc
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Simbolo.o: Simbolo.cc Simbolo.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Alfabeto.o: Alfabeto.cc Alfabeto.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

Gramatica.o: Gramatica.cc Gramatica.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
	rm -f *~