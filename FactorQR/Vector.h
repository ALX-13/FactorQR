#include "Resources.h"
#ifndef __VECTOR_H__
#define __VECTOR_H__
class Vector
{
private:
	int n;
	double* vector;
public:
	Vector();
	Vector(int n);
	~Vector();
	int Obtener_n();
	void Insertar_Elemento(int j, double elemento);
	void Modificar_Elemento(int j, double elemento);
	double Obtener_Elemento(int j);
	void Limpiar_Vector();
	void Mostrar_Vector();
};
Vector::Vector() {
	n = NULL;
	vector = nullptr;
}
Vector::Vector(int n) {
	this->n = n;
	vector = new double[n];
	for (int i = 0; i < n; i++) {
		vector[i] = NULL;
	}
}
Vector::~Vector() {
	delete[] vector;
}
int Vector::Obtener_n() {
	return n;
}
void Vector::Insertar_Elemento(int j, double elemento) {
	vector[j] = elemento;
}
void Vector::Modificar_Elemento(int j, double elemento) {
	vector[j] = elemento;
}
double Vector::Obtener_Elemento(int j) {
	return vector[j];
}
void Vector::Limpiar_Vector() {
	for (int i = 0; i < n; i++) {
		vector[i] = NULL;
	}
}
void Vector::Mostrar_Vector() {
	for (int i = 0; i < n; i++) {
		cout << vector[i] << endl;
	}
}
#endif // !__VECTOR_H__