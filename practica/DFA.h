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

#ifndef DFA_H
#define DFA_H
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include "Alfabeto.h"
#include "Estado.h"
#include "Cadena.h"
#include "Gramatica.h"

class DFA {
    private:
        Alfabeto Alfabeto_;
        int Numero_Estados_;
        std::string Estado_Arranque_;
        std::map<std::string, Estado> DFA_;

        bool ErrorEncontrado_ = false;
        std::map<std::string, bool> Estados_Definidos_; // Verifica que todos los estados indicados están definidos

    public:
        DFA () {}
        DFA (std::istream &archivo_lectura);

        Gramatica ConvertiraGramatica();


        Alfabeto alfabeto() {return Alfabeto_;}

        void ExistenciaEstado(std::string nombre_estado);

        bool CadenasAceptadas(Cadena &cadena);
        bool RecorridoDFA(Cadena cadena, std::string estado_actual, int posicion_cadena);

        Gramatica Gramatica_Modificacion(Cadena &cadena, Alfabeto &alfabeto); // MODIFICACIÓN

        bool EstadoAceptacion(std::string estado);
        void EstadosAceptacion();

        bool EsDFA(); // Verifica que sea un DFA

        bool EstadosDefinidos(); // Responde si todos los estados indicados han sido definidos

        friend std::ostream& operator<< (std::ostream &salida, DFA &fa);
        
};

#endif