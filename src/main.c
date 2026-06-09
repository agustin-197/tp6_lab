/** @file main.c
 ** @brief Programa de prueba para el barrido de la pantalla de 7 segmentos
 **/

#include "placa.h"
#include "screen.h"

/**
 * @brief Función de retardo muy rudimentaria para la prueba visual
 * @details Utiliza un bucle for para perder ciclos de reloj.
 * No es exacta y solo sirve para esta prueba inicial.
 */
void RetardoBloqueante(uint32_t iteraciones) {
    for (volatile uint32_t i = 0; i < iteraciones; i++) {
        // El modificador 'volatile' evita que el compilador optimice y borre este bucle
    }
}

int main(void) {
    // 1. Inicializar la placa y obtener el puntero a todos los recursos de hardware
    board_t mi_placa = BoardCreate();

    // 2. Preparar un arreglo con los números que queremos mostrar (Ej: 1, 2, 3, 4)
    uint8_t digitos_prueba[] = {1, 2, 3, 4};

    // 3. Escribir el arreglo en la memoria interna del controlador de la pantalla
    DisplayWriteBCD(mi_placa->display, digitos_prueba, 4);

    // 4. Bucle infinito de la aplicación
    while (1) {
        // Ejecutar UN SOLO PASO del barrido de la pantalla
        DisplayRefresh(mi_placa->display);

        // Frenar el microcontrolador un instante para que el ojo humano pueda ver el dígito encendido
        // Si parpadea muy rápido, aumenta este número. Si va demasiado lento, achícalo.
        RetardoBloqueante(3000000);
    }

    return 0;
}