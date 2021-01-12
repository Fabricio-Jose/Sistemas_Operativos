#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> 

int main()
{
    pid_t pidC;
    printf("** proc PID= %d comienza ** \n",getpid());

    pidC = fork();

    if(pidC > 0){           //Se esta ejecutando el padre
        printf("** proc PID= %d comienza Padre_1 ** \n",getpid());
        int wstatus;
        waitpid(-1, & wstatus, 0);
    }
    else if(pidC == 0){     //Se esta ejecutando el hijo
        printf("** proc PID= %d comienza Padre_2** \n",getpid());

        /** lee el codigo del hijo.c */
        execlp ("./bin/hijo","", NULL);
		printf("Si ves esto, no se pudo ejecutar el programa padre\n");
    }
    else{
        //si es -1 es error, el hijo no ha podido ser creado
    }
}
