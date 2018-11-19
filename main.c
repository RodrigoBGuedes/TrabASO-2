/*
Alunos: Victor Camargo de Lima Matrícula: 14104029
		Rodrigo Bueno Guedes Matrícula: 15102930

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 4444
#define Nthreads 10
pthread_mutex_t mutex; 
pthread_t thread[Nthreads];



void *func(void *threadid){


   	int *newSocket = (int *)threadid;
   	char Buffer[1025];
   	FILE * fp;
   
   	char server_response[1024] = {0};
   	int str_len = 1000;
   	char str[str_len];


   	while (strcmp("exit\n",Buffer) != 0){

	   	int recebido = recv(*newSocket, Buffer, 1025, 0);
		Buffer[recebido] = '\0';

	   //Criar pasta
	   	if ((strncmp("mkdir ", Buffer, 6)) == 0){
			printf("\n MKDIR %s\n", Buffer);
			pthread_mutex_lock(&mutex);
			//system(Buffer);
			
			fp = popen(Buffer, "r");
			
			pclose(fp);
			fflush(fp);
			pthread_mutex_unlock(&mutex);
		}
			//Remover 
			if ((strncmp("rm -r ", Buffer, 6)) == 0){
			printf("\n RM %s\n", Buffer);
			pthread_mutex_lock(&mutex);
			//system(Buffer);
			
			fp = popen(Buffer, "r");
			
			pclose(fp);
			fflush(fp);
			pthread_mutex_unlock(&mutex);
		}
			//Lista arquivos
			if ((strncmp("ls", Buffer, 2)) == 0){
			printf("\n LS %s\n", Buffer);
			pthread_mutex_lock(&mutex);
			//system(Buffer);
			
			fp = popen(Buffer, "r");
			while (fgets(str, str_len, fp) != NULL){
   				strcat(server_response,str);
   			}
			
			pclose(fp);
			fflush(fp);
			pthread_mutex_unlock(&mutex);
		}

			//Cria arquivo
			if ((strncmp("touch ", Buffer, 6)) == 0){
			printf("\n touch %s\n", Buffer);
			pthread_mutex_lock(&mutex);
			//system(Buffer);
			
			fp = popen(Buffer, "r");
			
			pclose(fp);
			fflush(fp);
			pthread_mutex_unlock(&mutex);
		}

			//Escreve no arquivo
			if ((strncmp("echo ", Buffer, 5)) == 0){
			printf("\n echo %s\n", Buffer);
			pthread_mutex_lock(&mutex);
			//system(Buffer);
			
			fp = popen(Buffer, "r");
			
			pclose(fp);
			fflush(fp);
			pthread_mutex_unlock(&mutex);
		}

			//Mostra o arquivo
			if ((strncmp("cat ", Buffer, 4)) == 0){
			printf("\n cat %s\n", Buffer);
			pthread_mutex_lock(&mutex);
			//system(Buffer);
			
			fp = popen(Buffer, "r");
			while (fgets(str, str_len, fp) != NULL){
   				strcat(server_response,str);
   			}
			
			pclose(fp);
			fflush(fp);
			pthread_mutex_unlock(&mutex);
		}

			//Troca de pasta
			if ((strncmp("cd", Buffer, 2)) == 0){
			printf("\n cd %s\n", Buffer);
			pthread_mutex_lock(&mutex);
			//system(Buffer);
			
			fp = popen(Buffer, "r");
			
			pclose(fp);
			fflush(fp);
			pthread_mutex_unlock(&mutex);
		}

		send(*newSocket, server_response, strlen(server_response), 0);
		
	}
}


int main(){

	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Erro na conexao.\n");
		exit(1);
	}
	printf("[+]Socket do servidor criado.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Erro no bind.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);


	while(1){

		int *newSocket = calloc(sizeof(int),1);

		for (int i = 0; i < Nthreads; i++){		

			if(listen(sockfd, 10) == 0){

			printf("[+]Aguardando....\n");
		}else{
			printf("[-]Erro no bind.\n");
			/* code */
		}
	

		*newSocket = accept(sockfd, (struct sockaddr*)NULL, NULL);
			
		printf("Socket criado: %d\n", *newSocket);
		pthread_create(&thread[i], NULL, func, newSocket);		
		
	}
	}
	return 0;
}





