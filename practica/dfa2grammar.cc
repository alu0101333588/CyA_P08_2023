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





// ./p06_automata_simulator input.fa input.txt

#include <iostream>
#include <fstream>
#include <string>
#include "DFA.h"
#include "Gramatica.h"

// Modificación clase:
// recibir una subcadena y alfabeto
// aba
// a,b

// S-> abaX
// X-> aX | bX


void Usage(int argc, char* argv[]);

int main(int argc, char* argv[]) {

  Usage(argc, argv);

  std::string teclado = argv[1];
  std::string teclado2 = argv[2];

  std::ifstream lectura(teclado);
  std::ofstream escritura(teclado2);

  //std::cout << "FA: " << teclado << " :: Cadenas: " << teclado2 << std::endl;

  DFA dfa(lectura);

  Cadena cadena_entrante;
  Alfabeto alfabeto_entrante;
  alfabeto_entrante.Insertar("a");
  alfabeto_entrante.Insertar("b");
  cadena_entrante.Insertar("aba");

  Gramatica gramatica = dfa.Gramatica_Modificacion(cadena_entrante, alfabeto_entrante);

  std::cout << gramatica << std::endl;
  

  return 0;
  
    
}


void Usage(int argc, char* argv[]) { 
  if(argc != 3) {
    if(argc == 2) {
      std::string parameter{argv[1]};
      if(parameter == "--help") { 
        std::cout << "El programa rellenará un documento de texto de salida con los resultados de la operación seleccionada" << std::endl;
        exit(EXIT_SUCCESS);
      }
    }
    std::cout << "./p06_automata_simulator - Simulación de Autómatas Finitos" << std::endl << "Modo de uso: ./p06_automata_simulator input.fa input.txt" << std::endl;
    std::cout << "Pruebe ./p06_automata_simulator --help para más información"<< std::endl;
    exit(EXIT_SUCCESS);
  }
}