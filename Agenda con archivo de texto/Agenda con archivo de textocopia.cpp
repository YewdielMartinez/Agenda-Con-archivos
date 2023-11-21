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
//Declaracion de las funciones
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
//Declaracion de los datos
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
//Funcion para validar que el numero que vayamos a utilizar sea correcto
double pedirNumero()
{

  double numero{ 0 };
  // Valida que sea un numero, diferente a cero y no contenga nada despues
  do
  {
    if (std::cin >> numero && std::cin.peek() == '\n')
    {
      std::cin.ignore(); // Limpiar el buffer despues de obtener el numero
      return numero;
    }
    else
    {
      // Limpia el cin y sus errores para pedir otra vez el numero
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ingresa solamente un numero valido por favor." << std::endl;
    }
  } while (true);

}
bool validarRespuesta() {
    std::string respuesta;
    std::cout << "Quiere regresar al Menu Principal (SI/NO): ";
    std::cin >> respuesta;

    // Convertir la respuesta a mayúsculas usando std::transform
    std::transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::toupper);

    while (true) {
        if (respuesta == "SI") {
            return true;
        } else if (respuesta == "NO") {
            return false;
        } else {
            std::cout << "Respuesta inválida. Por favor, ingrese 'SI' o 'NO'." << std::endl;
            std::cout << "Quiere regresar al Menu Principal (SI/NO): ";
            std::cin >> respuesta;
            std::transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::toupper);
        }
    }
}
void TiempoRestante() {//Funcion para calcular el tiempo restante para el evento
    Evento eventof;
    auto ahora = std::chrono::system_clock::now();
 
    for(const Evento& eventof : agenda){
       // Considerando el primer evento en la agenda
        auto tiempo_evento = eventof.FechaHora_Tiempo;//Aqui esta el tiempo del evento
        std::chrono::duration<double> tiempo_restante = std::chrono::duration_cast<std::chrono::seconds>(tiempo_evento - ahora);//Aqui se declara el tiempo restante restando el tiempo del evento con el actual
       
             //Aqui hace los calculos para convertir el tiempo de segundos a dias,horas,minutos y segundos
            int dias = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() / 24;
            int horas = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() % 24;
            int minutos = std::chrono::duration_cast<std::chrono::minutes>(tiempo_restante).count() % 60;
            int segundos = std::chrono::duration_cast<std::chrono::seconds>(tiempo_restante).count() % 60;

            std::cout << "Tiempo restante hasta el evento '" << eventof.Nombre_Evento << "': ";//aqui muestra el nombre del evento
                if (dias > 0) {//aqui si los dias son mayores que 0 va a mostrar los dias
                std::cout << dias << " días, ";
                }
                std::cout << horas << " horas, " << minutos << " minutos y " << segundos << " segundos." << std::endl;//Sino va a mostrar horas minutos y segundos
        if(agenda.empty()) {
        std::cout << "No hay eventos en la agenda." << std::endl;
        }
    } 
   

}

