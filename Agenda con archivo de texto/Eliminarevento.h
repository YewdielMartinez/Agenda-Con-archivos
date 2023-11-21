#ifndef ELIMINAREVENTO_H
#define ELIMINAREVENTO_H
#include <iostream>
#include <conio.h>//Libreria con funciones de control de entrada y salida
#include <string.h> // Libreria para hacer todas mayusculas
#include <ctime>//Libreria para el tiempo
#include <vector>//Libreria para los vectores
#include <chrono>//Libreria que sirve para el tiempo
#include <thread> //Libreria para los hilos
#include <iomanip>//Esta Libreria es para el get time
#include <string>
#include <sstream>
#include <algorithm> 
#include <fstream>
#include "Validaciones.h"
#include "Funcionesarchivo.h"
#include "Declaraciones.h"
#include "MenuPrincipal.h"
void Eliminarevento() {
    CargarDesdeArchivo();
    int indice {0};

    std::cout << "Lista de eventos en tu agenda:" << std::endl;
    for (size_t i = 0; i < agenda.size(); ++i) {
        std::cout << i + 1 << ". " << agenda[i].Nombre_Evento << std::endl;
    }

    std::cout << "Ingrese el índice del evento que desea eliminar: ";
    indice = pedirNumero();
    
    if (indice >= 1 && indice <= agenda.size()) {
        agenda.erase(agenda.begin() + indice - 1);
        std::cout << "Evento eliminado correctamente." << std::endl;

        // Guardar los cambios en el archivo después de eliminar un evento
        GuardarEnArchivo();
    } else if (indice != 0) {
        std::cout << "Índice de evento no válido." << std::endl;
    }
   
    if (validarRespuesta()) {
        MenuPrincipal();
    } else {
        Eliminarevento();
    }
}
#endif