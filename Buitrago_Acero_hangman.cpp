#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype> 

using namespace std;
const int MAX = 50;
const int MAX_ERROR = 6;
const int NUM_PALABRAS = 10;


const char PALABRAS[NUM_PALABRAS][MAX] = {
    "COLOMBIA", "AHORCADO", "PROGRAMACION", "COMPUTADORA", "GATO",
    "JUEGO", "CASA", "MECATRONICA", "INTELIGENCIA", "CIBERSEGURIDAD"
};

void dibujarAhorcado(int errores) {
    switch(errores) {
        case 0:
            cout << "  +---+\n      |\n      |\n      |\n     ===\n";
            break;
        case 1:
            cout << "  +---+\n  O   |\n      |\n      |\n     ===\n";
            break;
        case 2:
            cout << "  +---+\n  O   |\n  |   |\n      |\n     ===\n";
            break;
        case 3:
            cout << "  +---+\n  O   |\n /|   |\n      |\n     ===\n";
            break;
        case 4:
            cout << "  +---+\n  O   |\n /|\\  |\n      |\n     ===\n";
            break;
        case 5:
            cout << "  +---+\n  O   |\n /|\\  |\n /    |\n     ===\n";
            break;
        case 6:
            cout << "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ===\n";
            break;
    }
}


int main() {
    srand(time(0));
    char opcion[10];  

    do {
        char palabraSecreta[MAX];
        char estadoPalabra[MAX];
        char letrasIntentadas[26];
        int errores = 0, numIntentos = 0;
        bool victoria = false;

        
        int indice = rand() % NUM_PALABRAS;
        int longitud = 0;
        for(int i = 0; PALABRAS[indice][i] != '\0'; i++) {
            palabraSecreta[i] = PALABRAS[indice][i];
            longitud++;
        }
        palabraSecreta[longitud] = '\0';

        
        for(int i = 0; i < longitud; i++) {
            estadoPalabra[i] = '_';
        }
        estadoPalabra[longitud] = '\0';

        cout << "\n================ AHORCADO ================\n";
        cout << "Pista: la palabra comienza con '" << palabraSecreta[0]
             << "' y termina con '" << palabraSecreta[longitud - 1] << "'\n";

       
        do {
            cout << "\nPalabra: ";
            for(int i = 0; i < longitud; i++) cout << estadoPalabra[i] << " ";
            cout << "\nLetras intentadas: ";
            for(int i = 0; i < numIntentos; i++) cout << letrasIntentadas[i] << " ";
            cout << "\nErrores: " << errores << "/" << MAX_ERROR << endl;
            dibujarAhorcado(errores);

            
            char entrada[10];
            bool entradaValida = false;

            do {
                cout << "\nIngresa una letra: ";
                cin.getline(entrada, 10);

                
                if(entrada[0] == '\0') {
                    cout << "Error: entrada vacía.\n";
                    continue;
                }

                
                if(entrada[1] != '\0') {
                    cout << "Error: solo puedes ingresar una letra.\n";
                    continue;
                }

                
                if(!isalpha(entrada[0])) {
                    cout << "Error: solo se permiten letras (A-Z).\n";
                    continue;
                }

                
                char letra = toupper(entrada[0]);

                
                bool repetida = false;
                for(int i = 0; i < numIntentos; i++) {
                    if(letrasIntentadas[i] == letra) {
                        repetida = true;
                        break;
                    }
                }

                if(repetida) {
                    cout << "Ya intentaste esa letra.\n";
                    continue;
                }

                
                letrasIntentadas[numIntentos++] = letra;
                entradaValida = true;

                
                bool acierto = false;
                for(int i = 0; i < longitud; i++) {
                    if(palabraSecreta[i] == letra) {
                        estadoPalabra[i] = letra;
                        acierto = true;
                    }
                }

                if(!acierto) errores++;

            } while(!entradaValida);

            
            bool completa = true;
            for(int i = 0; i < longitud; i++) {
                if(estadoPalabra[i] == '_') {
                    completa = false;
                    break;
                }
            }
            if(completa) victoria = true;

        } while(errores < MAX_ERROR && !victoria);

        
        cout << "\n=========================================\n";
        if(victoria) {
            cout << "Felicidades! Has adivinado la palabra: " << palabraSecreta << endl;
        } else {
            cout << "Has perdido. La palabra era: " << palabraSecreta << endl;
            dibujarAhorcado(6);
        }
        cout << "=========================================\n";

        
        bool respuestaValida = false;
        do {
            cout << "\nDeseas jugar otra vez? (S/N): ";
            cin.getline(opcion, 10);
            if(opcion[0] == '\0') {
                cout << "Entrada vacía. Intenta de nuevo.\n";
                continue;
            }
            opcion[0] = toupper(opcion[0]);
            if(opcion[0] != 'S' && opcion[0] != 'N') {
                cout << "Solo se permite 'S' o 'N'.\n";
                continue;
            }
            respuestaValida = true;
        } while(!respuestaValida);

    } while(opcion[0] == 'S');

    cout << "\nGracias por jugar. ¡Hasta la próxima!\n";
    return 0;
}
