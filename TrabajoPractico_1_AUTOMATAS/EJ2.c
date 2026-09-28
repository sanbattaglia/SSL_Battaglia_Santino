// AUTOMATA EJERCICIO 2
// para compilar: gcc EJ2.c -o EJ2.exe
// para ejecutar: .\EJ2.exe

#include <stdio.h> // para utilizar printf y scanf
#include <string.h> // para utilizar strlen

int automataEj2(char caracter, int *numero){
    int estado = 0;

    switch(estado) {
        case 0:
            if(caracter == '0'){
                *numero = 0;
                estado = 1;
            }
            else if(caracter == '1'){
                *numero = 1;
                estado = 2;
            }
            else if(caracter == '2'){
                *numero = 2;
                estado = 3;
            }
            else if(caracter == '3'){
                *numero = 3;
                estado = 4;
            }
            else if(caracter == '4'){
                *numero = 4;
                estado = 5;
            }
            else if(caracter == '5'){
                *numero = 5;
                estado = 6;
            }
            else if(caracter == '6'){
                *numero = 6;
                estado = 7;
            }
            else if(caracter == '7'){
                *numero = 7;
                estado = 8;
            }
            else if(caracter == '8'){
                *numero = 8;
                estado = 9;
            }
            else if(caracter == '9'){
                *numero = 9;
                estado = 10;
            }
            else
                return 0;
    }

    return 1;
}

int main (){
    char cadena[100];
    int numero;
    printf("Ingrese caracter numerico: ");
    scanf("%s", cadena);
    if (strlen(cadena) != 1)
        printf("Cadena invalida");
    else if (automataEj2(cadena[0], &numero))
        printf("Caracter valido: %d", numero);
    else
        printf("Caracter invalido");
    return 0;
}