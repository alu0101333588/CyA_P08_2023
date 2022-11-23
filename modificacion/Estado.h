// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con lenguajes
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 10/10/22
// Archivo Lenguaje.h: clase Lenguaje.
// Contiene la clase Lenguaje
// que alberga el set sLenguaje_ y
// todo lo relacionado con el mismo
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 10/10/22 - Creación (primera versión) del código


#ifndef ESTADO_H
#define ESTADO_H
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "Simbolo.h"

class Estado {
    private:
        std::map<Simbolo, std::vector<std::string>> Transiciones_;
        bool Estado_Aceptacion_ = false;

    public:
        Estado() {}
        Estado (bool estado_aceptacion) {Estado_Aceptacion_ = estado_aceptacion;}

        void EstadoAceptacion(){Estado_Aceptacion_ = true;} // Al ser llamado se autodefine como un estado de aceptación

        bool E_Aceptacion() {return Estado_Aceptacion_;} // Responde si es o no un estado de aceptación

        void Asignar(std::string simbolo, std::string transicion); // Setter
        void Asignar (Simbolo simbolo, std::string transicion);

        std::string Obtener(Simbolo simbolo, int orden); // Getter
        std::string Obtener(std::string simbolo, int orden); // Getter

        bool EstadoMuerte (std::string estado);

        bool Buscar(Simbolo simbolo);

        std::vector<std::string> operator[] (Simbolo simbolo) {return Transiciones_[simbolo];}
        std::string operator() (Simbolo simbolo) {return Transiciones_[simbolo][0];}

        int NumeroTransiciones (std::string simbolo);
        int NumeroTransiciones (Simbolo simbolo);

        int NumeroEnlaces ();
                

        friend std::ostream& operator<< (std::ostream &salida, Estado &estado);
        bool operator<(const Estado& estado) const {return Transiciones_ < estado.Transiciones_;}
};

#endif