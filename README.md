## TP Final  - Curso Sistemas Embebidos  2024
# “INTERFACE MODBUS TCP”
#
### Autor:
## Gabriel H. Mossi gmossi@gmail.com
#
#
#
## 1. Selección del proyecto a implementar
#
Los aspectos que se toman para la decisión de proyecto a implementar son los siguientes:
-	Utilidad del proyecto.
-	Tiempo de implementación.
-	Conocimientos técnicos.

Los proyectos para analizar su implementación son los siguientes:
-	Interface Modbus TCP (Manejo de entradas y salidas digitales, entradas analógicas, sensor de temperatura con interface SPI, modulo WiFi para configuración de parámetros).
-	Conversor de Modbus TCP a Modbus RTU (Posibilidad de comunicar hasta 3 dispositivos Modbus RTU).


Se realiza un análisis de pesos por cada proyecto planteado:

|Proyecto|Utilidad del proyecto| |Tiempo de implementación| |Conocimientos técnicos| |Total|
|:----|:----|:----|:----|:----|:----|:----|:----|
| |peso|8|peso|9|peso|10| |
|Interface Modbus TCP|7| |9| |8| |217|
| |56| |81| |80| | |
|Conversor Modbus TCP a RTU|9| |5| |5| |167|
| |72| |45| |50| | |
#

En el contexto industrial, la utilidad del Conversor supera a la de la Interface. Sin embargo, la Interface destaca cuando se trata del tiempo de implementación y los conocimientos técnicos necesarios para su puesta en marcha. Se ha otorgado mayor importancia a los conocimientos técnicos, ya que se requiere una sólida comprensión del protocolo Modbus. Con el Conversor, se profundiza más en este tema, lo que implica un mayor tiempo de implementación.
Para resumir, la Interface sobresale particularmente en términos de tiempo de implementación. Como se mencionó anteriormente, ambos, la Interface y el Conversor, operan con Modbus TCP, un factor crucial en el entorno laboral en el que me desempeño. En una futura actualización de este proyecto, se podría lograr la funcionalidad del Conversor.
#
![image](https://github.com/user-attachments/assets/74aedc48-74ad-44f0-886f-7b5417af8653)

#
La funcionabilidad básica de la Interface, es poder leer entradas analógicas, digitales y valor de temperatura, como activar salidas mediante el uso de registros Modbus. El cliente envía funciones de lectura y escritura de registros mapeados a dichas entradas y salidas. Se utilizará como cliente en la PC Node-Red con nodos de lectura y escritura Modbus TCP.
#
#
#
## 2. Elicitación de requisitos y casos de uso
#
### Tabla comparativa de productos en el mercado:
|Características|Prodigy EG Series|ADAM-6050|
|:----|:----|:----|
|Conectividad|Modbus RTU/TCP| Modbus/SNMP/MQTT |
|Entradas/Salidas|8/14 Analog Inputs - 16/32 3.3V GPIOs|12DI/6DO|
|Configuración|Interface USB|Interface Ethernet|
|Alimentación|12 VDC|10 - 30 VDC|
|Precio|250 usd|200 usd|
|Link|https://numato.com/product/prodigy-eg-series-16-32-channel-usb-rtu-tcp-modbus-gpio-module/|https://www.advantech.com/es-ar/products/a67f7853-013a-4b50-9b20-01798c56b090/adam-6050/mod_b009c4b4-4b7c-4736-b16f-241978245e6a|
#
### Tabla de requisitos:
| Requisitos       | ID  | Descripción                                                                                                                                                          |
|------------------|-----|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Conectividad     | 1.1 | El equipo permitirá comunicación Modbus TCP.                                                                                                                         |
|                  | 1.2 | El equipo permitirá comunicación RS-232.                                                                                                                             |
| Entradas/Salidas | 2.1 | El equipo contará con manejo de entradas digitales.                                                                                                                  |
|                  | 2.2 | El equipo contará con manejo de salidas digitales.                                                                                                                   |
|                  | 2.3 | El equipo contará con manejo de entradas analogicas.                                                                                                                 |
|                  | 2.4 | El equipo contará con sensor de temperatura.                                                                                                                         |
| Modo de trabajo  | 3.1 | El equipo tendrá entradas y salidas mapeandas a registros Modbus.                                                                                                    |
|                  | 3.2 | El equipo  enviará vía RS 232 datos de registros Modbus.                                                                                                            |
| Configuración    | 4.1 | El equipo se podrá configurar vía WiFi.                                                                                                                              |
| Alimentación     | 5.1 | El equipo será alimentado por fuente de 5V.                                                                                                                          |
| Fecha de entrega | 6.1 | El equipo podrá estar finalizado en dos semanas.                                                                                                                     |
| Documentación    | 7.1 | El prototipo debe ir acompañado de una lista de componentes, un diagrama , repositorio de código y una tabla que indica el cumplimiento de requisitos y casos de uso. |
#
### Casos de uso:
#
Caso de uso N°1: “El usuario por medio de una PC tendrá manejo de entradas y salidas”.
|Elementos caso de uso|Definición|
|:----|:----|
|Disparador|El usuario necesita controlar periféricos, como detectar sensores o switches.|
|Precondición|Tener un cliente Modbus TCP como Node-red.|
|Flujo basico|El usuario puede leer o escribir registros que mepean entradas y salidas, de esta manera puede manejar hardware.|
|Flujo alternativo| |

#
Caso de uso N°2: “El usuario por medio de una PC podrá implementar un sistema de control”.
|Elementos caso de uso|Definición|
|:----|:----|
|Disparador|El usuario necesita armar un sistema de control para el llenado de un piscina.|
|Precondición|Tener un cliente Modbus TCP como Node-red con una lógica de prender bomba según estado de sensor de llenado.|
|Flujo basico|El usuario puede leer o escribir registros que mepean entradas y salidas, de esta manera lograr una lógica para controlar un proceso.|
|Flujo alternativo| |

#
Caso de uso N°3: “El usuario envía datos por Modbus TCP y un equipo con puerto serie lo recibe”.
|Elementos caso de uso|Definición|
|:----|:----|
|Disparador|El usuario necesita que un equipo que no cuenta con puerto serie envié datos a uno que solo tiene puedo serie.|
|Precondición|Tener un cliente Modbus TCP como Node-red para envió  de datos.|
|Flujo basico|El usuario puede escribir un registro particular y el dato en el mismo será enviado por UART. Si el dato en el registro cambia, nuevamente se producirá un envió de información.|
|Flujo alternativo| |


