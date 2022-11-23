// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Símbolos, alfabetos y cadenas
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 12/10/21
// Archivo main.cc: fichero principal.
// Contiene el fichero principal
// del programa. Haciendo llamada
// a las funciones necesarias
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 12/10/21 - Creación (primera versión) del código





// ./Grammar2CNF input.gra input.gra

#include <iostream>
#include <fstream>
#include <string>
#include "Gramatica.h"


void Usage(int argc, char* argv[]);

int main(int argc, char* argv[]) {

  Usage(argc, argv);

  std::string teclado = argv[1];
  std::string teclado2 = argv[2];

  std::ifstream lectura(teclado);
  std::ofstream escritura(teclado2);

  Gramatica gramatica (lectura);

  Gramatica gramatica_FNC = gramatica.ConvertidorFNChomsky();

  escritura << gramatica_FNC;
  

  return 0;
  
    
}


void Usage(int argc, char* argv[]) { 
  if(argc != 3) {
    if(argc == 2) {
      std::string parameter{argv[1]};
      if(parameter == "--help") { 
        std::cout << "El programa rellenará un documento de texto de salida con la gramática en FNC" << std::endl;
        exit(EXIT_SUCCESS);
      }
    }
    std::cout << "./Grammar2CNF - Gramáticas en Forma Normal de Chomsky" << std::endl << "Modo de uso: ./Grammar2CNF input.gra output.gra" << std::endl;
    std::cout << "Pruebe ./Grammar2CNF --help para más información"<< std::endl;
    exit(EXIT_SUCCESS);
  }
}