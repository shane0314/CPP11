#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
#include <cctype>
#include <algorithm>

char client_message[2000];
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * socketThread(void *arg)
{
  int sd = *((int *)arg);

  while( true )
  {
    ssize_t nrecv = recv( sd , client_message , sizeof(client_message)-1 , 0);
    if( nrecv <= 0 )
    {
      //Somebody disconnected , get his details and print  
      struct sockaddr_in address;
      int addrlen = sizeof(address);
      getpeername(sd , (struct sockaddr*)&address , 
          (socklen_t*)&addrlen);   
      printf("Host disconnected , ip %s , port %d \n" ,  
            inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
           
      //Close the socket and mark as 0 in list for reuse  
      close( sd );
      break;
    }
  
    // Send message to the client socket 
    pthread_mutex_lock(&lock);
    client_message[nrecv] = '\0';
    char *message = (char*)malloc(sizeof(client_message)+20);
    strcpy(message,"Hello Client : ");
    strcat(message,client_message);
    strcat(message,"\n");
    strcpy(buffer,message);
    std::transform( buffer, buffer+sizeof(buffer), buffer, ::toupper );
    free(message);
    pthread_mutex_unlock(&lock);
  
    sleep(1);
  
    send( sd,buffer,strlen(buffer)+1,0 );
    printf("%d recv and send: %s\n", sd, buffer );
  } 

  pthread_exit(NULL);

}

int main(){

  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  //Create the socket. 
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  // Configure settings of the server address struct
  // Address family = Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function to use proper byte order 
  serverAddr.sin_port = htons(8888);
  //Set IP address to localhost 
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  //Set all bits of the padding field to 0 
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  //Bind the address struct to the socket 
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  //Listen on the socket, with 40 max connection requests queued 
  if(listen(serverSocket,50)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  pthread_t tid[60];
  int i = 0;
  while(1)
  {
      //Accept call creates a new socket for the incoming connection
      addr_size = sizeof serverStorage;
      newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
      printf("accept new connect: %d\n", newSocket);

      //for each client request creates a thread and assign the client request to it to process
     //so the main thread can entertain next request
      if( pthread_create(&tid[i++], NULL, socketThread, &newSocket) != 0 )
         printf("Failed to create thread\n");
      if( i >= 50)
      {
        i = 0;
        while(i < 50)
        {
          pthread_join(tid[i++],NULL);
        }
        i = 0;
      }
  }

  return 0;
}
