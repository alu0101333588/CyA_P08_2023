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

#include <set>
#include <map>
#include <string>
#include "DFA.h"
#include <fstream>
#include <iostream> 
#include "Estado.h"
#include "Cadena.h"


DFA::DFA (std::istream &archivo_lectura) { // Constructor
    
    std::string linea;
    getline(archivo_lectura, linea);
    Alfabeto_(linea);

    archivo_lectura >> Numero_Estados_;

    archivo_lectura >> Estado_Arranque_;
    
    getline(archivo_lectura, linea);

    //std::cout << "PREVIA: " << Numero_Estados_ << " : " << Estado_Arranque_ << " :: Alfabeto: " << Alfabeto_ << std::endl;
    
    std::string estado, estados; 
    int opcion, transiciones;
    // estado = nombre del estado
    // opcion = 1 o 0 en función de si es o no de aceptación
    // estados = estado siguiente
    // transiciones = número de transiciones

    while(!archivo_lectura.eof() && ErrorEncontrado_ == false){ // Repite el proceso línea por línea

        archivo_lectura >> estado;
        archivo_lectura >> opcion;
        archivo_lectura >> transiciones;

        Estado estado_auxiliar;

        if (opcion == 1) {
            //FA_[estado]
            estado_auxiliar.EstadoAceptacion(); // Indicar que es un estado de aceptación
        }

        Estados_Definidos_[estado] = true;

        for (int i = 0; i < transiciones; i++) {
            std::string transicion;
            archivo_lectura >> transicion;
            Simbolo simbolo_auxiliar(transicion);
            archivo_lectura >> estados;
            ExistenciaEstado(estados);
            //std::cout << "PRUEBA: " << estado << " (" << transicion << ")-> " << estados << std::endl;

            if (!Alfabeto_.Buscar(transicion) && transicion != "&") {
                std::cerr << "El enlace introducido no existe" << std::endl;
                exit(EXIT_FAILURE);
                ErrorEncontrado_ = true;
            }

            estado_auxiliar.Asignar(simbolo_auxiliar, estados);
        }
        //std::cout << std::endl;
        DFA_[estado] = estado_auxiliar;
    }

    if (!EstadosDefinidos()) { // En caso de que no haya algún estado definido establecemos que hay un error
        exit(EXIT_FAILURE);
        ErrorEncontrado_ =  true;
    }

    if (!EsDFA()) {
        std::cerr << "ERROR. Las especificaciones introducidas no se corresponden con un DFA" << std::endl;
        ErrorEncontrado_ =  true;
        exit(EXIT_FAILURE);
        
    }
    
}


Gramatica DFA::Gramatica_Modificacion(Cadena &cadena, Alfabeto &alfabeto) { // MODIFICACIÓN

    Gramatica gramatica_resultante;

    std::set<Simbolo> alfabeto_auxiliar = alfabeto.ContenidoAlfabeto();

    std::string terminal_auxiliar;
    terminal_auxiliar += cadena.Obtener();
    terminal_auxiliar += "X";

    gramatica_resultante.InsertarNoTerminal(terminal_auxiliar, gramatica_resultante.SimboloArranque());
    gramatica_resultante.InsertarProduccion(gramatica_resultante.SimboloArranque(), terminal_auxiliar);

    for (auto i : alfabeto_auxiliar) { // TERMINALES
        gramatica_resultante.InsertarTerminal(i);
        std::string terminal_auxiliar;
        Simbolo simbolo_auxiliar = i;
        terminal_auxiliar += i.Obtener();
        terminal_auxiliar += "X";
        gramatica_resultante.InsertarNoTerminal(terminal_auxiliar, "X");
        gramatica_resultante.InsertarProduccion("X", terminal_auxiliar);
    }    

    gramatica_resultante.InsertarProduccion("X", "&");

    gramatica_resultante.InsertarNoTerminal("&", "X");
    
    return gramatica_resultante;    
}

void DFA::ExistenciaEstado(std::string nombre_estado) {
    auto busqueda = Estados_Definidos_.find(nombre_estado);
    if (busqueda == Estados_Definidos_.end()) { // si no se encuentra un estado se añade
        Estados_Definidos_[nombre_estado] = false;
    }   
}

bool DFA::EstadosDefinidos() {
    std::map<std::string, bool>::iterator it;

    for (it = Estados_Definidos_.begin(); it != Estados_Definidos_.end(); it++) {
        if ((it->second) == false) {
            std::cerr << "ERROR. El estado " << it->first << " no ha sido definido [" << it->second << "]" << std::endl;
            exit(EXIT_FAILURE);
            ErrorEncontrado_ = true;
        }
    }
    return true;
}

bool DFA::EstadoAceptacion(std::string estado) {
    return DFA_[estado].E_Aceptacion();
}

void DFA::EstadosAceptacion() {
    std::map<std::string, Estado>::iterator it;
    std::cout << "ESTADOS DE ACEPTACIÓN: ";
    for (it = DFA_.begin(); it != DFA_.end(); it++) {

        bool aceptacion = it->second.E_Aceptacion();

        if (aceptacion) {
            std::cout << it->first << " :: ";
        }
    }
    std::cout << std::endl;
}

