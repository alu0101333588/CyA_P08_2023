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

#ifndef GRAMATICA_H
#define GRAMATICA_H
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "DFA.h"

class Gramatica {
    private:
        std::set<Simbolo> Terminales_;
        //std::vector<std::vector<std::string>> No_terminales_;
        std::map<std::string, std::string> No_terminales_;
        std::string Simbolo_arranque = "S";
        std::map<std::string, std::vector<std::string>> Producciones_;

    public:
        Gramatica () {}

        void InsertarTerminal(Simbolo terminal) {Terminales_.insert(terminal);}
        void InsertarNoTerminal(std::string no_terminal, std::string estado) {No_terminales_[no_terminal] = estado;}
        void InsertarProduccion(std::string no_terminal, std::string produccion) {Producciones_[no_terminal].push_back(produccion);}

        int NumeroNoTerminales () {return No_terminales_.size();}

        std::string SimboloArranque () {return Simbolo_arranque;}

        std::string No_Terminal (std::string nombre);


        friend std::ostream& operator<< (std::ostream &salida, Gramatica &gramatica);
        
};

#endif