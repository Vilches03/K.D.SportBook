#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <utility>
#include <fstream>

using namespace std;

vector<pair<string, string>> listadejuegosb() {
    vector<string> equipos = { "ATLETICOS", "CRIOLLOS", "CAPITANES", "LEONES", "PIRATAS", "CANGREJEROS",
                               "GIGANTES", "METS", "SANTEROS", "INDIOS", "OSOS", "VAQUEROS" };

    for (size_t i = 0; i < equipos.size(); i++) {
        size_t j = rand() % equipos.size();
        swap(equipos[i], equipos[j]);
    }

    vector<pair<string, string>> juegos;
    int numerodejuego = 1;
    for (size_t i = 0; i < equipos.size(); i += 2) {
        cout << numerodejuego << ") " << equipos[i] << " VS " << equipos[i + 1] << endl;
        juegos.push_back(make_pair(equipos[i], equipos[i + 1]));
        numerodejuego++;
    }
    return juegos;
}

void guardarhistorial(string equipo1, string equipo2, int elegido, float apuesta, int ganador) {
    ofstream historial("historial.txt", ios::app);
    if (historial.is_open()) {
        historial << "JUEGO: " << equipo1 << " VS " << equipo2 << "\n";

        historial << "APUESTA: ";
        if (elegido == 1) {
            historial << equipo1 << "\n";
        }
        else {
            historial << equipo2 << "\n";
        }

        historial << "CANTIDAD APOSTADA: $" << apuesta << "\n";

        historial << "GANADOR: ";
        if (ganador == 1) {
            historial << equipo1 << "\n";
        }
        else {
            historial << equipo2 << "\n";
        }

        historial << "RESULTADO: ";
        if (ganador == elegido) {
            historial << "GANASTE!\n";
        }
        else {
            historial << "PERDISTE.\n";
        }

        historial << "---------------------------------\n";
        historial.close();
    }
    else {
        cout << "ERROR AL GUARDAR HISTORIAL\n";
    }
}

void mostrarhistorial() {
    ifstream historial("historial.txt");
    if (historial.is_open()) {
        string linea;
        cout << "\n======= HISTORIAL DE APUESTAS =======\n";
        while (getline(historial, linea)) {
            cout << linea << endl;
        }
        historial.close();
    }
    else {
        cout << "NO HAY HISTORIAL\n";
    }
}

int main() {
    srand(time(0));

    int menu, submenu, elegirequipo, juego;
    float dinero = 0, retirar, deposito, apuesta;

    do {
        cout << "\n\n                           K.D. SPORTSBOOK \n";
        cout << "           $$ BIENVENIDOS A LA MEJOR CASA DE APUESTAS $$\n";
        cout << "  **************************************************************** \n";
        cout << "                           MENU PRINCIPAL\n";
        cout << "                           BALANCE $" << dinero << "\n";
        cout << " 1) CUENTA \n";
        cout << " 2) JUEGOS DEL DIA \n";
        cout << " 3) HISTORIAL\n";
        cout << " 4) SALIR\n";
        cin >> menu;

        switch (menu) {
        case 1:
            cout << "\n                       CUENTA\n";
            cout << "BALANCE: $" << dinero << "\n";
            cout << "1) DEPOSITAR\n";
            cout << "2) RETIRAR\n";
            cout << "3) BORRAR HISTORIAL\n";
            cin >> submenu;

            switch (submenu) {
            case 1:
                cout << "CANTIDAD A DEPOSITAR: $";
                cin >> deposito;
                dinero = dinero + deposito;
                break;
            case 2:
                cout << "CANTIDAD A RETIRAR: $";
                cin >> retirar;
                if (retirar > dinero) {
                    cout << "CANTIDAD INSUFICIENTE\n";
                }
                else {
                    dinero = dinero - retirar;
                }
                break;
            case 3: {
                ofstream borrarhistorial("historial.txt", ios::trunc);
                if (borrarhistorial.is_open()) {
                    cout << "\nHISTORIAL BORRADO\n";
                    borrarhistorial.close();
                }
                else {
                    cout << "ERROR AL BORRAR HISTORIAL\n";
                }
                break;
            }
            default:
                cout << "OPCION INVALIDA\n";
                break;
            }
            break;

        case 2:
            cout << "\n                     DEPORTES\n";
            cout << "1) BALONCESTO\n";
            cout << "2) VOLVER AL MENU\n";
            cin >> submenu;

            switch (submenu) {
            case 1: {
                cout << "\nJUEGOS DISPONIBLES\n";
                vector<pair<string, string>> listaguardada = listadejuegosb();

                char letra;
                cout << "\nDESEAS APOSTAR? (Y/N): ";
                cin >> letra;
                letra = toupper(letra);

                if (letra == 'Y') {
                    cout << "\nA QUE JUEGO QUIERES APOSTAR? ";
                    cin >> juego;

                    if (juego >= 1 and juego <= listaguardada.size()) {
                        pair<string, string> juegoelegido = listaguardada[juego - 1];
                        cout << "\n" << juegoelegido.first << " VS " << juegoelegido.second << "\n";

                        cout << "\nA QUE EQUIPO DESEAS APOSTAR?\n";
                        cout << "1) " << juegoelegido.first << "\n";
                        cout << "2) " << juegoelegido.second << "\n";
                        cin >> elegirequipo;

                        if (elegirequipo == 1 or elegirequipo == 2) {
                            cout << "CUANTO DESEAS APOSTAR?: $";
                            cin >> apuesta;

                            if (apuesta > dinero or dinero <= 0) {
                                cout << "\nNO TIENES SUFICIENTE DINERO.\n";
                            }
                            else {
                                dinero = dinero - apuesta;
                                cout << "SUERTE!\n";
                                cin.ignore();
                                cin.get();
                                cout << "3.....\n";
                                cin.ignore();
                                cin.get();
                                cout << "2.....\n";
                                cin.ignore();
                                cin.get();
                                cout << "1.....\n";


                                if (elegirequipo == 1) cout << juegoelegido.first << "!\n";
                                else cout << juegoelegido.second << "!\n";

                                int ganador = rand() % 2 + 1;

                                if (ganador == 1)
                                    cout << "GANADOR: " << juegoelegido.first << endl;
                                else
                                    cout << "GANADOR: " << juegoelegido.second << endl;

                                if (ganador == elegirequipo) {
                                    cout << "\nFELICIDADES! HAS GANADO LA APUESTA!\n";
                                    dinero += apuesta * 2;
                                }
                                else {
                                    cout << "\nHAS PERDIDO LA APUESTA\n";
                                }

                                guardarhistorial(juegoelegido.first, juegoelegido.second, elegirequipo, apuesta, ganador);
                            }
                        }
                        else {
                            cout << "SELECCION INVALIDA\n";
                        }
                    }
                    else {
                        cout << "NUMERO DE JUEGO INVALIDO\n";
                    }
                }
                else if (letra == 'N') {
                    cout << "VOLVIENDO AL MENU PRINCIPAL\n";
                }
                else {
                    cout << "OPCION INVALIDA\n";
                }
                break;
            }
            case 2:
                cout << "VOLVIENDO AL MENU PRINCIPAL\n";
                break;
            default:
                cout << "OPCION INVALIDA\n";
                break;
            }
            break;

        case 3:
            mostrarhistorial();
            break;

        case 4:
            cout << "\nGRACIAS POR USAR K.D. SPORTSBOOK. VUELVA PRONTO\n";
            break;

        default:
            cout << "OPCION INVALIDA\n";
            break;
        }
    } while (menu != 4);

    return 0;
}