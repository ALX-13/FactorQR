/*
Proyecto:Factorizacion QR
Fecha:11/10/23
Autor(es):Leonardo Bravo, Renzo Julca, Sebastian Mendoza
*/

#include "Matriz.h"

#define Color SetConsoleTextAttribute

Vector* DiferenciaVectorial(Vector* V, Vector* U);
Vector* ProductoEscalarVectorial(double Escalar, Vector* V);
double MagnitudVectorial(Vector* V);
double ProductoVectorial(Vector* V, Vector* U);
Vector* ProyeccionVectorial(Vector* V, Vector* U);
Matriz* Gram_Schmidt(Matriz* A);
Matriz* ProductoMatricial(Matriz* A, Matriz* B);
Matriz* MatrizAleatoria(int orden = 4 + rand() % +7);

void LogoGod() {
	cout << " ___________              __               ________ __________ " << endl;
	cout << " " << char(92) << "_   _____/____    _____/  |_  ___________" << char(92) << "_____  " << char(92) << char(92) << "______   " << char(92) << endl;
	cout << "  |    __) " << char(92) << "__  " << char(92) << " _/ ___" << char(92) << "   __" << char(92) << "/  _ " << char(92) << "_  __ " << char(92) << "/  / " << char(92) << "  " << char(92) << "|       _/" << endl;
	cout << "  |     " << char(92) << "   / __ " << char(92) << char(92) << "  " << char(92) << "___|  | (  <_> )  | " << char(92) << "/   " << char(92) << "_/.  " << char(92) << "    |   " << char(92) << endl;
	cout << "  " << char(92) << "___  /  (____  /" << char(92) << "___  >__|  " << char(92) << "____/|__|  " << char(92) << "_____" << char(92) << " " << char(92) << "_/____|_  /" << endl;
	cout << "      " << char(92) << "/        " << char(92) << "/     " << char(92) << "/                         " << char(92) << "__>      " << char(92) << "/ " << endl << endl;
}
int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	Matriz* A = nullptr, * Q = nullptr, * R = nullptr;
	short opcionUsuario;
	string Message;

	while (true) {
		system("cls");
		Color(hConsole, 11);
		LogoGod();
		cout << " [   1   ]   "; Message = "Ingresar Matriz\n\n";
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
			cout << i.operator*(); _sleep(100 / 10);
		}
		cout << " [   2   ]   "; Message = "Factorizar QR\n\n";
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
			cout << i.operator*(); _sleep(100 / 10);
		}
		cout << " [   3   ]   "; Message = "Mostrar A\n\n";
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
			cout << i.operator*(); _sleep(100 / 10);
		}
		cout << " [   4   ]   "; Message = "Mostrar QR\n\n";
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
			cout << i.operator*(); _sleep(100 / 10);
		}
		cout << " [   5   ]   "; Message = "Salir\n\n";
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
			cout << i.operator*(); _sleep(100 / 10);
		}

		Message = " get option: ";
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
			cout << i.operator*(); _sleep(100 / 10);
		}

		cin >> opcionUsuario;
		cout << endl;
		switch (opcionUsuario) {
		case 1:
			system("cls");
			LogoGod();
			cout << " [  1  ]   "; Message = "Automatico\n\n";
			for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
				cout << i.operator*(); _sleep(100 / 10);
			}
			cout << " [  2  ]   "; Message = "Manual\n\n";
			for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
				cout << i.operator*(); _sleep(100 / 10);
			}

			Message = " get option: ";
			for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
				cout << i.operator*(); _sleep(100 / 10);
			}
			cin >> opcionUsuario;
			if (opcionUsuario == 2) {
				short orden;
				do {
					system("cls");
					LogoGod();
					cout << " get matrix order (4 <= order <= 10): ";
					cin >> orden;
				} while (orden < 4 || orden > 10);
				A = new Matriz(orden, orden);

				int valor;
				for (int m = 0; m < orden; m++) {
					for (int n = 0; n < orden; n++) {
						cout << " [  A(" << m + 1 << "x" << n + 1 << ")  ]  : ";
						cin >> valor;
						A->Insertar_Elemento(m, n, valor);
					}
				}
			}
			else
				A = MatrizAleatoria();
			break;
		case 2:
			Q = Gram_Schmidt(A);
			R = ProductoMatricial(Gram_Schmidt(A)->MatrizTranspuesta(), A);
			break;
		case 3:
			cout << " [  Matriz A  ] :" << endl;
			if (A != nullptr)
				A->Mostrar_Matriz();
			break;
		case 4:
			cout << " [  Matriz Q  ] :" << endl;
			if (Q != nullptr)
				Q->Mostrar_Matriz();
			cout << endl;
			cout << " [  Matriz R  ] :" << endl;
			if (R != nullptr)
				R->Mostrar_Matriz();
			break;
		case 5:
			return false;
			break;
		default:
			break;
		}
		getch();
	}

	delete A;
	delete Q;
	delete R;
	A = nullptr;
	Q = nullptr;
	R = nullptr;
	return 0;
}

