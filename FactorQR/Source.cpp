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

void delay(const string& texto, int delay_ms = 10) {
    for (char c : texto) {
        cout << c;
        _sleep(delay_ms);
    }
}

void LogoGod() {
    cout << R"( ___________             ___               ________ __________ 
 \_   _____/____   _____/   |_  ___________\_____  \\______   \
  |    __) \__  \ /  ___\   __\/  _ \_  __ \/  / \  \|       _/
  |     \   / __ \\  \___|  | (  <_> )  | \/   \_/.  \    |   
  \___  /  (____  /\___  >__|  \____/|__|  \_____\ \_/____|_  /
      \/        \/     \/                         \__>      \/ 

)" << endl;
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));
    Matriz* A = nullptr, * Q = nullptr, * R = nullptr;
    short opcionUsuario;

    while (true) {
        system("cls");
        Color(hConsole, 11);
        LogoGod();

        struct Opcion {
            int num;
            const char* texto;
        } opciones[] = {
            {1, "Ingresar Matriz\n\n"},
            {2, "Factorizar QR\n\n"},
            {3, "Mostrar A\n\n"},
            {4, "Mostrar QR\n\n"},
            {5, "Salir\n\n"}
        };

        for (auto& op : opciones) {
            cout << " [   " << op.num << "   ]   ";
            delay(op.texto);
        }

        delay(" get option: ");
        cin >> opcionUsuario;
        cout << endl;

        switch (opcionUsuario) {
        case 1: {
            system("cls");
            LogoGod();
            cout << " [  1  ]   "; delay("Automatico\n\n");
            cout << " [  2  ]   "; delay("Manual\n\n");
            delay(" get option: ");
            cin >> opcionUsuario;

            if (opcionUsuario == 2) {
                short orden;
                do {
                    system("cls");
                    LogoGod();
                    cout << " get matrix order (4 <= order <= 10): ";
                    cin >> orden;
                } while (orden < 4 || orden > 10);

                delete A; // evitar fuga si ya había una matriz
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
            else {
                delete A;
                A = MatrizAleatoria();
            }
            break;
        }
        case 2:
            if (A != nullptr) {
                delete Q; delete R;
                Q = Gram_Schmidt(A);
                R = ProductoMatricial(Q->MatrizTranspuesta(), A);
            }
            break;

        case 3:
            cout << " [  Matriz A  ] :" << endl;
            if (A != nullptr)
                A->Mostrar_Matriz();
            else
                cout << "Matriz A no ha sido ingresada.\n";
            break;

        case 4:
            cout << " [  Matriz Q  ] :" << endl;
            if (Q != nullptr)
                Q->Mostrar_Matriz();
            else
                cout << "Matriz Q no disponible.\n";

            cout << endl << " [  Matriz R  ] :" << endl;
            if (R != nullptr)
                R->Mostrar_Matriz();
            else
                cout << "Matriz R no disponible.\n";
            break;

        case 5:
            delete A; delete Q; delete R;
            return 0;

        default:
            cout << "Opción inválida, intente de nuevo.\n";
            break;
        }
        getch();
    }
}

Vector* DiferenciaVectorial(Vector* V, Vector* U) {
	Vector* D = new Vector(V->Obtener_n());
	for (int i = 0, n = V->Obtener_n(); i < n; i++)
		D->Insertar_Elemento(i, V->Obtener_Elemento(i) - U->Obtener_Elemento(i));
	return D;
}

Vector* ProductoEscalarVectorial(double e, Vector* V) {
	Vector* P = new Vector(V->Obtener_n());
	for (int i = 0, n = V->Obtener_n(); i < n; i++)
		P->Insertar_Elemento(i, e * V->Obtener_Elemento(i));
	return P;
}

double MagnitudVectorial(Vector* V) {
	double sum = 0;
	for (int i = 0, n = V->Obtener_n(); i < n; i++) {
		double val = V->Obtener_Elemento(i);
		sum += val * val;
	}
	return sqrt(sum);
}

double ProductoVectorial(Vector* V, Vector* U) {
	double prod = 0;
	for (int i = 0, n = V->Obtener_n(); i < n; i++)
		prod += V->Obtener_Elemento(i) * U->Obtener_Elemento(i);
	return prod;
}

Vector* ProyeccionVectorial(Vector* V, Vector* U) {
	double denom = pow(MagnitudVectorial(U), 2);
	return ProductoEscalarVectorial(ProductoVectorial(V, U) / denom, U);
}

Matriz* Gram_Schmidt(Matriz* A) {
	int n = A->Obtener_n(), m = A->Obtener_m();
	Matriz* U = new Matriz(n, m);
	Matriz* Q = new Matriz(n, m);

	for (int k = 0; k < m; k++) {
		Vector* Diferencia = A->Obtener_Vector(k);
		for (int j = 0; j < k; j++) {
			Vector* Proyeccion = ProyeccionVectorial(A->Obtener_Vector(k), U->Obtener_Vector(j));
			Vector* Temp = DiferenciaVectorial(Diferencia, Proyeccion);
			Diferencia = Temp;
			delete Proyeccion;
		}
		for (int i = 0; i < n; i++)
			U->Insertar_Elemento(i, k, Diferencia->Obtener_Elemento(i));
		if (k > 0) delete Diferencia;
	}

	for (int j = 0; j < m; j++) {
		double escalar = 1 / MagnitudVectorial(U->Obtener_Vector(j));
		Vector* v = ProductoEscalarVectorial(escalar, U->Obtener_Vector(j));
		for (int i = 0; i < n; i++)
			Q->Insertar_Elemento(i, j, v->Obtener_Elemento(i));
		delete v;
	}

	delete U;
	return Q;
}

Matriz* ProductoMatricial(Matriz* A, Matriz* B) {
	int n = A->Obtener_n(), m = B->Obtener_m(), p = A->Obtener_m();
	Matriz* Producto = new Matriz(n, m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			double sum = 0;
			for (int t = 0; t < p; t++)
				sum += A->Obtener_Elemento(i, t) * B->Obtener_Elemento(t, j);
			Producto->Insertar_Elemento(i, j, sum);
		}
	return Producto;
}

Matriz* MatrizAleatoria(int orden) {
	Matriz* A = new Matriz(orden, orden);
	for (int i = 0; i < orden; ++i)
		for (int j = i; j < orden; ++j) {
			int val = 1 + rand() % 9;
			A->Insertar_Elemento(i, j, val);
			A->Insertar_Elemento(j, i, val);
		}
	return A;
}