#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

void salto( jmp_buf saltimbanqui, int v )
{
   longjmp( saltimbanqui, v );
}

int main()
{   
   int valor;
   jmp_buf entorno;

   printf( "longjmp y setjmp son una forma de simular el \'goto\'\n\n" );

   valor = setjmp( entorno );   /* Volveremos aqu&iexcl; */
   if( valor != 0 ) 
   {
      printf( "Longjmp con el valor: %d\n", valor );
      exit( valor );
   }

   printf( "Vamos a saltar ... \n" );
   salto( entorno, 1 );         /* Salta al momento de setjmp() */

   return 0;
}