Vector* DiferenciaVectorial(Vector* V, Vector* U) {
	Vector* Diferencia = new Vector(V->Obtener_n());

	for (int i = 0; i < V->Obtener_n(); i++) {
		Diferencia->Insertar_Elemento(i, V->Obtener_Elemento(i) - U->Obtener_Elemento(i));
	}

	return Diferencia;
}

Vector* ProductoEscalarVectorial(double Escalar, Vector* V) {
	Vector* Producto = new Vector(V->Obtener_n());

	for (int i = 0; i < V->Obtener_n(); i++) {
		Producto->Insertar_Elemento(i, Escalar * V->Obtener_Elemento(i));
	}

	return Producto;
}

double MagnitudVectorial(Vector* V) {
	double Magnitud = 0;

	for (int i = 0; i < V->Obtener_n(); i++) {
		Magnitud += pow(V->Obtener_Elemento(i), 2);
	}

	Magnitud = sqrt(Magnitud);

	return Magnitud;
}

double ProductoVectorial(Vector* V, Vector* U) {
	double Producto = 0;

	for (int i = 0; i < V->Obtener_n(); i++) {
		Producto += V->Obtener_Elemento(i) * U->Obtener_Elemento(i);
	}

	return Producto;
}

Vector* ProyeccionVectorial(Vector* V, Vector* U) {
	Vector* Proyeccion = new Vector(V->Obtener_n());

	Proyeccion = ProductoEscalarVectorial(ProductoVectorial(V, U) / pow(MagnitudVectorial(U), 2), U);

	return Proyeccion;
}

Matriz* Gram_Schmidt(Matriz* A) {
	Matriz* U = new Matriz(A->Obtener_n(), A->Obtener_m());
	Matriz* Q = new Matriz(U->Obtener_n(), U->Obtener_m());

	Vector* Proyeccion = new Vector(U->Obtener_n());
	Vector* Diferencia = new Vector(U->Obtener_n());

	for (int k = 0; k < U->Obtener_m(); k++) {
		Diferencia = A->Obtener_Vector(k);
		for (int j = 0; j < k; j++) {
			Proyeccion = ProyeccionVectorial(A->Obtener_Vector(k), U->Obtener_Vector(j));
			Diferencia = DiferenciaVectorial(Diferencia, Proyeccion);
		}

		for (int i = 0; i < U->Obtener_n(); i++) {
			U->Insertar_Elemento(i, k, Diferencia->Obtener_Elemento(i));
		}
	}

	double Escalar;
	for (int j = 0; j < Q->Obtener_m(); j++) {
		for (int i = 0; i < Q->Obtener_n(); i++) {
			Escalar = 1 / MagnitudVectorial(U->Obtener_Vector(j));
			Q->Insertar_Elemento(i, j, ProductoEscalarVectorial(Escalar, U->Obtener_Vector(j))->Obtener_Elemento(i));
		}
	}

	return Q;
}

Matriz* ProductoMatricial(Matriz* A, Matriz* B) {
	Matriz* Producto = new Matriz(A->Obtener_n(), B->Obtener_m());

	double Sumatoria;
	for (int i = 0; i < Producto->Obtener_n(); i++) {
		for (int j = 0; j < Producto->Obtener_m(); j++) {
			Sumatoria = 0;
			for (int t = 0; t < Producto->Obtener_m(); t++) {
				Sumatoria += A->Obtener_Elemento(i, t) * B->Obtener_Elemento(t, j);
			}
			Producto->Insertar_Elemento(i, j, Sumatoria);
		}
	}

	return Producto;
}

Matriz* MatrizAleatoria(int orden) {
	int valor = 0;
	Matriz* A = new Matriz(orden, orden);
	for (int m = 0; m < orden; m++) {
		for (int n = 0; n < orden; n++) {
			valor = 1 + rand() % +9;
			A->Insertar_Elemento(m, n, valor);
			A->Insertar_Elemento(n, m, valor);
		}
	}
	return A;
}