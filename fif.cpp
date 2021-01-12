#include <iostream>

using namespace std;

void insertar(int datos[],int tiempo[],int l){
    for(int i = 0; i < (l); i++){
        cout << "inserte el tiempo en el proceso [" << datos[i] << "]: ";
        cin >> tiempo[i];

    }
}
void fifo(int datos[],int tiempo[], int l,int hllegada[]){
    int tiempoTotal = 0;
    float tiempoReturn = 0;
    insertar(datos,tiempo, l);
    for(int j = 0;j < l; j++){
        tiempoTotal += tiempo[j];
        tiempoReturn += tiempoTotal;
        cout <<"\n""tiempo TF de["<<datos[j]<<"]: "<<tiempoTotal<<"\t";
    	cout<<"su tiempo TR es: "<<tiempoTotal-hllegada[j] <<endl;
    }
    tiempoReturn = tiempoReturn / l;
    cout<<"\nEl tiempo de las entradas son: "<<tiempoReturn;
    
}

void fifospn(int datos[],int tiempo[], int l,int hllegada[]){
    int tiempoTotal = 0;
    float tiempoReturn = 0;
    insertar(datos,tiempo, l);
    for(int j = 0;j < l; j++){
       tiempoTotal += tiempo[j];
        tiempoReturn += tiempoTotal;
        cout <<"\n""tiempo TF de["<<datos[j]<<"]: "<<tiempoTotal<<"\t";
    	cout<<"su tiempo TR es: "<<tiempoTotal-hllegada[j] <<endl;
	for(int a=2;a<l;a++){
		int aux=0;
			if(tiempo[a]<tiempo[a-1]){
				aux=tiempo[a-1];
				tiempo[a-1]=tiempo[a];
				tiempo[a]=aux;
				aux=hllegada[a-1];
				hllegada[a-1]=hllegada[a];
				hllegada[a]=aux;
				aux=datos[a-1];
				datos[a-1]=datos[a];
				datos[a]=aux;
				int j=a-1;
				int k=a-2;
				while (k>=1){
					if(tiempo[j]<tiempo[k]){
						aux=tiempo[k];
						tiempo[k]=tiempo[j];
						tiempo[j]=aux;
						aux=hllegada[k];
						hllegada[k]=tiempo[j];
						hllegada[j]=aux;
						aux=datos[a-1];
						datos[a-1]=datos[a];
						datos[a]=aux;			
					}
						j--;
						k--;		
				}}
	
	}}
	for (int a=0;a<l;a++){
		int aux=0;
		if(datos[a]<datos[a-1]){
			aux=datos[a-1];
			datos[a-1]=datos[a];
			datos[a]=aux;
			aux=tiempo[a-1];
			tiempo[a-1]=tiempo[a];
			tiempo[a]=aux;
			aux=hllegada[a-1];
			hllegada[a-1]=hllegada[a];
			hllegada[a]=aux;
			int j=a-1;
			int k=a-2;
			while (k>=1){
				if(datos[j]<datos[k]){
					aux=datos[k];
					datos[k]=datos[j];
					datos[j]=aux;				
					aux=tiempo[k];
					tiempo[k]=tiempo[j];
					tiempo[j]=aux;
					aux=hllegada[k];
					hllegada[k]=tiempo[j];
					hllegada[j]=aux;
					}
						j--;
						k--;		
					}}}	
	
    tiempoReturn = tiempoReturn / l;
    cout<<"\nEl tiempo de las entradas son: "<<tiempoReturn;
    
}



void robin(char orden[],int hllegada[], int tservicio[]){
    int q=1;
    int s=0;
    int i;
    int j=-1;
    while(s!=20){
//	if(s==20){break;}
    	if(hllegada[j+1]==s){
            j++;}
        i=j;
        while(i!=-1){
            if(tservicio[i]!=0){
                tservicio[i]=tservicio[i]-q;
                cout<<"el tiempo de servicio es: "<<tservicio[i]<<" en: "<<orden[i]<<endl;
        //		i--;
                s++;
            }
            i--; 
        }
    }}

int main(){
//    int datos[3] = {1,2,3}; int tiempo[3];   int tiempo2[3] = {0,3,6};
          
//  fifo(datos,tiempo,3,tiempo2); fifospn(datos,tiempo,3,tiempo2);

	char orden[4] = {'a','b','c','d'};
	int hllegada[4] = {0,2,4,6};
	int tservicio[4] = {8,6,4,2};
	int prioridad[4]={2,1,2,0};
	/*char orden[5]={'a','b','c','d','e'};
	int hllegada[5]={0,2,5,7,10};
	int tservicio[5]={3,6,4,5,2};
	robin(orden,hllegada,tservicio);*/
	int ts=0;
	int p=0;
	int pmax=2;
	int x;
	for(int i=0;i<4;i++){
		ts=ts+tservicio[i];
	}
	int s=0;
	for (int i=0;i<4;i++){
		if(hllegada[i]==s){
			s=s+tservicio[i];
			x=tservicio[i];
			tservicio[i]=0;
			cout<<"Proceso: "<<orden[i]<<" tiempo en segundos: "<<x<<", su TF es: "<<s<<", y TR es:"<<s-hllegada[i]<<endl;
			p=prioridad[i];
		}
	}if(p+1>pmax){p=0;}else p++;
	while(s<ts){
		for(int j=0;j<4;j++){
			if((tservicio[j]!=0) && (prioridad[j]==p)){
				s=s+tservicio[j];
				x=tservicio[j];
				tservicio[j]=0;
				cout<<"Proceso: "<<orden[j]<<" tiempo en segundos: "<<x<<", su TF es: "<<s<<", y TR es:"<<s-hllegada[j]<<endl;
	//			cout<<"Proceso: "<<orden[j]<<" tiempo en segundos "<<x<<endl;

			}
		}if(p+1>pmax){p=0;}else p++;		
	}

    

    return 0;
}

