 // para compilar: gcc EJ1-1.5.c -o EJ1-1.5.exe
// para ejecutar: ./EJ1-1.5.exe
 
 /* Que reconoce:
    Decimal:      signo opcional (+ o -) y despues uno o mas digitos 0-9
    Octal:        la letra 'o' y despues uno o mas digitos 0-7
    Hexadecimal:  la letra 'h' y despues uno o mas digitos 0-9, a-f, A-F
 
  Funcionamiento:
    Se lee la cadena caracter por caracter. Una variable "estado" dice
    "en que parte del token estoy". Cada caracter mueve el estado.
    Cuando aparece '@' (o se termina la cadena) el token termino y se
    mira en que estado quedamos para saber si era valido y de que tipo.
 */
#include <stdio.h>
 
/* Los estados del automata (q0..q6 del diagrama) */
enum {
    Q0,   /* inicio de un token            */
    Q1,   /* se leyo un signo (+ o -)      */
    Q2,   /* decimal valido                */
    Q3,   /* se leyo la 'o'                */
    Q4,   /* octal valido                  */
    Q5,   /* se leyo la 'h'                */
    Q6,   /* hexadecimal valido            */
    ERROR /* caracter no permitido         */
};
 
/* Funciones auxiliares: cada una responde una pregunta sobre un caracter */
int es_digito_octal(char c)   { return c >= '0' && c <= '7'; }
int es_digito_decimal(char c) { return c >= '0' && c <= '9'; }
int es_digito_hexa(char c) {
    return es_digito_decimal(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
 
 //Dado el estado actual y el caracter leido, devuelve el estado siguiente.

int siguiente_estado(int estado, char c)
{
    switch (estado) {
        // Estoy al inicio del token
        case Q0:                                  
            if (c == '+' || c == '-')      return Q1;
            if (es_digito_decimal(c))      return Q2;
            if (c == 'o')                  return Q3;
            if (c == 'h')                  return Q5;
            return ERROR;
        
        //Leí el signo, espero un dígito decimal
        case Q1:                                  
            if (es_digito_decimal(c))      return Q2;
            return ERROR;
        
        //Leo un decimal
        case Q2:                                 
            if (es_digito_decimal(c))      return Q2;
            return ERROR;
        
        //Leí la 'o', espero un dígito octal
        case Q3:                                 
            if (es_digito_octal(c))        return Q4;
            return ERROR;
        
        //Leo un octal
        case Q4:                                 
            if (es_digito_octal(c))        return Q4;
            return ERROR;
        
        //Leí la 'h', espero un dígito hexadecimal
        case Q5:                                  
            if (es_digito_hexa(c))         return Q6;
            return ERROR;
        
        //Leo un hexadecimal
        case Q6:                                  
            if (es_digito_hexa(c))         return Q6;
            return ERROR;
    }
    return ERROR;
}
 
int main(void)
{
    char cadena[1024];
    int i;                     // Posicion dentro de la cadena
    int estado = Q0;           // Estado actual del automata
    int numero_token = 1;      //Que token estoy leyendo (1, 2, 3...)
    int cant_decimales = 0;
    int cant_octales = 0;
    int cant_hexa = 0;
    int hay_error = 0;
 
    printf("Ingrese la cadena: ");
    if (fgets(cadena, sizeof cadena, stdin) == NULL) {
        printf("No se pudo leer la cadena.\n");
        return 1;
    }
 
    //Sacar el salto de linea del final
    for (i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == '\n' || cadena[i] == '\r') {
            cadena[i] = '\0';
            break;
        }
    }
 
    /* Recorrer la cadena. Se llega tambien al '\0' final para cerrar
       el ultimo token, que no termina con '@'. */
    for (i = 0; ; i++) {
        char c = cadena[i];
 
        if (c == '@' || c == '\0') {
            //Termino un token: miro en que estado quede
            if (estado == Q2)      cant_decimales++;
            else if (estado == Q4) cant_octales++;
            else if (estado == Q6) cant_hexa++;
            else {
                /* Cualquier otro estado es invalido: el token estaba
                   incompleto, vacio, o tenia un caracter inválido */
                printf("Error lexico en el token %d.\n", numero_token);
                hay_error = 1;
            }
 
            if (c == '\0') break;   //Se termino la cadena
 
            estado = Q0;            //Empieza un token nuevo
            numero_token++;
        }
        else if (estado != ERROR) {
            estado = siguiente_estado(estado, c);
        }
        /* Si el estado ya es ERROR, se ignora el resto del token
           hasta el proximo '@' */
    }
 
    if (hay_error) {
        printf("La cadena tiene errores lexicos.\n");
        return 1;
    }
 
    printf("Cadena valida. Cantidad de constantes:\n");
    printf("  Decimales:     %d\n", cant_decimales);
    printf("  Octales:       %d\n", cant_octales);
    printf("  Hexadecimales: %d\n", cant_hexa);
    return 0;
}