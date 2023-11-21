#ifndef DECLARACIONES_H
#define DECLARACIONES_H
#include <iostream>
#include <chrono>
#include <vector>



struct Evento{
std::string Nombre_Evento;//Declaracion en la estructura evento el Nombre del evento
std::string Descripcion_Evento;//Declaracion de la descripcion del evento
std::chrono::system_clock::time_point FechaHora_Tiempo;//Declaracion de la fecha y hora como un punto en el tiempo


};
Evento eventof;
const char* format = "%Y-%m-%d %H:%M";//Declaracion del formato para la fecha y hora 
std::string HoraF_TiempoStr;//Declarar como string para leer la hora
//Declaracion de la agenda como un vector
std::vector<Evento> agenda;//Crear el vector para la agenda con la estructura
void MenuPrincipal();
void Agregarevento();
void Modificarevento();
void Veragenda();
void Eliminarevento();
void TiempoRestante();
void CargarDesdeArchivo();
void GuardarEnArchivo();
void MostrarEventosCercanos();
double pedirNumero();
bool validarRespuesta();
double pedirNumeroM();
#endif