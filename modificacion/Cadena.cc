// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Símbolos, alfabetos y cadenas
// Autor: Andrés Hernández Ortega
// Correo: alu0101333588@ull.es
// Fecha: 30/09/22
// Archivo Cadena.cc: clase Cadena y procedimientos generales.
// Contiene la implementación de la clase Cadena
// que alberga el string sCadena vector vCadena y gestiona
// todo lo relacionado con los mismos
// y clases para procedimientos generales 
// del programa como el Usage
// Referencias: --
// Enlaces de inter ́es --

// Historial de revisiones
// 30/09/22 - Creación (primera versión) del código

#include <iostream>
#include <vector>
#include <string>
#include "Cadena.h"
#include "Simbolo.h"
#include "Alfabeto.h"


Cadena::Cadena(std::string cadena, Alfabeto &alfabeto) { // Constructor

    int longitud = cadena.length();
    std::string simbolo;
    int sumador_longitud_introducida = 0;

    if (cadena == "&") {
        Cadena_.push_back(cadena);
        sumador_longitud_introducida = 1;
    } else {
        for (int i = 0; i < longitud; i++) {

            simbolo += cadena[i];

            if (alfabeto.Buscar(simbolo)) {
                sumador_longitud_introducida = sumador_longitud_introducida + simbolo.length();
                Cadena_.push_back(simbolo);
                simbolo.resize(0);
            }
        
        }
        
        if (sumador_longitud_introducida != longitud) {
            std::cerr << "--- ERROR. Alguno de los símbolos de la cadena introducida no pertenecen al alfabeto [" << cadena << " :: " << alfabeto << "]: " << sumador_longitud_introducida << std::endl;
            Pertenece_ = false;
        }
    }
    
    

    
}


void Cadena::Insertar (std::string simbolo) {
    Simbolo simbolo_auxiliar;
    simbolo_auxiliar.Asignar(simbolo);
    Cadena_.push_back(simbolo_auxiliar);

}

std::ostream& operator<<(std::ostream &salida, Cadena &cadena) {

    int dimension_cadena = cadena.Cadena_.size();
    for (int i = 0; i < dimension_cadena; i++) {
        salida << cadena.Cadena_[i]; 
    }
    return salida;

}


std::string Cadena::Obtener() {
    std::string cadena_resultante;
    int dimension_cadena = Cadena_.size();
    for (int i = 0; i < dimension_cadena; i++) {
        cadena_resultante += Cadena_[i].Obtener();
    }
    return cadena_resultante;
}

std::string Cadena::Obtener(int posicion) {
    Simbolo simbolo_auxiliar;
    simbolo_auxiliar = Cadena_[posicion];

    std::string string_auxiliar;
    string_auxiliar = simbolo_auxiliar.Obtener();
    return string_auxiliar;
}

/*bool Cadena::Vacio() { // ¿Hay un &?
    int dimension = Cadena_.size();
    for (int i = 0; i < dimension; i++) {
        if (Cadena_[i].Elemento() == "&") {
            return true;
        }
    }
    return false;
}*/


bool Cadena::operator==(Cadena &cadena) {

    int dimension_cadena = cadena.Cadena_.size();
    int dimension_cadena_local = Cadena_.size();
    if (dimension_cadena_local != dimension_cadena) {
        return false;
    }

    for (int i = 0; i < dimension_cadena_local; i++) {
        if (Cadena_[i] != cadena.Cadena_[i]) {
            return false;
        }
    }
    return true;
}

// Catalogo de opciones

int Cadena::Longitud() { // Opción 1
    if (Cadena_[0] == "&") {
        return 0;
    }
    return Cadena_.size();
}

/*Cadena Cadena::Inversa() {
    Cadena cadena_inversa;
    for(int i = Dimension() - 1 ; i > -1; i = i - 1) {
        cadena_inversa.Insertar(Cadena_[i].Elemento());
    }

    return cadena_inversa;
}


void Cadena::Sufijos(std::ostream &salida) { // Opción 4
    salida << "& ";
    for(int i = Dimension() - 1; i > -1; i = i - 1) {

        for(int j = i; j < Dimension(); j++) {
            salida << Cadena_[j].Elemento();
        }
        salida << " "; 
    }   
    salida << std::endl;
}

void Cadena::Prefijos(std::ostream &salida) { // Opción 3
    salida << "& ";
    for(int l = 0; l < Dimension(); l++) {
        for(int j = 0; j < l + 1; j++) {
            salida << Cadena_[j].Elemento();
        }
        salida << " "; 
    } 

}


void Cadena::Subcadenas(std::ostream &salida) { // Opción 5
    salida << "& ";    
    std::vector<std::string> vSubcadenas; // Para evitar repeticiones

    for(int i = 0; i < Dimension(); i++) { // Recorro vCadena
        vSubcadenas.push_back(Cadena_[i].Elemento());
    } 

    int tam = vSubcadenas.size();
    bool Repe = false; // evitar repetición de elementos
    std::string impresion = ""; // concatenación de elementos de vCadena

    for(int l = 0; l < Dimension(); l++) { // Incluyo prefijos
        for(int j = 0; j < l+1; j++){
            impresion += Cadena_[j].Elemento();
        }            

        
        for(int z = 0; z < tam; z++) { // evitar repeticiones
            if (vSubcadenas[z] == impresion) {
                Repe = true;
            }
        }

        if (Repe == false) {
            vSubcadenas.push_back(impresion);
            tam = vSubcadenas.size();
        } else {
            Repe = false;
        }
        impresion = "";

    } 

    Repe = false;
    for(int i = Dimension()-1; i > -1; i = i-1) { // Incluyo sufijos

        for(int j = i; j < Dimension(); j++) {
            impresion += Cadena_[j].Elemento();
        }

        for(int z = 0; z < tam; z++) { // evitar repeticiones
            if (vSubcadenas[z] == impresion){
                Repe = true;
            }
        }

        if (Repe == false) {
            vSubcadenas.push_back(impresion);
            tam = vSubcadenas.size();
        } else {
            Repe = false;
        }

        impresion = "";
    }   
    for(int l = 0; l < Dimension(); l++) { // Incluyo elementos del medio
        for(int j = l+1; j < Dimension(); j++) {
            for(int z = l; z < j+1; z++) {
                impresion += Cadena_[z].Elemento();
            }
            
            for(int z = 0; z < tam; z++) {
                if(vSubcadenas[z] == impresion) {
                    Repe = true;
                }
            }

            if (Repe == false) {
                vSubcadenas.push_back(impresion);
                tam = vSubcadenas.size();
            } else {
                Repe = false;
            }
            impresion = "";
        }

        
    } 
    


    for(int i = 0; i < tam; i++) {
        salida << vSubcadenas[i] << " ";
    }

    salida << std::endl;
    vSubcadenas.resize(0);
}*/

