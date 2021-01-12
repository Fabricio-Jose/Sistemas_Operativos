# Practica N_1
Crear procesos con Memoria compartida para y utilizar las funciones sleep() y kill()
## Ejecución
1. Primero se procederá a abrir un terminal en cada carpeta: consumer y producer
2. Se ejecutará primero en la carpeta "producer" el comando make, y luego en "consumer".
3. Una vez terminado cada proceso, o al  interrumpirlo con ctrl+c, ejecutar make clean en ambos terminales

## Explicación

Primero, tanto en el archivo producer.c como en el consumer lo primero que se trabajó fue cambiar los parámetros de las funciones (como se indica en la práctica, los parámetros para ubicarlos solamente), que ahora sería una estructura. Un vez compartida la memoria para trabajar con una estructura tanto en consumer como en producer, procedemos a llenar el array "buffer[]" que se encuentra en el Struct. Este array guardara los PID's que se vayan creando con las funciones fork's. Para ello se usara como iterador el miembro "in", quien aumentará conforme se llenen los campos en el array buffer. Luego se procedera a dormir el proceso antes de repetir el bucle.

Luego de haber indicado la misma memoria en el consumer, se procede a leer el buffer, a través de un iterador llamado "out". Luego se procede a usar la función Kill, que dependera de la librería "signal.h" para su ejecución.


## Desarrollador

- Barrionuevo Paredes, Fabricio Jose


