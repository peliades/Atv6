# Atv5
## 1) Objetivo do código:

O objetivo do codigo é implementar uma quantidade P + C de threads onde P threads produzem dados com um limite X e os armazenam em um buffer e C threads consomem esses dados e os removem do buffer

## 2) Funcionamento:

Primeiro são lidas as entradas P, C, N e B do usuário onde P = o numero de produtores, C = o numero de consumidores, N =  o numero limite para os dados a ser produzidos e B o tamanho do buffer. Depois são criados os numeros de threads correspondentes a P & C. Ao ser criadas as threads, é passado a elas as funções de produzir caso sejam threads produtoras e de consumir caso sejam threads consumidoras. 

A função de produzir recebe como argumento o numero da thread, em seguida entra em um loop infinito onde espera o semaforo "bufferComEspaco" indicar que ha espaço no buffer para armazenar dados, em seguida, a função ativa uma trava mutex, acessa a variavel global "x" para gerar um dado dada a função f(x) = 2*x + 1, armazena o dado criado pela função f(x) no buffer na posição atual indicada pela variavel global "posicao", aumenta o contador de posição, imprime que esta produzindo indicando o numero da thread, o valor do dado e a posicao no buffer, libera a trava mutex e adiciona 1 ao semaforo "bufferComDado". 

Ja  a função consumir recebe tambem como argumento o numero da thread e entra em um loop infinito, porém não produz nenhum dado, simplesmente espera o semaforo "bufferComDado" sinalizar que ha dados a serem consumidos no Buffer. Depois do sinal do semaforo, a função ativa uma trava mutex dentro da qual lê os dados do buffer na posição atual e decrementa a posição atual por 1. Logo após, imprime que esta consumindo indicando o numero da thread, o valor do dado e a posicao no buffer, libera a trava mutex e decrementa 1 ao semaforo "bufferComEspaco". 


## 3) Makefile

A primeira função do makefile é "make" que cria o arquivo .bin do código main.c, ela inclui consigo "-lpthread" que serve para a utilização de threads e semaforos

A segunda função do makefile é "run" que executa o binario.

A terceira função do makefile é "clean" que deleta o arquivo binario.
