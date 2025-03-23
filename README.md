# Sistema de Muestreo con Fotodetector

Este proyecto, desarrollado para el laboratorio de física de la Universidad Industrial de Santander (UIS), consiste en un sistema de muestreo que utiliza un riel con servomotor y fotodetectores analógicos conectados a un ESP32 con un sistema de amplificador de instrumentación.

## Contenido

- [Descripción](#descripción)
- [Características](#características)
- [Especificaciones Técnicas](#especificaciones-técnicas)
- [Requisitos](#requisitos)
- [Instalación](#instalación)
- [Uso](#uso)
- [Contribuciones](#contribuciones)
- [Licencia](#licencia)
- [Agradecimientos](#agradecimientos)

## Descripción

El objetivo de este proyecto es desarrollar un sistema de muestreo óptico que permita la detección y medición precisa de señales luminosas. El sistema está compuesto por un riel motorizado controlado por un servomotor, fotodetectores analógicos para la captura de señales ópticas y un microcontrolador ESP32 que procesa y transmite los datos. Además, se incorpora un amplificador de instrumentación para mejorar la calidad de las señales capturadas.

## Características

- **Detección óptica precisa**: Utiliza fotodetectores analógicos para la captura de señales luminosas.
- **Control motorizado**: Implementa un riel con servomotor para el posicionamiento exacto de los sensores.
- **Procesamiento eficiente**: Emplea un ESP32 para el procesamiento y transmisión de datos.
- **Amplificación de señales**: Incorpora un amplificador de instrumentación para mejorar la calidad de las señales detectadas.

## Especificaciones Técnicas

- **Microcontrolador**: ESP32
- **Fotodetectores**: Sensores analógicos optimizados para la detección de luz.
- **Sistema de movimiento**: Riel con servomotor para el posicionamiento de los sensores.
- **Amplificación**: Amplificador de instrumentación para señales de baja amplitud.
- **Comunicación**: Conectividad Wi-Fi y Bluetooth proporcionada por el ESP32.

## Requisitos

### Hardware

- Placa de desarrollo ESP32
- Fotodetectores analógicos
- Servomotor compatible con el riel utilizado
- Amplificador de instrumentación
- Fuente de alimentación adecuada

### Software

- [PlatformIO](https://platformio.org/) o [Arduino IDE](https://www.arduino.cc/en/software)
- Librerías necesarias (detalladas en el archivo `platformio.ini` o en las instrucciones de instalación)

## Instalación

1. **Clonar el repositorio**:

   ```bash
   git clone https://github.com/jcristancho2/photodetector-sampling-system.git
