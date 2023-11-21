#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
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
#include "Agregarevento.h"
#include "Validaciones.h"
#include "Eliminarevento.h"
#include "Funcionesarchivo.h"
#include "Declaraciones.h"
#include "TiempoRestante.h"
#include "Veragenda.h"
//Declaracion de las funciones

void MenuPrincipal()//Esta funcion es el menu principal del programa
{
   CargarDesdeArchivo();
   int opcion {0};
    std::cout <<"-----------------------------------"<<std::endl;
    std::cout <<"| 1.- Agregar Evento: |"<<std::endl;
    std :: cout <<"| 2.- Modificar Evento: |"<<std::endl;
    std :: cout <<"| 3.- Ver agenda: |"<<std::endl;
    std :: cout <<"| 4.- Eliminar Evento: |"<<std::endl;
    std::cout <<"| 5.-  Eventos mas cercanos : |"<<std::endl;
    std::cout <<"| 6.-  Salir: |"<<std::endl;
    std::cout <<"-----------------------------------"<<std::endl;
    
    
    std:: cout <<"Digite el numero de la opcion a elegir: ";
    opcion = pedirNumeroM();//Aqui hace la llamada a la funcion para que pueda validar el numero
    
    do{
     
        switch(opcion){
        case 1:Agregarevento();
        std::cin.ignore();
        break;
        case 2:Modificarevento();break;
        case 3:Veragenda();break;
        case 4:Eliminarevento();break;
        case 5:MostrarEventosCercanos();break;
        case 6: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
        cerrarPrograma();
        break;
        
        default: std:: cout <<"Elige una opcion del 1 al 6";break;

        }   
    } while (opcion!=6);
    
}
#endif