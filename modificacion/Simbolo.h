// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Símbolos, alfabetos y cadenas
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 30/09/22
// Archivo Simbolo.h: clase Simbolo.
// Contiene la clase Simbolo
// que alberga el string Simbolo y gestiona
// todo lo relacionado con el mismo
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 30/09/22 - Creación (primera versión) del código

#ifndef SIMBOLO_H
#define SIMBOLO_H
#include <iostream>
#include <string>

class Simbolo{
    private:
        std::string Simbolo_;

    public:
        Simbolo() {}
        Simbolo (std::string simbolo) {Simbolo_ = simbolo;}
        ~Simbolo() {}
        

        void Asignar (std::string elemento) {Simbolo_ = elemento;} // Setter

        std::string Obtener() {return Simbolo_;} // Getter

        bool operator!=(Simbolo &simbolo);
        bool operator==(Simbolo &simbolo);
        bool operator==(std::string simbolo);

        bool operator<(const Simbolo& simbolo) const {return Simbolo_ < simbolo.Simbolo_;}

        // Operadores no miembros
        friend std::ostream& operator<< (std::ostream &salida, Simbolo &simbolo);

};

#endif