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

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Gramatica.h"
#include "Alfabeto.h"
#include "Simbolo.h"


std::ostream& operator<< (std::ostream &salida, Gramatica &gramatica) {
    
    salida << gramatica.NumeroTerminales() << std::endl; // TERMINALES
    
    salida << gramatica.Terminales_;

    salida << gramatica.NumeroNoTerminales() << std::endl; // NO TERMINALES
    
    for (auto i : gramatica.No_Terminales_) {
        salida << i << std::endl;
    }

    Simbolo simbolo_arranque = gramatica.SimboloArranque(); // SIMBOLO DE ARRANQUE

    salida << simbolo_arranque << std::endl; 

    salida << gramatica.NumeroProducciones() << std::endl; // PRODUCCIONES
    
    std::map<Simbolo, std::vector<std::string>>::iterator it_aux;

    for (it_aux = gramatica.Producciones_.begin(); it_aux != gramatica.Producciones_.end(); it_aux++) {
        //salida << it_aux->first << std::endl;
        

        int numero_producciones = 0;
        //numero_producciones = it_aux->first.size();
        numero_producciones = gramatica.Producciones_[it_aux->first].size();
        //std::cout << "numero_producciones: " << numero_producciones << std::endl;
        Simbolo simbolo_auxiliar = it_aux->first;
        salida << simbolo_auxiliar << " -> ";
        for (int i = 0; i < numero_producciones; i++) {
            
            //salida << simbolo_auxiliar << " -> " << it_aux->second[i] << std::endl;
            if (i == numero_producciones-1) {
                salida << it_aux->second[i] <<  std::endl;
            } else {
                salida << it_aux->second[i] <<  " | ";
            }
            
        }
    }

    return salida;

}

int Gramatica::NumeroProducciones() {
    std::map<Simbolo, std::vector<std::string>>::iterator it_aux;
    int numero_producciones = 0;

    for (it_aux = Producciones_.begin(); it_aux != Producciones_.end(); it_aux++) {    
        numero_producciones += Producciones_[it_aux->first].size(); 
    }
    return numero_producciones;
}

bool Gramatica::BuscarNoTerminal(Simbolo no_terminal) {
    for (auto i : No_Terminales_) {
        if (i == no_terminal) { 
            return true;
        }
    }
    return false;
}


bool Gramatica::ComprobacionesVaciasUnitarias () {

    std::map<Simbolo, std::vector<std::string>>::iterator it_aux;
    for (it_aux = Producciones_.begin(); it_aux != Producciones_.end(); it_aux++) {        

        int numero_producciones = 0;
        numero_producciones = Producciones_[it_aux->first].size();
        Simbolo simbolo_auxiliar = it_aux->first;
        if (numero_producciones == 1) {
            std::string contenido_produccion = it_aux->second[0];
            
            if (contenido_produccion == "&") {
                std::cerr << "ERROR. Hay una producción VACÍA: " << simbolo_auxiliar << " -> " << contenido_produccion << std::endl;
                return false;
            }
        }

        for (int i = 0; i < numero_producciones; i++) {
            std::string contenido_produccion = it_aux->second[i];
            int dimension_contenido_produccion = 0;
            dimension_contenido_produccion = contenido_produccion.length();
            if (dimension_contenido_produccion == 1) {
                if (BuscarNoTerminal(contenido_produccion)) {
                    std::cerr << "ERROR. Hay una producción UNITARIA: " << simbolo_auxiliar << " -> " << contenido_produccion << std::endl;
                    return false;
                }
            }
        }
    }

    return true;
}

