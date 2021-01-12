# Laboratorio 02

## **Integrantes**
- Fabricio Jose Barrionuevo Paredes
- Lesly Yaneth Mita Yagua

## **Resolucion de Ejercicio**
- Se uso ``execlp``, ``waitpid`` y ``fork`` en el archivo **padre.c** y **hijo.c**
- **execlp**: Para reemplazar el codigo del programa hijo en **padre.c** y **hijo.c**.

- **waitpid**: ya que el padre espera a que el hijo termine de ejecutarse y este hijo esperara al nieto.

- Se imprimio un el pid de cada proceso para verificar que entro al codigo correspondiente.

## **Memoria compartida**

- Se utilizo memoria compartida entre el **hijo.c** y **nieto.c** para ello se creo una estrutura para la comunicacion entre procesos llamada region.

- region tendra un buffer de **hijo.c** contendra las senhales soportadas que compartira al  **nieto.c** .

- Se realizarion pruebas con el proceso SIGSEGV, los procesos soportados entran al **nieto.c** ya que este accede al buffer del **hijo.c**.

- La estructura sigaction tiene diferentes metodos y atributos, uno de estos es el handler del cual se podra optener de la informacion de la senhal (se ejecutara con sigaction).

- En el handler a travez de siginfo (segundo parametro de handler) obtenemos la informacion que se pidio en la practica. 

- Tambien se realizaron pruebas fallidas al final del codigo nieto


## **Ejecucion**
- Para la ejecucion del programa padre que a su vez ejecutara el hijo y este al nieto usar ``make all``.
- Para limpiar el bin usar ``make clear``.

    

