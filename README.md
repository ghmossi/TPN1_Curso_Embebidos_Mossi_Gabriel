# TP1  - Curso Sistemas Embebidos  - INTERFACE PC

## Gabriel Mossi - gmossi@gmail.com

## Descripción del Proyecto

Para este proyecto se utilizan las entradas analógicas A0 y A1 conectadas a un potenciómetro. Se utiliza el valor entre 0.0 y 1.0 volt que nos da la salida de los conversores y se envía por UART a NODE-RED. También se usa la entrada BOTON USER y la salida LED1, para silumar entrada y salida. 

## Funcionalidades

 **Toma de Datos y Visualización:**
  - Los datos se toman como objetos en NODE-RED y se muestran en dos Gauges.
  - La toma de los datos del ADC y su envío se realiza cada 3 segundos.
  - Desde la UI de NODE-RED, se puede activar por 3 segundos la salida LED de la placa NUCLEO.
  - Cada vez que se presiona el botón de la placa, se puede ver en la UI de NODE-RED un LED de funcionamiento que cambia según el estado del botón.
  - La comunicacion PC y PLACA es via UART usando funciones de escritura y lectura.

## Requisitos

- Placa NUCLEO F429Zi
- Potenciómetros
- NODE-RED

## Uso

- Ajustar el potenciómetro para ver los cambios en los Gauges en la UI de NODE-RED.
- Activar la salida LED desde la UI de NODE-RED.
- Presionar el botón de la placa para ver el cambio en el LED de funcionamiento en la UI de NODE-RED.

## IMAGENES

![Sin título](https://github.com/ghmossi/TP1-Curso-Embebidos/assets/55816661/be99c3bc-06e3-4b13-a09d-c84a4968f94e)
![IMG_20240707_221534_HDR](https://github.com/ghmossi/TP1-Curso-Embebidos/assets/55816661/b516d9ec-77ad-4d99-825a-23944a049741)

---------------------------------------------------------------------------------------------------


# TP2  - Curso Sistemas Embebidos  - INTERFACE PC

## Gabriel Mossi - gmossi@gmail.com

## Descripción del Proyecto

Es la continuación del TP1, donde se agregó un sensor de temperatura spi (MAX6675), se trabajó en forma modular con archivos, se utilizó variables públicas y privadas.
La NUCLEO envía cada determinado tiempo los valores adc0, adc1, temperatura, input0 e input1. Además, envía datos cuando hay un cambio en alguna de sus entradas.
El uso de maquina de estado finita se implemento para el debounce de las señales de entrada.