Gramatica::Gramatica (std::istream &archivo_lectura) {

    int numeroN;

    archivo_lectura >> numeroN; // TERMINALES

    for (int i = 0; i < numeroN; i++) { 
        std::string terminal;
        archivo_lectura >> terminal;
        Simbolo simbolo_auxiliar(terminal);
        InsertarTerminal(simbolo_auxiliar);
    }
    numeroN = 0;

    archivo_lectura >> numeroN; // NO TERMINALES

    for (int i = 0; i < numeroN; i++) { 
        std::string no_terminal;
        archivo_lectura >> no_terminal;
        Simbolo simbolo_auxiliar(no_terminal);
        InsertarNoTerminal(simbolo_auxiliar);
    }


    std::string simbolo_arranque; // SÍMBOLO DE ARRANQUE
    archivo_lectura >> simbolo_arranque; 
    Simbolo simbolo_auxiliar(simbolo_arranque);

    if (!BuscarNoTerminal(simbolo_auxiliar)) {
        std::cerr << "ERROR. El símbolo de arranque debe estar incluido en los no terminales" << std::endl;
        exit(EXIT_FAILURE);
    }

    Simbolo_arranque_ = simbolo_auxiliar;


    numeroN = 0;

    archivo_lectura >> numeroN; // PRODUCCIONES
    std::string linea;
    getline(archivo_lectura, linea);


    for (int i = 0; i < numeroN; i++) { 
        getline(archivo_lectura, linea);
    
        int dimension_linea = linea.length();
        int k = 0;
        std::string simbolo_noterminal;
        std::string contenido_produccion;

        if (dimension_linea == 0) {
            break;
        }
        
        while (linea[k] != ' ') { // Leemos el símbolo no terminal
            simbolo_noterminal += linea[k];
            k++;
        }
        k++;

        while (linea[k] != ' ') { // Buscamos '->'
            k++;
        }
        k++;

        while (k != dimension_linea) { // Buscamos el contenido de la producción
            std::string elemento_verificar;
            elemento_verificar += linea[k];
            Simbolo simbolo_verificar(elemento_verificar);

            if ((!BuscarNoTerminal(simbolo_verificar)) && (!BuscarTerminal(simbolo_verificar))) {
                std::cerr << "ERROR. Se ha introducido un símbolo que no es no terminal ni terminal (" << linea << ")" << std::endl;
                exit(EXIT_FAILURE);    
            }

            contenido_produccion += linea[k];
            k++;
        }


        Simbolo simbolo_no_terminal(simbolo_noterminal);

        InsertarProduccion(simbolo_no_terminal, contenido_produccion);

        if (!BuscarNoTerminal(simbolo_no_terminal)) {
            std::cerr << "ERROR. El símbolo de no terminal introducido no ha sido definido anteriomente (" << linea << ")" << std::endl;
            exit(EXIT_FAILURE);    
        }

    }

    // Realizar comprobaciones para verificar que no hay produciones unitarias ni vacias
    if (!ComprobacionesVaciasUnitarias()) {
        exit(EXIT_FAILURE);
    }
    

    
}

