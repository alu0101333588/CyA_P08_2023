
// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Símbolos, alfabetos y cadenas
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 30/09/22
// Archivo Alfabeto.cc: clase Alfabeto.
// Contiene la implementación de las
// funciones de la clase Alfabeto
// que alberga el vector alfabeto y gestiona
// todo lo relacionado con el mismo
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 30/09/22 - Creación (primera versión) del código

#include <iostream>
#include <vector>
#include <string>
#include "Alfabeto.h"
#include "Simbolo.h"

void Alfabeto::Insertar (std::string simbolo) {
    Simbolo simbolo1 (simbolo);
    Alfabeto_.insert(simbolo1);
}

bool Alfabeto::Buscar (std::string elemento) {

    for (auto i : Alfabeto_) {
        if (i == elemento) { // i.Obtener()
            return true;
        }
    }

    if (elemento == "&") {
        return true;
    }
    return false;
}

void Alfabeto::Insertar (Simbolo &simbolo) {
    Alfabeto_.insert(simbolo);
}

Alfabeto::Alfabeto (std::string linea) {
    int longitud = linea.length();
    std::string linea_entrada;
    for (int i = 0; i < longitud+1; i++) {
        if (linea[i] == ' ') {
            Insertar(linea_entrada);
            linea_entrada.resize(0);
        } else {
            linea_entrada += linea[i];
        }
    }
}

void Alfabeto::operator() (std::string linea) {
    int longitud = linea.length();
    std::string linea_entrada;
    for (int i = 0; i < longitud; i++) {
        if (linea[i] == ' ') {
            Insertar(linea_entrada);
            linea_entrada.resize(0);
        } else {
            linea_entrada += linea[i];
        }
    }

    if (linea_entrada != " ") {
        Insertar(linea_entrada);
    }

}

/*Alfabeto Alfabeto::operator* (Alfabeto &alfabeto) {
    if (alfabeto.Dimension() == 0) {
        return *this;
    }
    Alfabeto alfabeto_resultante;
    for (auto i : Alfabeto_) {
        alfabeto_resultante.Insertar(i);
    }
    for (auto i : alfabeto.Alfabeto_) {
        alfabeto_resultante.Insertar(i);
    }
    return alfabeto_resultante;
}*/

std::ostream& operator<<(std::ostream &salida, Alfabeto &alfabeto) {
    salida << "{ ";
    for (auto i : alfabeto.Alfabeto_) {
        salida << i << " ";
    }
    salida << "}";
    return salida;
}


/*Alfabeto Alfabeto::operator+(Alfabeto &alfabeto_entrante) {
    Alfabeto alfabeto_resultante;

    for (auto i : alfabeto_entrante.Alfabeto_) {
        alfabeto_resultante.Insertar(i);
    }
    for (auto i : Alfabeto_) {
        alfabeto_resultante.Insertar(i);
    }

    return alfabeto_resultante;
}

Alfabeto Alfabeto::operator|(Alfabeto &alfabeto_entrante) {
    Alfabeto alfabeto_resultante;

    for (auto i : alfabeto_entrante.Alfabeto_) {
        alfabeto_resultante.Insertar(i);
    }
    for (auto i : Alfabeto_) {
        alfabeto_resultante.Insertar(i);
    }

    return alfabeto_resultante;
}

Alfabeto Alfabeto::operator^(Alfabeto &alfabeto_entrante) {
    Alfabeto alfabeto_resultante;

    for (auto i : Alfabeto_) {
        for (auto j : alfabeto_entrante.Alfabeto_) {
            if (i.Elemento() == j.Elemento()) {
                alfabeto_resultante.Insertar(i);
            }
        }
    }

    return alfabeto_resultante;
}

Alfabeto Alfabeto::operator-(Alfabeto &alfabeto_entrante) {
    Alfabeto alfabeto_resultante;

    for (auto i : Alfabeto_) {
        bool repeticion = false;
        for (auto j : alfabeto_entrante.Alfabeto_) {
            if (i.Elemento() == j.Elemento()) {
                repeticion = true;
            }
        }
        if (!repeticion) {
            alfabeto_resultante.Insertar(i);
        }
    }

    return alfabeto_resultante;
}*/