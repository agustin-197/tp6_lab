/*********************************************************************************************************************
Copyright 2016-2025, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/

Copyright 2026, Gerardo Agustín Díaz <agustin041097@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file main.c
 ** @brief Programa de prueba para el barrido de la pantalla de 7 segmentos
 ** @details Archivo principal de la aplicación que inicializa el hardware y ejecuta
 ** un bucle infinito para validar el funcionamiento del display multiplexado.
 **/

/* === Headers files inclusions ================================================================ */

#include "placa.h"
#include "screen.h"

/* === Macros definitions ====================================================================== */

/**
 * @brief Cantidad de ciclos de reloj para el retardo
 * @details Este valor permite ajustar la velocidad a la que se refresca la pantalla
 * durante la prueba visual.
 */
#define CICLOS_RETARDO 3000000

/* === Private data type declarations ========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Función de retardo muy rudimentaria para la prueba visual
 * @details Utiliza un bucle for para perder ciclos de reloj.
 * No es exacta y solo sirve para esta prueba inicial.
 * @param[in] iteraciones Cantidad de iteraciones del bucle for para generar la demora.
 */
void RetardoBloqueante(uint32_t iteraciones);

/* === Private variable definitions ============================================================ */

/* === Public variable definition  ============================================================= */

/* === Private function definitions ============================================================ */

void RetardoBloqueante(uint32_t iteraciones) {
    for (volatile uint32_t i = 0; i < iteraciones; i++) {
        // El modificador 'volatile' evita que el compilador optimice y borre este bucle
    }
}

/* === Public function implementation ========================================================== */

/**
 * @brief Función principal del programa
 * @details Inicializa la placa EDU-CIAA, configura la pantalla y el zumbador,
 * y ejecuta el bucle principal de barrido y prueba.
 * @return int Retorna 0 al finalizar la ejecución (nunca debería ocurrir en un sistema embebido).
 */
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

        // Hacemos parpadear el "zumbador" (LED Azul)
        DigitalOutputToggle(mi_placa->buzzer);

        // Frenar el microcontrolador un instante para que el ojo humano pueda ver el dígito encendido
        RetardoBloqueante(CICLOS_RETARDO);
    }

    return 0;
}

/* === End of documentation ==================================================================== */