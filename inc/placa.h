/*********************************************************************************************************************
Copyright 2016-2025, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/

Copyright 2016-2025, Esteban Volentini <evolentini@herrera.unt.edu.ar>

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
*************************************************************************************************/

#ifndef PLACA_H_
#define PLACA_H_

/** @file placa.h
 ** @brief Declaraciones de la capa de abstracción de la placa
 ** @details Define la estructura de datos que contiene todos los recursos funcionales
 ** de hardware de la placa (Zumbador, Teclas y Pantalla) y declara la función de
 ** inicialización.
 **/

/* === Headers files inclusions ============================================ */

#include "digital.h"
#include "screen.h" // ¡Agregamos esto para que reconozca el display_t!

/* === Header for C++ compatibility ======================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public data type declarations ======================================= */

/**
 * @brief Estructura que agrupa todos los recursos de hardware del poncho
 * @details Esta estructura contiene los punteros a los objetos abstractos
 * de la placa. El tipo \c board_t se define como un puntero constante a 
 * esta estructura para protegerla de modificaciones accidentales.
 */
typedef struct board_s {
    digital_output_t buzzer;
    
    digital_input_t tecla_cancel; // Nombres ajustados para coincidir con placa.c
    digital_input_t tecla_accept;       

    digital_input_t tecla_f1;
    digital_input_t tecla_f2;
    digital_input_t tecla_f3;
    digital_input_t tecla_f4;
    
    display_t display;            // ¡Agregamos el descriptor de la pantalla!

} const *board_t;

/* === Public function declarations ======================================== */

/**
 * @brief Inicializa toda la placa y sus periféricos
 * @return board_t Puntero a la estructura con los recursos funcionales
 */
board_t BoardCreate(void);

/* === End of conditional blocks =========================================== */

#ifdef __cplusplus
}
#endif

#endif /* PLACA_H_ */