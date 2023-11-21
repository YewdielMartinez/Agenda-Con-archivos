#ifndef FUNCIONESARCHIVO_H
#define FUNCIONESARCHIVO_H
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
#include "Declaraciones.h"
#include "TiempoRestante.h"  
void CargarDesdeArchivo() {
    std::ifstream archivo("agenda.txt");
    if (archivo.is_open()) {
        agenda.clear(); // Limpiar el vector antes de cargar los datos desde el archivo
        std::string nombreEvento, descripcionEvento, fechaHoraStr;
        while (std::getline(archivo, nombreEvento) &&
               std::getline(archivo, descripcionEvento) &&
               std::getline(archivo, fechaHoraStr)) {
            Evento evento;
            evento.Nombre_Evento = nombreEvento;
            evento.Descripcion_Evento = descripcionEvento;
            std::tm tm = {};
            std::istringstream fhs(fechaHoraStr);
            fhs >> std::get_time(&tm, format);
            evento.FechaHora_Tiempo = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            agenda.push_back(evento);
        }
        archivo.close();
        std::cout << "Datos cargados correctamente desde el archivo 'agenda.txt'." << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo para cargar los datos." << std::endl;
    }
}
void GuardarEnArchivo() {
    std::ofstream archivo("agenda.txt"); // Abre el archivo en modo escritura

    if (archivo.is_open()) {
        for (const Evento& evento : agenda) {
            archivo << evento.Nombre_Evento << std::endl;
            archivo << evento.Descripcion_Evento << std::endl;
            std::time_t tiempoEvento = std::chrono::system_clock::to_time_t(evento.FechaHora_Tiempo);
            archivo << std::put_time(std::localtime(&tiempoEvento), format) << std::endl;
        }
        archivo.close(); // Cierra el archivo después de escribir los datos
        std::cout << "Datos guardados correctamente en el archivo 'agenda.txt'." << std::endl;

    } else {
        std::cerr << "No se pudo abrir el archivo para guardar los datos." << std::endl;
    }
}
#endif