Gramatica Gramatica::ConvertidorFNChomsky() {
    Gramatica gramatica_primera_fase; 

    gramatica_primera_fase.Terminales_ = Terminales_;
    gramatica_primera_fase.No_Terminales_ = No_Terminales_;
    gramatica_primera_fase.Simbolo_arranque_ = Simbolo_arranque_;

    std::map<Simbolo, std::vector<std::string>>::iterator it;

    for (it = Producciones_.begin(); it != Producciones_.end(); it++) { // PRIMERA PARTE
        
        int numero_producciones = 0;
        numero_producciones = Producciones_[it->first].size();

        for (int i = 0; i < numero_producciones; i++) {
            std::string contenido_produccion_final;
            Simbolo simbolo_auxiliar = it->first;
            std::string contenido_produccion = it->second[i];
            int dimension_contenido_produccion = 0;
            dimension_contenido_produccion = contenido_produccion.length();

            for (int k = 0; k < dimension_contenido_produccion; k++) {
                std::string cont_produc;
                cont_produc += contenido_produccion[k];

                if (BuscarTerminal(cont_produc) && (dimension_contenido_produccion != 1)) {
                    
                    std::string nombre_no_terminal = "C(";
                    nombre_no_terminal += cont_produc;
                    nombre_no_terminal += ")";
                    Simbolo no_terminal(nombre_no_terminal);
                    if (!gramatica_primera_fase.BuscarNoTerminal(no_terminal)) {
                        gramatica_primera_fase.InsertarProduccion(no_terminal, cont_produc);
                        gramatica_primera_fase.InsertarNoTerminal(no_terminal);
                    }
                    
                    contenido_produccion_final += nombre_no_terminal;
                } else {
                    contenido_produccion_final += contenido_produccion[k];
                }
            } 
            gramatica_primera_fase.InsertarProduccion(simbolo_auxiliar, contenido_produccion_final);
        }
    }

    Gramatica gramatica_resulante; 
    char letra = 'D';

    gramatica_resulante.Terminales_ = gramatica_primera_fase.Terminales_;
    gramatica_resulante.No_Terminales_ = gramatica_primera_fase.No_Terminales_;
    gramatica_resulante.Simbolo_arranque_ = gramatica_primera_fase.Simbolo_arranque_;


    for (it = gramatica_primera_fase.Producciones_.begin(); it != gramatica_primera_fase.Producciones_.end(); it++) { // SEGUNDA PARTE
        int numero_producciones = 0;
        numero_producciones = gramatica_primera_fase.Producciones_[it->first].size();
        int contador = 0;


        for (int i = 0; i < numero_producciones; i++) {
            std::string contenido_produccion_final;
            Simbolo simbolo_auxiliar = it->first;
            std::string contenido_produccion = it->second[i];
            Simbolo simbolo_contenido(contenido_produccion);
            int dimension_contenido_produccion = 0;
            dimension_contenido_produccion = contenido_produccion.length();
            std::string contenido;
            int contador_no_terminales = 0;

            for (int k = 0; k < dimension_contenido_produccion; k++) {
                contenido += contenido_produccion[k];
                Simbolo no_terminal_a_buscar(contenido);
                if (gramatica_primera_fase.BuscarNoTerminal(no_terminal_a_buscar)) {
                    contador_no_terminales++;
                    contenido.resize(0);
                }
            }
                

            if (contador_no_terminales >= 3) {

                std::string contenido_produccion_aux = contenido_produccion;
                int dimension_contenido_produccion_aux = dimension_contenido_produccion;
                Simbolo simbolo_aux = simbolo_auxiliar;
                while (contador_no_terminales >= 3) {
                    contador++;

                    std::string cont_produc;
                    int contador_referencia = 0;

                    for (int k = 0; k < dimension_contenido_produccion_aux; k++) { // Posición primer no terminal
                        cont_produc += contenido_produccion_aux[k];
                        Simbolo no_terminal_a_buscar(cont_produc);
                        if (gramatica_primera_fase.BuscarNoTerminal(no_terminal_a_buscar)) {
                            contador_referencia = k+1;
                            break;
                        }
                    }

                    cont_produc.resize(0);

                    for (int k = contador_referencia; k < dimension_contenido_produccion_aux; k++) { // Contenido resto de no terminales
                        cont_produc += contenido_produccion_aux[k];
                    }

                    std::string nombre_no_terminal; // LA SEGUNDA PARTE DE LA PRODUCCIÓN
                    nombre_no_terminal += letra;
                    nombre_no_terminal += "(";
                    nombre_no_terminal += std::to_string(contador);
                    nombre_no_terminal += ")";
                    Simbolo no_terminal(nombre_no_terminal);

                    std::string contenido_produccion_auxiliar; // LA PRIMERA PARTE DE LA PRODUCCIÓN
                    for (int k = 0; k < contador_referencia; k++) { 
                        contenido_produccion_auxiliar += contenido_produccion_aux[k];
                    }
                    contenido_produccion_auxiliar += nombre_no_terminal;
                
                    gramatica_resulante.InsertarProduccion(simbolo_aux, contenido_produccion_auxiliar);
                    gramatica_resulante.InsertarNoTerminal(simbolo_aux);

                    contenido_produccion_aux = cont_produc;
                    dimension_contenido_produccion_aux = cont_produc.size();
                    contenido.resize(0);
                    int contador_no_terminales_aux = 0;

                    for (int k = 0; k < dimension_contenido_produccion_aux; k++) {
                        contenido += contenido_produccion_aux[k];
                        Simbolo no_terminal_a_buscar(contenido);
                        if (gramatica_primera_fase.BuscarNoTerminal(no_terminal_a_buscar)) {
                            contador_no_terminales_aux++;
                            contenido.resize(0);
                        }
                    }
                    contador_no_terminales = contador_no_terminales_aux;    
                    simbolo_aux.Asignar(nombre_no_terminal);

                    if (contador_no_terminales < 3) {
                        gramatica_resulante.InsertarProduccion(nombre_no_terminal, cont_produc);
                        gramatica_resulante.InsertarNoTerminal(nombre_no_terminal);
                    }

                }
                letra++; 
                contador = 0;

            } else {
                if (!gramatica_resulante.BuscarNoTerminal(simbolo_auxiliar)) {
                    gramatica_resulante.InsertarNoTerminal(simbolo_auxiliar);
                }
                gramatica_resulante.InsertarProduccion(simbolo_auxiliar, contenido_produccion);
            }
            
        } 
    }

    return gramatica_resulante;
}