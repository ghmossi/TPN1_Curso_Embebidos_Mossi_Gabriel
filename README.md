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
![IMG_20240707_221534_HDR](https://github.com/user-attachments/assets/b23c060a-47f8-4d7e-b5f7-486f5bf18e76)
![Sin título](https://github.com/user-attachments/assets/4e53e035-91f6-4533-94cc-7089b29705c6)

![Sin título](https://github.com/ghmossi/TP1-Curso-Embebidos/assets/55816661/be99c3bc-06e3-4b13-a09d-c84a4968f94e)
![IMG_20240707_221534_HDR](https://github.com/ghmossi/TP1-Curso-Embebidos/assets/55816661/b516d9ec-77ad-4d99-825a-23944a049741)
