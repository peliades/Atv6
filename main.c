#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int * buffer;

int x = 0;

void * produzir(void * args);

void * consumir (void * args);

int limite = 0;

sem_t bufferComEspaco;

sem_t BufferComDado;

int posicao = 0;

int on = 1;

int tamanhoBuffer = 0;

int main () {
    int numProdutores = 0;

    int numConsumidores = 0;

    

    scanf("%d", &numProdutores);

    scanf("%d", &numConsumidores);

    scanf("%d", &limite);

    scanf("%d", &tamanhoBuffer);

    buffer = (int *)malloc(tamanhoBuffer * sizeof(int));

    pthread_t threads[numConsumidores*numProdutores];

    sem_init(&BufferComDado, 0, 0);

    sem_init(&bufferComEspaco, 0, tamanhoBuffer - 1);

    for (int i = 0; i < numProdutores; i++){

        int * argumentoProd = malloc(sizeof(int));

        * argumentoProd = i;

        if(pthread_create(&threads[i], NULL, &produzir, argumentoProd)!=0){
            printf("Falha ao criar thread\n");
        }
    }

    for (int e = numProdutores; e < (numProdutores + numConsumidores); e++){

        int * argumentoCons = malloc(sizeof(int));

        * argumentoCons = e;

	    if(pthread_create(&threads[e], NULL, &consumir, argumentoCons)!=0){
            printf("Falha ao criar thread\n");
        }
    }

    for (int i = 0; i < (numProdutores + numConsumidores); i++){
            pthread_join(threads[i], NULL);
    }

}


void * produzir(void * argProd){
    int numeroProdutor = *(int*)argProd;

    while(1){
        if (posicao < tamanhoBuffer){
            
            sem_wait(&bufferComEspaco);
            pthread_mutex_lock(&mutex);
            if (x >= limite){
                x = 2*0 + 1;
            }
            else{
                x = 2*x + 1;
                if (x >= limite){
                    x = 2*0 + 1;
                }
            }
            buffer[posicao] = x;
            posicao ++;
            printf("Produtor %d produzindo %d na posicao %d\n",numeroProdutor, x, posicao);
            pthread_mutex_unlock(&mutex);
            sem_post(&BufferComDado);
        }
    }
}

void * consumir (void * argCons){
    int numeroConsumidor = *(int*)argCons;
    int leitura;

    while(1){
        if (posicao >= 0){
            sem_wait(&BufferComDado);
            pthread_mutex_lock(&mutex);
            leitura = buffer[posicao];
            posicao --;
            printf("Consumidor %d consumindo %d na posicao %d\n",numeroConsumidor, leitura, posicao);
            pthread_mutex_unlock(&mutex);
            sem_post(&bufferComEspaco);
        }
    }
}