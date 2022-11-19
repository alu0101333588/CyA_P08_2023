// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con lenguajes
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 10/10/22
// Archivo Simbolo.cc: clase Simbolo.
// Contiene la implementación
// de la clase Simbolo
// que alberga el string Simbolo y gestiona
// todo lo relacionado con el mismo
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 10/10/2022 - Creación (primera versión) del código

#include <fstream>
#include <iostream>
#include <string>
#include "Simbolo.h"

/*void Simbolo::Eliminar() { // Destructor
    Simbolo_.resize(0);
}*/

std::ostream& operator<<(std::ostream &salida, Simbolo &simbolo) {
    salida << simbolo.Simbolo_;
    return salida;
}

/*void Simbolo::AnadirC (char caracter){
    
    Simbolo_.push_back(caracter);
}*/


bool Simbolo::operator!=(Simbolo &simbolo) {

    if (Simbolo_ != simbolo.Simbolo_) {
        return true;
    }
    return false;

}

bool Simbolo::operator==(Simbolo &simbolo) {
    if (Simbolo_ == simbolo.Simbolo_) {
        return true;
    }
    return false;
}

bool Simbolo::operator==(std::string simbolo) {

    if (Simbolo_ == simbolo) {
        return true;
    }
    return false;
}