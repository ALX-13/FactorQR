#ifndef __MATRIZ_H__
#define __MATRIZ_H__
#include "Resources.h"
#include "Vector.h"
class Matriz
{
private:
	int n, m;
	double** matriz;
	std::vector<Vector*>* vectores;
public:
	Matriz(int n, int m);
	~Matriz();
	int Obtener_n() { return n; }
	int Obtener_m() { return m; }
	void Insertar_Elemento_Vector(int i, int j, double elemento) {
		vectores->at(j)->Insertar_Elemento(i, elemento);
		matriz[i][j] = elemento;
	}
	void Modificar_Elemento_Vector(int i, int j, double elemento) {
		Insertar_Elemento_Vector(i, j, elemento);
	}
	double Obtener_Elemento_Vector(int i, int j) { return vectores->at(j)->Obtener_Elemento(i); }
	Vector* Obtener_Vector(int j) { return vectores->at(j); }
	void Insertar_Elemento(int i, int j, double elemento) {
		double val = (abs(elemento) < 1e-10 || isnan(elemento)) ? 0 : elemento;
		matriz[i][j] = val;
		vectores->at(j)->Insertar_Elemento(i, val);
	}
	void Modificar_Elemento(int i, int j, double elemento) {
		matriz[i][j] = elemento;
		vectores->at(j)->Modificar_Elemento(i, elemento);
	}
	double Obtener_Elemento(int i, int j) { return matriz[i][j]; }
	void Limpiar_Matriz() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				matriz[i][j] = 0;
				vectores->at(j)->Insertar_Elemento(i, 0);
			}
	}
	void Mostrar_Matriz() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				std::cout << matriz[i][j] << " ";
			std::cout << "\n";
		}
	}
	Matriz* MatrizTranspuesta() {
		Matriz* Transpuesta = new Matriz(m, n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				Transpuesta->Insertar_Elemento(j, i, matriz[i][j]);
		return Transpuesta;
	}
	bool EsSimetrica() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (matriz[i][j] != matriz[j][i])
					return false;
		return true;
	}
	bool EsOrtogonal() {
		Matriz* Trans = MatrizTranspuesta();
		Matriz* Producto = new Matriz(n, n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				double suma = 0;
				for (int k = 0; k < m; k++)
					suma += matriz[i][k] * Trans->Obtener_Elemento(k, j);
				Producto->Insertar_Elemento(i, j, suma);
			}
		delete Trans;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i == j && Producto->Obtener_Elemento(i, j) != 1 ||
					i != j && Producto->Obtener_Elemento(i, j) != 0) {
					delete Producto;
					return false;
				}
		delete Producto;
		return true;
	}
};
Matriz::Matriz(int n, int m) : n(n), m(m) {
	matriz = new double* [n];
	for (int i = 0; i < n; i++)
		matriz[i] = new double[m]();
	vectores = new std::vector<Vector*>();
	for (int i = 0; i < m; i++)
		vectores->push_back(new Vector(n));
}
Matriz::~Matriz() {
	for (int i = 0; i < n; i++) delete[] matriz[i];
	delete[] matriz;
	for (auto v : *vectores) delete v;
	delete vectores;
}
#endif // !__MATRIZ_H__