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
#include "Simbolo.h"
#include "Alfabeto.h"

class Gramatica {
    private:
        Alfabeto Terminales_;
        std::set<Simbolo> No_Terminales_;
        Simbolo Simbolo_arranque_;
        std::map<Simbolo, std::vector<std::string>> Producciones_;

    public:
        Gramatica (std::istream &archivo_lectura);
        Gramatica () {}

        void InsertarTerminal(Simbolo terminal) {Terminales_.Insertar(terminal);}
        void InsertarNoTerminal(Simbolo no_terminal) {No_Terminales_.insert(no_terminal);}
        void InsertarProduccion(Simbolo no_terminal, std::string produccion) {Producciones_[no_terminal].push_back(produccion);}
        
        int NumeroNoTerminales () {return No_Terminales_.size();}
        int NumeroTerminales () {return Terminales_.Dimension();}
        int NumeroProducciones();


        Simbolo SimboloArranque () {return Simbolo_arranque_;}

        bool BuscarNoTerminal(Simbolo no_terminal);
        bool BuscarTerminal(Simbolo no_terminal) {return Terminales_.Buscar(no_terminal);}

        bool ComprobacionesVaciasUnitarias ();

        Gramatica ConvertidorFNChomsky();

        friend std::ostream& operator<< (std::ostream &salida, Gramatica &gramatica);
        
};

#endif