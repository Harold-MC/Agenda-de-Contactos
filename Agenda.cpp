#include "Agenda.h"
#include <fstream>
#include <string>

#define NOMBRE_ARCHIVO "contactos.txt"

Agenda::Agenda(): _primer(NULL) , _ultimo(NULL)
{
}

void Agenda::Agregar(Contacto* contacto)
{
    //Implementar este método 
    /*
        Este método tiene como objetivo agregar un contacto a la agenda.
    */

	if (_ultimo == NULL) {
		_primer = contacto;
		_ultimo = _primer;
	}
	else {
		_ultimo->SetSiguiente(contacto);
		_ultimo = contacto;
	}

	
}

bool Agenda::Eliminar(int indice)
{
    //Implementar este método 
    /*
        Este método tiene como objetivo eliminar un contacto de la agenda.

        Este método recibe parámetro el índice del contacto a eliminar (iniciando en cero).
    */
	if (_primer != NULL) {
		if (indice == 0) {
			Contacto* temporal = _primer;
			_primer = temporal->GetSiguiente();
			temporal->SetSiguiente(NULL);
			delete temporal;

		}
		else {

			Contacto *temp = _primer;

			Contacto* aux1;
			Contacto* aux2;
			for (int i = 0; i < indice - 1; i++) {
				temp = temp->GetSiguiente();

			}

			aux1 = temp;
			aux2 = temp->GetSiguiente()->GetSiguiente();

			temp = temp->GetSiguiente();
			temp->SetSiguiente(NULL);
			delete temp;
			aux1->SetSiguiente(aux2);


		}
	}
    return false;
}

bool Agenda::Modificar(int indice, std::string nombre, std::string telefono)
{
    //Implementar este método 
    /*
        Este método tiene como objetivo modificar un contacto de la agenda.

        Este método recibe parámetros el índice del contacto a eliminar (iniciando en cero) , el nuevo nombre y nuevo teléfono de dicho contacto.
    */

	int i = 0;
	Contacto* contacto = _primer;

	while (contacto != NULL)
	{
		if (i == indice) {
			contacto->SetNombre(nombre);
			contacto->SetTelefono(telefono);
		}
		contacto = contacto->GetSiguiente();
		i++;
	}

    return false;
}

void Agenda::Cargar()
{
    //Terminar la implementación de este método 
    /*
        Este método es el que carga desde un archivo de texto todos los contactos almacenados en el disco duro.
    */
    std::ifstream lector(NOMBRE_ARCHIVO);
	std::string linea;

	/*if (lector.fail()) {
		exit(1);
	}*/

	while (!lector.eof()) {

		std::getline(lector, linea);

		if (linea != "") {

			std::string nombre = "", tel = "";

			nombre = linea.substr(0, linea.find(","));
			tel = linea.substr(linea.find(",") + 1);

			Contacto* siguienteContacto = new Contacto(nombre, tel);

			if (_primer == NULL) {
				
				_primer = siguienteContacto;
				_ultimo = _primer;
			}
			else {
				
				_ultimo->SetSiguiente(siguienteContacto);
				_ultimo = siguienteContacto;
			}
		}
	}

    lector.close();
}

void Agenda::Guardar()
{
    //Terminar la implementación de este método 
    /*
        Este método es el que guarda en un archivo de texto (en el disco duro) todos los contactos.
    */
    std::ofstream escritor(NOMBRE_ARCHIVO);

	Contacto* contactoActual = _primer;

	while (contactoActual != NULL)
	{

		std::string nombre = contactoActual->GetNombre(), telefono = contactoActual->GetTelefono();
			escritor << nombre << "," << telefono;
			contactoActual = contactoActual->GetSiguiente();
	}

    escritor.close();
}
