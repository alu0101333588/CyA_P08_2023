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

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "DFA.h"
#include "Gramatica.h"


std::ostream& operator<< (std::ostream &salida, Gramatica &gramatica) {
    salida << gramatica.Producciones_.size() << std::endl; // PRODUCCIONES
    
    std::map<std::string, std::vector<std::string>>::iterator it_aux;

    for (it_aux = gramatica.Producciones_.begin(); it_aux != gramatica.Producciones_.end(); it_aux++) {
        //salida << it_aux->first << std::endl;
        

        int numero_producciones = 0;
        //numero_producciones = it_aux->first.size();
        numero_producciones = gramatica.Producciones_[it_aux->first].size();
        //std::cout << "numero_producciones: " << numero_producciones << std::endl;

        for (int i = 0; i < numero_producciones; i++) {
            salida << it_aux->first << " -> " << it_aux->second[i] << std::endl;
        }
    }

    return salida;

}


std::string Gramatica::No_Terminal (std::string nombre) {

    auto busqueda = No_terminales_.find(nombre);
    if (busqueda != No_terminales_.end()) {
        return No_terminales_.find(nombre)->second;
    } else {
        return "-1";
    }    
}