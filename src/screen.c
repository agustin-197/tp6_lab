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

/** @file screen.c
 ** @brief Implementación del controlador de la pantalla de 7 segmentos
 ** @details Controlador totalmente portable, no interactúa con el hardware
 ** directamente, sino a través de callbacks (driver).
 **/

/* === Headers files inclusions ================================================================ */

#include "screen.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

/**
 * @brief Cantidad máxima de pantallas que se pueden instanciar
 */
#define DISPLAY_MAX_INSTANCES 1

/* === Private data type declarations ========================================================== */

/**
 * @brief Estructura interna (oculta) del descriptor de la pantalla
 */
struct display_s {
    uint8_t digits;                 /**< Cantidad de dígitos de la pantalla */
    uint8_t active_digit;           /**< Dígito actualmente encendido en el barrido */
    uint8_t memory[8];              /**< Memoria de video (máscaras de segmentos) */
    struct display_driver_s driver; /**< Copia de los callbacks del hardware */
};

/* === Private function declarations =========================================================== */

/* === Private variable definitions ============================================================ */

/**
 * @brief Tabla de conversión BCD a máscara de 7 segmentos
 */
static const uint8_t IMAGENES[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,              // 0
    SEGMENT_B | SEGMENT_C,                                                              // 1
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,                          // 2
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,                          // 3
    SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,                                      // 4
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,                          // 5
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,              // 6
    SEGMENT_A | SEGMENT_B | SEGMENT_C,                                                  // 7
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,  // 8
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G               // 9
};

/**
 * @brief Asignación de memoria estática para las instancias
 * @details Evitamos el uso de malloc() por seguridad en sistemas embebidos.
 */
static struct display_s instances[DISPLAY_MAX_INSTANCES];

/* === Public variable definition  ============================================================= */

/* === Private function definitions ============================================================ */

/* === Public function implementation ========================================================== */

display_t DisplayCreate(uint8_t digits, display_driver_t driver) {
    display_t display = &instances[0];

    display->digits = digits;
    display->active_digit = digits - 1; // Para que el primer refresco empiece en el dígito 0
    
    display->driver.UpdateDigits = driver->UpdateDigits;
    display->driver.UpdateSegments = driver->UpdateSegments;

    memset(display->memory, 0, sizeof(display->memory));

    display->driver.UpdateSegments(0);
    display->driver.UpdateDigits(0);

    return display;
}

void DisplayWriteBCD(display_t display, uint8_t * number, uint8_