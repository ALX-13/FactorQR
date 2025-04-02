#ifndef __MATRIZ_H__
#define __MATRIZ_H__
#include "Resources.h"
#include "Vector.h"
#include <vector>
class Matriz
{
private:
	int n, m;
	double** matriz;
	vector<Vector*>* vectores;
public:
	Matriz(int n, int m);
	~Matriz();
	int Obtener_n();
	int Obtener_m();
	void Insertar_Elemento_Vector(int i, int j, double elemento);
	void Modificar_Elemento_Vector(int i, int j, double elemento);
	double Obtener_Elemento_Vector(int i, int j);
	Vector* Obtener_Vector(int j);
	void Insertar_Elemento(int i, int j, double elemento);
	void Modificar_Elemento(int i, int j, double elemento);
	double Obtener_Elemento(int i, int j);
	void Limpiar_Matriz();
	void Mostrar_Matriz();
	Matriz* MatrizTranspuesta();
	bool EsSimetrica();
	bool EsOrtogonal();
};
Matriz::Matriz(int n, int m) {
	this->n = n;
	this->m = m;
	matriz = new double* [n];

	for (int i = 0; i < n; i++) {
		matriz[i] = new double[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matriz[i][j] = NULL;
		}
	}

	vectores = new vector<Vector*>();

	for (int i = 0; i < m; i++) {
		vectores->push_back(new Vector(n));
	}
}
Matriz::~Matriz() {
	for (int i = 0; i < n; i++) {
		delete[] matriz[i];
	}

	delete[] matriz;
	delete vectores;
}
int Matriz::Obtener_n() {
	return n;
}
int Matriz::Obtener_m() {
	return m;
}
void Matriz::Insertar_Elemento_Vector(int i, int j, double elemento) {
	vectores->at(j)->Insertar_Elemento(i, elemento);
	matriz[i][j] = elemento;

}
void Matriz::Modificar_Elemento_Vector(int i, int j, double elemento) {
	vectores->at(j)->Insertar_Elemento(i, elemento);
	matriz[i][j] = elemento;
}
double Matriz::Obtener_Elemento_Vector(int i, int j) {
	return vectores->at(j)->Obtener_Elemento(i);
}
Vector* Matriz::Obtener_Vector(int j) {
	return vectores->at(j);
}
void Matriz::Insertar_Elemento(int i, int j, double elemento) {
	if (abs(elemento) < 1e-10 || isnan(elemento)) {
		matriz[i][j] = 0;
		vectores->at(j)->Insertar_Elemento(i, 0);
	}
	else {
		matriz[i][j] = elemento;
		vectores->at(j)->Insertar_Elemento(i, elemento);
	}
}
void Matriz::Modificar_Elemento(int i, int j, double elemento) {
	matriz[i][j] = elemento;
	vectores->at(j)->Modificar_Elemento(i, elemento);
}
double Matriz::Obtener_Elemento(int i, int j) {
	return matriz[i][j];
}
void Matriz::Limpiar_Matriz() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matriz[i][j] = NULL;
			vectores->at(i)->Insertar_Elemento(j, NULL);
		}
	}
}
void Matriz::Mostrar_Matriz() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}
Matriz* Matriz::MatrizTranspuesta() {
	Matriz* Transpuesta = new Matriz(m, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			Transpuesta->Insertar_Elemento(j, i, matriz[i][j]);
		}
	}
	return Transpuesta;
}
bool Matriz::EsSimetrica() {
	bool Simetria = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matriz[i][j] != matriz[j][i]) {
				Simetria = false;
			}
		}
	}
	return Simetria;
}
bool Matriz::EsOrtogonal() {
	Matriz* Producto = new Matriz(n, m);

	double Sumatoria;
	for (int i = 0; i < Producto->Obtener_n(); i++) {
		for (int j = 0; j < Producto->Obtener_m(); j++) {
			Sumatoria = 0;
			for (int t = 0; t < Producto->Obtener_m(); t++) {
				Sumatoria += Obtener_Elemento(i, t) * MatrizTranspuesta()->Obtener_Elemento(t, j);
			}
			Producto->Insertar_Elemento(i, j, Sumatoria);
		}
	}

	for (int i = 0; i < Producto->Obtener_n(); i++) {
		for (int j = 0; j < Producto->Obtener_m(); j++) {
			if (i == j) {
				if (Producto->Obtener_Elemento(i, j) == 1) {

				}
				else {
					return false;
				}
			}
		}
	}

	return true;
}
#endif // !__MATRIZ_H__