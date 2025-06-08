#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Resources.h"

class Vector {
private:
    std::vector<double> datos;

public:
    explicit Vector(int n) : datos(n, 0.0) {}

    int Obtener_n() const { return datos.size(); }

    void Insertar_Elemento(int j, double elemento) {
        if (j < 0 || j >= Obtener_n()) throw std::out_of_range("Índice fuera de rango");
        datos[j] = elemento;
    }

    void Modificar_Elemento(int j, double elemento) {
        Insertar_Elemento(j, elemento);  // mismo comportamiento que Insertar
    }

    double Obtener_Elemento(int j) const {
        if (j < 0 || j >= Obtener_n()) throw std::out_of_range("Índice fuera de rango");
        return datos[j];
    }

    void Limpiar_Vector() { std::fill(datos.begin(), datos.end(), 0.0); }

    void Mostrar_Vector() const {
        for (double val : datos)
            std::cout << val << "\n";
    }
};
#endif // __VECTOR_H__