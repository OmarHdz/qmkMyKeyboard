/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define USE_SERIAL

// Mantener la pantalla esclava siempre despierta y sincronizada
#define OLED_TIMEOUT 0

// 1. Decirle fijamente que el lado izquierdo siempre es el maestro
#define MASTER_LEFT

// 2. Prohibir el modo suspensión (para que la esclava jamás apague su pantalla)
#define NO_SUSPEND_POWER_DOWN

// 3. Modo Unicode para Linux
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// 4. Margen de espera de medio segundo para inicialización USB limpia al encender el PC
#define USB_SUSPEND_WAKEUP_DELAY 500
