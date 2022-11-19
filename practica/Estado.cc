// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con lenguajes
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 10/10/22
// Archivo Lenguaje.cc: clase Lenguaje.
// Contiene la implementación de la clase Lenguaje
// que alberga el set sLenguaje_
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 10/10/22 - Creación (primera versión) del código


#include <iostream>
#include <vector>
#include <string>
#include "Estado.h"
#include "Simbolo.h"



void Estado::Asignar(std::string simbolo, std::string transicion) { // Setter
    Simbolo simbolo_auxiliar(simbolo);
    Transiciones_[simbolo_auxiliar].push_back(transicion);
}

std::string Estado::Obtener(std::string simbolo, int orden) { // Getter
    Simbolo simbolo_auxiliar(simbolo);
    return Transiciones_.at(simbolo_auxiliar)[orden];

} 


bool Estado::Buscar(Simbolo simbolo) {
    auto busqueda = Transiciones_.find(simbolo);

    if (busqueda != Transiciones_.end()) {
        return false;
    } 
    
    return true;
}

std::ostream& operator<< (std::ostream &salida, Estado &estado) {
    std::map<Simbolo, std::vector<std::string>>::iterator it;

    for (it = estado.Transiciones_.begin(); it != estado.Transiciones_.end(); it++) {
        
        int numero_enlaces = estado.Transiciones_[it->first].size();
        for (int i = 0; i < numero_enlaces; i++) {
            Simbolo simbolo_auxiliar = (it->first);
            salida << simbolo_auxiliar << " -> " << estado.Transiciones_[it->first][i] << " | ";

        }
    }
    return salida;
}

int Estado::NumeroEnlaces () {
    std::map<Simbolo, std::vector<std::string>>::iterator it;
    int numero_enlaces = 0;

    for (it = Transiciones_.begin(); it != Transiciones_.end(); it++) {
        int dimension = 0;
        dimension = (it->second).size();
        numero_enlaces += dimension;
    }

    return numero_enlaces;
}

bool Estado::EstadoMuerte (std::string estado) {

    std::map<Simbolo, std::vector<std::string>>::iterator it;

    bool estado_muerte = false;

    for (it = Transiciones_.begin(); it != Transiciones_.end(); it++) {
        
        int numero_enlaces = 0;
        numero_enlaces = Transiciones_[it->first].size();
        for (int i = 0; i < numero_enlaces; i++) {
            Simbolo simbolo_auxiliar = (it->first);
            std::cout << simbolo_auxiliar << " -> " << Transiciones_[it->first][i] << " | ";

            std::string nombre_estado = Transiciones_[it->first][i];

            if (nombre_estado != estado) {
                estado_muerte = true;
            } 

        }
    }

    if (Estado_Aceptacion_ && estado_muerte) {
        return true;
    }
    return false;

}


void Estado::Asignar(Simbolo simbolo, std::string transicion) { // Setter
    Transiciones_[simbolo].push_back(transicion);
}

std::string Estado::Obtener(Simbolo simbolo, int orden) { // Getter
    return Transiciones_[simbolo][orden];
} 


int Estado::NumeroTransiciones(std::string simbolo) {
    Simbolo simbolo_auxiliar(simbolo);
    return Transiciones_.at(simbolo_auxiliar).size();
}

int Estado::NumeroTransiciones(Simbolo simbolo) {
    return Transiciones_.at(simbolo).size();
}
