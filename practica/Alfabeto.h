// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Símbolos, alfabetos y cadenas
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 30/09/22
// Archivo Alfabeto.h: clase Alfabeto.
// Contiene la clase Alfabeto
// que alberga el vector alfabeto y gestiona
// todo lo relacionado con el mismo
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 30/09/22 - Creación (primera versión) del código

#ifndef ALFABETO_H
#define ALFABETO_H
#include <fstream>
#include <iostream>
//#include <vector>
#include <string>
#include "Simbolo.h"
#include <set>

class Alfabeto{
    private:
        std::set<Simbolo> Alfabeto_;
    public:
        Alfabeto () {}
        Alfabeto (std::string linea);
        ~Alfabeto () {}


        void operator() (std::string linea);

        void Insertar (std::string simbolo); // Añade un string al Alfabeto
        void Insertar (Simbolo &simbolo);

        // Alfabeto operator+(Alfabeto &alfabeto_entrante); // Concatenación
        // Alfabeto operator|(Alfabeto &alfabeto_entrante); // Unión
        // Alfabeto operator^(Alfabeto &alfabeto_entrante); // Intersección
        // Alfabeto operator-(Alfabeto &alfabeto_entrante); // Diferencia
        int Dimension () {return Alfabeto_.size();}

        bool Buscar (std::string elemento);
        bool Buscar (Simbolo elemento);

        std::set<Simbolo> ContenidoAlfabeto() {return Alfabeto_;}

        // Operadores no miembros
        friend std::ostream& operator<< (std::ostream &salida, Alfabeto &alfabeto);
        
};

#endif