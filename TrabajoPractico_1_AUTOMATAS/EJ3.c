// AUTOMATA EJERCICIO 3
// ER: [0-9]+ ([-+*][0-9]+)*

// para compilar: gcc EJ3.c -o EJ3.exe
// para ejecutar: ./EJ3.exe

#include <stdio.h> // para utilizar printf y scanf

int automataEj3(char cadena[]) {
    int estado = 0;
    int i = 0;

    while(cadena[i] != '\0')
    {
        switch (estado)
        {
            case 0:
                if (cadena[i] >= '0' && cadena[i] <= '9')
                    estado = 1;
                else
                    return 0;
                break;

            case 1:
                if(cadena[i] >= '0' && cadena[i] <= '9')
                    estado = 1;
                else if (cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*')
                    estado = 2;
                else
                    return 0;
                break;

            case 2:
                if(cadena[i] >= '0' && cadena[i] <= '9')
                    estado = 1;
                else
                    return 0;
                break;
        }
        i++;
    }
    return estado == 1;
    
}

int resultadoCadena(char cadena[]) {
    int i = 0; // indice que lee cada caracter de la cadena
    int numero = 0; // guarda el numero leido
    int resultado = 0; // guarda la suma/resta acumulada
    char operacion = '+'; // guarda la operacion pendiente
    while(cadena[i] != '\0')
    {
        numero = 0;

        while(cadena[i] >= '0' && cadena[i] <= '9')
        {
            numero = numero * 10 + (cadena[i]-'0');
            i++;
        }

        while(cadena[i] == '*')
        {
            i++;
            int siguiente = 0;
            while(cadena[i] >= '0' && cadena[i] <= '9')
            {
                siguiente = siguiente * 10 + (cadena[i]-'0');
                i++;
            }
            numero = numero * siguiente;
        }

        if(operacion == '+')
            resultado += numero;
        else if (operacion == '-')
            resultado -= numero;
        
        if(cadena[i] != '\0')
        {
            operacion = cadena[i];
            i++;
        }
    }
    return resultado;
}




 int main (){
    char cadena [100];
    int resultado;

    printf("Ingrese expresion: ");
    scanf("%s", cadena);

    if (automataEj3(cadena) == 0) {
        printf ("Cadena invalida");
    }
    else {
        resultado = resultadoCadena(cadena);
        printf("Cadena valida. El resultado de la operacion es: %d", resultado);
    }

}