bool DFA::CadenasAceptadas(Cadena &cadena) {

    if (ErrorEncontrado_) {
        std::cerr << " --- ERROR con el FA, está mal definido" << std::endl;
        return false;
    }

    //std::string cadena_auxiliar = cadena.Obtener();

    

    std::string estado_actual = Estado_Arranque_;
    int posicion_cadena = 0;

    if (EstadoAceptacion(estado_actual) && cadena.Obtener() == "&") {
        return true; 
    }

    if (RecorridoDFA(cadena, estado_actual, posicion_cadena)) {
        return true;
    }

    return false;
}


std::ostream& operator<< (std::ostream &salida, DFA &fa) {

    std::map<std::string, Estado>::iterator it;

    for (it = fa.DFA_.begin(); it != fa.DFA_.end(); it++) {
        
        salida << it->first << ": " << it->second;
    }
    return salida;

}

bool DFA::EsDFA() {

    std::map<std::string, Estado>::iterator it;

    for (it = DFA_.begin(); it != DFA_.end(); it++) {
        
        std::set<Simbolo> alfabeto_auxiliar = Alfabeto_.ContenidoAlfabeto();

        for (auto i : alfabeto_auxiliar) {

            int numero_enlaces = 0;
            numero_enlaces = DFA_[it->first][i].size(); 

            if (numero_enlaces >= 2) {
                return false;
            }
        } 
    }
    return true;
}

Gramatica DFA::ConvertiraGramatica() {
    Gramatica gramatica_resultante;

    std::set<Simbolo> alfabeto_auxiliar = Alfabeto_.ContenidoAlfabeto();

    for (auto i : alfabeto_auxiliar) { // TERMINALES
        gramatica_resultante.InsertarTerminal(i);
    }    

    std::map<std::string, Estado>::iterator it;

    char noterminal = 'A';

    for (it = DFA_.begin(); it != DFA_.end(); it++) { // NO TERMINALES
        if ((it->first) == Estado_Arranque_) {
            gramatica_resultante.InsertarNoTerminal(it->first, gramatica_resultante.SimboloArranque()); // SIMBOLO DE ARRANQUE
        } else {
            std::string nterminal;
            nterminal += noterminal;
            gramatica_resultante.InsertarNoTerminal(it->first, nterminal);
            noterminal++;
        } 
    }

    for (it = DFA_.begin(); it != DFA_.end(); it++) { // PRODUCCIONES

        std::string nombre_noterminal;
        std::string elemento_a_buscar;
        elemento_a_buscar = it->first;
        nombre_noterminal = gramatica_resultante.No_Terminal(elemento_a_buscar);

        for (auto i : alfabeto_auxiliar) { // TERMINALES
            std::string produccion_auxiliar;
            produccion_auxiliar = DFA_[it->first](i);

            int numero_enlaces = 0;
            numero_enlaces = DFA_[it->first][i].size(); 
            produccion_auxiliar = gramatica_resultante.No_Terminal(produccion_auxiliar);

            if (numero_enlaces != 0) {
                
                std::string produccion_resultante;
                produccion_resultante += i.Obtener();
                produccion_resultante += produccion_auxiliar;
                gramatica_resultante.InsertarProduccion(nombre_noterminal, produccion_resultante);

            }
        } 

        if (DFA_[it->first].E_Aceptacion()) {
            gramatica_resultante.InsertarProduccion(nombre_noterminal, "&");
        }
    } 
    
    return gramatica_resultante;
}


bool DFA::RecorridoDFA(Cadena cadena, std::string estado_actual, int posicion_cadena) {

    //std::cout << "ESTADO: " << estado_actual << ". posicion: " << posicion_cadena << std::endl;

    int tamano = cadena.Longitud_Cadena();
    //std::cout << "Estado: " << estado_actual << ". Posicion: " << posicion_cadena << ". Aceptacion: " << EstadoAceptacion(estado_actual) << std::endl;
    
    if (EstadoAceptacion(estado_actual) && posicion_cadena == tamano) {
        // std::cout << "AUTORIZO: estado: " << estado_actual  << ". posicion_cadena: " << posicion_cadena << ". tamano: " << tamano << std::endl;
        return true; 
    }

    if (posicion_cadena == tamano) {
        // std::cout << "FALSO X " << std::endl;
        return false;
    }

    for (int z = posicion_cadena; z < tamano; z++) {

        Simbolo simbolo_a_buscar = cadena[posicion_cadena];

        int numero_enlaces = 0;
        numero_enlaces = DFA_[estado_actual][simbolo_a_buscar].size(); 
        //std::cout << "numero enlaces: " << numero_enlaces << " en " << estado_actual << std::endl;

        /*if (numero_enlaces == 0) {
            // std::cout << "FALSO XX " << std::endl;
            return false;
        }*/

        for (int l = 0; l < numero_enlaces; l++) { 
            
            int posicion_actual = z + 1;

            std::string siguiente_estado = DFA_[estado_actual].Obtener(simbolo_a_buscar, l);
            
            // std::cout << "estado: " << estado_actual << ". posicion: " << posicion_cadena << ". pasa: " << posicion_actual << ". a: " << siguiente_estado << ". numero enlaces: " << numero_enlaces << ". l: " << l << std::endl; 
            
            if (RecorridoDFA(cadena, siguiente_estado, posicion_actual)) {
                // std::cout << "Se acepta" << std::endl;
                //std::cout << "Acepto, cadena: " << cadena << " :: estado: " << estado_actual << " :: posicion_cadena: " << posicion_cadena << ". enlaces: " << numero_enlaces << ". siguiente estado: " << siguiente_estado << std::endl;
                return true;
            }

        }

        return false;
    }
    return false;
}