void MostrarEventosCercanos() {
    CargarDesdeArchivo(); // Cargar datos desde el archivo antes de mostrar eventos cercanos
    auto ahora = std::chrono::system_clock::now();
    auto dosSemanas = ahora + std::chrono::hours(24 * 14); // Dos semanas desde ahora

    bool hayEventosCercanos = false;

    for (const Evento& eventof : agenda) {
        auto tiempo_evento = eventof.FechaHora_Tiempo;

        if (tiempo_evento >= ahora && tiempo_evento <= dosSemanas) {
            auto tiempo_restante = std::chrono::duration_cast<std::chrono::seconds>(tiempo_evento - ahora);

            int dias = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() / 24;
            int horas = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() % 24;
            int minutos = std::chrono::duration_cast<std::chrono::minutes>(tiempo_restante).count() % 60;
            int segundos = std::chrono::duration_cast<std::chrono::seconds>(tiempo_restante).count() % 60;

            std::cout << "Evento próximo en la agenda: '" << eventof.Nombre_Evento << "' - ";
            if (dias > 0) {
                std::cout << dias << " días, ";
            }
            std::cout << horas << " horas, " << minutos << " minutos y " << segundos << " segundos." << std::endl;
            hayEventosCercanos = true;
        }
    }

    if (!hayEventosCercanos) {
        std::cout << "No hay eventos próximos en las próximas dos semanas." << std::endl;
    }

    GuardarEnArchivo(); // Guardar los cambios en el archivo después de mostrar los eventos cercanos

    if (validarRespuesta()) {
        MenuPrincipal();
    } else {
        MostrarEventosCercanos();
    }
}
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
    std::cout <<"| 6.-  Guardar los datos en el archivo: |"<<std::endl;
    std::cout <<"| 7.-  Salir : |"<<std::endl;
    std::cout <<"-----------------------------------"<<std::endl;
    
    
    std:: cout <<"Digite el numero de la opcion a elegir: ";
    opcion = pedirNumero();//Aqui hace la llamada a la funcion para que pueda validar el numero
    
    do{
     
        switch(opcion){
        case 1:Agregarevento();break;
        case 2:Modificarevento();break;
        case 3:Veragenda();break;
        case 4:Eliminarevento();break;
        case 5:MostrarEventosCercanos();break;
        case 6:GuardarEnArchivo();break;
        case 7: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
        return ;
        break;
        
        default: std:: cout <<"Elige una opcion del 1 al 4";break;

        }   
    } while (opcion!=6);
    
}




void Agregarevento() //Funcion agregar evento
{   
    //Declaracion de variables constantes etc....
    Evento eventof;
    const char* format = "%d/%m/%Y %H:%M";//Declaracion del formato para la fecha
    
    
    std::string HoraF_TiempoStr;//Declarar como string para leer la hora
    //Aqui empieza la funcion
        std::cout<<"----- Bienvenido al menu de agregar un evento -----"<<std::endl;
        //Aqui agregamos el nombre del evento
        std :: cout<<"Escribe el nombre del evento: "<<std::endl;
        std::getline(std::cin ,eventof.Nombre_Evento);
        while(eventof.Nombre_Evento.empty()){
            std::cout << "No puede dejar el espacio vacio" <<std::endl;
            std::cin.ignore();
            std::getline(std::cin ,eventof.Nombre_Evento);
        }
        //Aqui agregamos la descripcion de el evento
        std ::cout <<"Escribe una descripcion del evento "<<std::endl;
        
        std::getline(std::cin, eventof.Descripcion_Evento);
        while(eventof.Descripcion_Evento.empty()){
            std::cout << "No puede dejar el espacio vacio"<<std::endl;
            
            std::getline(std::cin ,eventof.Descripcion_Evento);
        }
        //Aqui agregamos la fecha del evento y la hora 
        do 
        {
                std::cout << "Escribe la Fecha y hora del evento del evento en este formato (Dia/Mes/Año Hora:Minutos): ";
                std::string HoraF_TiempoStr;
                std::getline(std::cin, HoraF_TiempoStr);
                

            try {
                std::tm tm = {};
                std::istringstream timestream(HoraF_TiempoStr);
                timestream >> std::get_time(&tm, format);//Aqui valida que el tiempo que ya esta convertido a tiempo este en el formato correcto 
                if (timestream.fail()) 
                {
                throw std::runtime_error("Formato de fecha y hora  incorrecto(Dia/Mes/Año Hora:Minutos)");
                }
                // Validación para febrero en años bisiestos y no bisiestos
                int year = tm.tm_year + 1900; // tm.tm_year devuelve años desde 1900
                int month = tm.tm_mon + 1; // tm.tm_mon devuelve meses desde 0 (enero)
                int day = tm.tm_mday;

                bool esBisiesto = (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));

                if ((month == 2 && (esBisiesto && day > 29 || !esBisiesto && day > 28)) ||
                (month < 1 || month > 12 || day < 1 || day > 31)) {
                throw std::runtime_error("Fecha inválida para febrero.");
                }
                
                
                eventof.FechaHora_Tiempo = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                // Si llegamos aquí, la hora es válida
                break;
                } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        

        }while(true);

        agenda.push_back(eventof);
    
        std::cout << "Evento agregado correctamente." << std::endl;
        if (validarRespuesta()){
        MenuPrincipal();
        
        }else{
        Agregarevento();
        }


}



