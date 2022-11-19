// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Símbolos, alfabetos y cadenas
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 30/09/22
// Archivo Cadena.h: clase Cadena y procedimientos generales.
// Contiene la clase Cadena
// que alberga el string sCadena vector vCadena y gestiona
// todo lo relacionado con los mismos
// y clases para procedimientos generales 
// del programa como el Usage
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 30/09/22 - Creación (primera versión) del código


#ifndef CADENA_H
#define CADENA_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Simbolo.h"
#include "Alfabeto.h"


class Cadena {
    private:
        std::vector<Simbolo> Cadena_; // Almacenada la cadena
        bool Pertenece_ = true;
         
    public:
        Cadena () {} // Constructor
        Cadena (std::string cadena, Alfabeto &alfabeto);
        ~Cadena () {}

        std::string Obtener(); // Getter
        //void Establecer(std::string cadena); // Setter

        void Insertar (std::string simbolo);

        bool Pertenece() {return Pertenece_;}

        friend std::ostream& operator<<(std::ostream &salida, Cadena &cadena);

        bool operator==(Cadena &cadena);
        bool operator<(const Cadena& cadena) const {return Cadena_ < cadena.Cadena_;}

        Simbolo operator[](int posicion) {return Cadena_[posicion];}
        
        std::string Obtener(int posicion);


        //Catalogo de opciones
        int Longitud(); // Tiene en cuenta el &

        int Longitud_Cadena() {return Cadena_.size();} // Las posiciones del vector, sin tener en cuenta el &


        /*Cadena Inversa();
        void Sufijos(std::ostream &salida); 
        void Prefijos(std::ostream &salida); 
        void Subcadenas(std::ostream &salida);       
        bool Vacio();*/

};

#endif