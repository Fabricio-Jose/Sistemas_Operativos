#include<iostream>
#include<cstdlib>
#include<pthread.h>
using namespace std;
#define NUM_TH 5
void *printhello(void *threadid){
	long tid;
	tid=(long)threadid;
	cout<<"Hola mundo! thread ID, "<<tid*2<<endl;
	
	pthread_exit(NULL);
}
void *rutine2(void *threadid){
	long tid;
	tid=(long)threadid;
	cout<<"Hola mundo! thread ID, "<<tid*5<<endl;

	pthread_exit(NULL);
}
void *produc(void *threadid){
	long tid;
	tid=(long)threadid;
	cout<<"Hola mundo! thread ID, "<<tid<<endl;

	pthread_exit(NULL);
}




int main(){
	pthread_t threads[NUM_TH];
	int rc;
	int i;
	for(i=0;i<NUM_TH;i++){
		cout<<"main():creating thread, "<<i<<endl;
		if(i%2==0){
			rc = pthread_create(& threads[i], NULL, printhello, (void *) i);}
		else{
			rc = pthread_create(& threads[i], NULL, rutine2, (void *) i);
		}
		
	       if(rc){
		       cout<<"error creating thread, "<<rc<<endl;
		       exit (-1);
	       }	
	}
	pthread_exit(NULL);

	/*
	pthread_t threads[NUM_TH];
	int rc;
	int i;

	for(i=0;i<NUM_TH;i++){
		//cout<<"main():creating thread, "<<i<<endl;
		rc = pthread_create(& threads[i], NULL, produc, (void *) i);}
	       if(rc){
		       cout<<"error creating thread, "<<rc<<endl;
		       exit (-1);
	       }	
	}
	pthread_exit(NULL);


	*/

/*	//pthread_t threads[NUM_TH];
	int rc2;
	int i2;
	for(i2=0;i2<NUM_TH;i2++){
		cout<<"main():creating thread, "<<i2<<endl;
		rc2 = pthread_create(& threads[i2], NULL, rutine2, (void *) i2);
	
	       if(rc2){
		       cout<<"error creating thread, "<<rc2<<endl;
		       exit (-1);
	       }	
	}
	pthread_exit(NULL);*/


}
