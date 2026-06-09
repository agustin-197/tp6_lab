/** @file screen.c
 ** @brief Implementación del controlador de la pantalla de 7 segmentos
 ** @details Controlador totalmente portable, no interactúa con el hardware
 ** directamente, sino a través de callbacks (driver).
 **/

#include "screen.h"
#include <string.h>

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

struct display_s {
    uint8_t digits;               // Cantidad de dígitos de la pantalla
    uint8_t active_digit;         // Dígito actualmente encendido en el barrido
    uint8_t memory[8];            // Memoria de video (máscaras de segmentos)
    struct display_driver_s driver; // Copia de los callbacks del hardware
};

static struct display_s instances[1];

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

void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        if (i < display->digits) {
            display->memory[display->digits - 1 - i] = IMAGENES[number[i]];
        }
    }
}

void DisplayRefresh(display_t display) {
    display->driver.UpdateSegments(0);

    display->driver.UpdateDigits(display->active_digit);

    display->driver.UpdateSegments(display->memory[display->active_digit]);

    display->active_digit++;
    if (display->active_digit >= display->digits) {
        display->active_digit = 0;
    }
}

void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t frecuency) {}
void DisplayToggleDots(display_t display, uint8_t from, uint8_t to) {}