void Modificarevento() {
    CargarDesdeArchivo();
    int indice {0};

    std::cout << "Lista de eventos en tu agenda:" << std::endl;
    for (size_t i = 0; i < agenda.size(); ++i) {
        std::cout << i << ". " << agenda[i].Nombre_Evento << std::endl;
    }

    std::cout << "Ingrese el índice del evento que desea modificar: ";
    indice = pedirNumero();

    if (indice >= 0 && static_cast<size_t>(indice) < agenda.size()) {
        Evento& eventof = agenda[indice];

        std::cout << "Ingrese el nuevo nombre del evento: ";
        std::getline(std::cin, eventof.Nombre_Evento);
        while(eventof.Nombre_Evento.empty()){
            std::cout << "No puede dejar el espacio vacio" ;
            std::cin.ignore();
            std::getline(std::cin ,eventof.Nombre_Evento);
        }

        std::cout << "Ingrese la nueva descripción del evento: ";
        std::getline(std::cin, eventof.Descripcion_Evento);
        while(eventof.Descripcion_Evento.empty()){
            std::cout << "No puede dejar el espacio vacio" ;
            std::cin.ignore();
            std::getline(std::cin ,eventof.Descripcion_Evento);
        }

        const char* format = "%d/%m/%Y %H:%M";
        do {
            std::cout << "Ingrese la nueva fecha y hora (Dia/Mes/Año Hora/Minutos): ";
            std::string HoraF_TiempoStr;
            std::getline(std::cin, HoraF_TiempoStr);

            try {
                std::tm tm = {};
                std::istringstream timestream(HoraF_TiempoStr);
                timestream >> std::get_time(&tm, format);

                if (timestream.fail()) {
                    throw std::runtime_error("Formato de hora incorrecto. (Dia/Mes/Año Hora:Minutos)");
                }

                int year = tm.tm_year + 1900;
                int month = tm.tm_mon + 1;
                int day = tm.tm_mday;
                bool esBisiesto = (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));

                if ((month == 2 && (esBisiesto && day > 29 || !esBisiesto && day > 28)) ||
                    (month < 1 || month > 12 || day < 1 || day > 31)) {
                    throw std::runtime_error("Fecha inválida para febrero.");
                }

                eventof.FechaHora_Tiempo = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                break;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (true);

        std::cout << "Evento modificado correctamente." << std::endl;
        GuardarEnArchivo(); // Guardar los cambios en el archivo
    } else if (indice != 0) {
        std::cout << "Índice de evento no válido." << std::endl;
    }

    if (validarRespuesta()) {
        MenuPrincipal();
    } else {
        Modificarevento();
    }
}




void Veragenda() {
    CargarDesdeArchivo(); // Cargar datos desde el archivo antes de mostrar la agenda
    std::cout << "Agenda de Eventos:" << std::endl;

    for (size_t i = 0; i < agenda.size(); ++i) {
        const Evento& eventof = agenda[i];
        std::time_t tiempoEvento = std::chrono::system_clock::to_time_t(eventof.FechaHora_Tiempo);
        std::cout << "Índice: " << i << std::endl;
        std::cout << "Nombre: " << eventof.Nombre_Evento << std::endl;
        std::cout << "Descripción: " << eventof.Descripcion_Evento << std::endl;
        std::cout << "Fecha y hora: " << std::put_time(std::localtime(&tiempoEvento), format) << std::endl;
        std::cout << std::endl;
        TiempoRestante();
    }
    if (validarRespuesta()) {
        MenuPrincipal();
    } else {
        Veragenda();
    }
}


void Eliminarevento() {
    CargarDesdeArchivo();
    int indice {0};

    std::cout << "Lista de eventos en tu agenda:" << std::endl;
    for (size_t i = 0; i < agenda.size(); ++i) {
        std::cout << i << ". " << agenda[i].Nombre_Evento << std::endl;
    }

    std::cout << "Ingrese el índice del evento que desea eliminar: ";
    indice = pedirNumero();
    
    if (indice >= 0 && indice < agenda.size()) {
        agenda.erase(agenda.begin() + indice);
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


int main ()
{
    MenuPrincipal();
    return 0;
}