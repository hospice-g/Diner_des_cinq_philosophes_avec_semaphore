#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<time.h>
#include <pthread.h>
#include <sys/types.h>


#define G ((N+i-1)%N)

#define D ( (i+1) % N)

#define N 5
 
sem_t S[N];

sem_t mutex;  

typedef enum { reflechir , faim , manger}etat;
  
  etat Etat[N] = {reflechir,reflechir,reflechir,reflechir,reflechir};

void Test(int i){

      


    if ( (Etat[i] == faim ) && (Etat[G] != manger) && (Etat[D] != manger ) )
    {

        Etat[i] = manger ;
        

       //printf("\n le philosophe [%d] mange\n",i );

       // sem_post(&S[i]);

        
    }


}






void *philosophe(void* num){

    int  i = *(int*)num ;

    int nb = 1 ;

    int duree_msg = rand() % 10 +1 , duree_ref = rand() % 10 + 1 ; //gestion des temps alleatoires

    while(nb){

        nb--;
       printf(" le philosophe [%d] reflechit ..... (%ds)\n\n",i , duree_ref);
        sleep(duree_ref); //reflechir

        printf("\n le philosophe [%d] a faim\n",i ); //faim

       sem_wait(&mutex);

        Etat[i] = faim;

         sem_wait(&S[i]);

       Test(i); // tester s'il peut manger

       printf("\n\033[0;31m le philosophe [%d] mange.\033[0m\n",i ); //mange

        

           sleep(duree_ref);
        printf(" le philosophe [%d] a fini de manger et passe à reflechir.....\n",i );
        Etat[i] = reflechir ;
       sem_post(&S[i]);

       
       sem_post(&mutex);

        
        //sleep(2);

        //sem_wait(&mutex);
          
         //printf(" le philosophe [%d] pense maintenant\n",i );


        // sem_post(&mutex);
         
         
        

       
 
        
    }
}


int main(int argc, char const *argv[]){

int i , numphi[N] = {0,1,2,3,4} ;

pthread_t ph[N];

sem_init(&mutex , 0, 1) ;

for(i = 0; i < N ; i++)
    sem_init(&S[i],0,1);

for(i = 0; i < N ; i++)
 pthread_create(&ph[i], NULL, philosophe, (void *)&numphi[i]);

for(i = 0; i < N ; i++) 
    pthread_join(ph[i], (void *)NULL);



 return 0;
}
