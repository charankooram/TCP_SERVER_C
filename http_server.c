#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 800
#define PORT 8080
#define SA struct sockaddr

void transactions(int connfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;)
    {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains client message
        printf("from client: %s\n", buff);
        //bzero(buff, MAX);
        //n = 0;
        // copy server message in buffer
        //while ((buff[n++] = getchar()) != '\n')
        //    ;
        //char index_page[] = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 48\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1><form action=\"\" method=\"post\"><div class=\"imgcontainer\"><img src=\"img_avatar2.png\" alt=\"Avatar\" class=\"avatar\"></div><div class=\"container\"><label for=\"uname\"><b>Username</b></label><input type=\"text\" placeholder=\"Enter Username\" name=\"uname\" required><label for=\"psw\"><b>Password</b></label><input type=\"password\" placeholder=\"Enter Password\" name=\"psw\" required><button type=\"submit\">Login</button><label><input type=\"checkbox\" checked=\"checked\" name=\"remember\"> Remember me</label></div><div class=\"container\" style=\"background-color:#f1f1f1\"><button type=\"button\" class=\"cancelbtn\">Cancel</button><span class=\"psw\">Forgot <a href=\"#\">password?</a></span></div</form></body></html>";
        char login_page[] = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 1319\nContent-Type: text/html\n\n<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title> Login Page </title><style>Body {font-family: Calibri, Helvetica, sans-serif;background-color: pink;}button {background-color: #4CAF50;width: 100%;color: orange;padding: 15px;margin: 10px 0px;border: none;cursor: pointer;}form {border: 3px solid #f1f1f1;}input[type=text], input[type=password] {width: 100%;margin: 8px 0;padding: 12px 20px;display: inline-block;border: 2px solid green;box-sizing: border-box;}button:hover {opacity: 0.7;}.cancelbtn {width: auto;padding: 10px 18px;margin: 10px 5px;}.container {padding: 25px;background-color: lightblue;}</style></head><body><center> <h1> Student Login Form </h1> </center><form><div class=\"container\"><label>Username : </label><input type=\"text\" placeholder=\"Enter Username\" name=\"username\" required><label>Password : </label><input type=\"password\" placeholder=\"Enter Password\" name=\"password\" required><button type=\"submit\">Login</button><input type=\"checkbox\" checked=\"checked\"> Remember me<button type=\"button\" class=\"cancelbtn\"> Cancel</button>Forgot <a href=\"#\"> password? </a></div></form></body></html>";

        //"<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title> Login Page </title><style>Body {font-family: Calibri, Helvetica, sans-serif;background-color: pink;}button {background-color: #4CAF50;width: 100%;color: orange;padding: 15px;margin: 10px 0px;border: none;cursor: pointer;}form {border: 3px solid #f1f1f1;}input[type=text], input[type=password] {width: 100%;margin: 8px 0;padding: 12px 20px;display: inline-block;border: 2px solid green;box-sizing: border-box;}button:hover {opacity: 0.7;}.cancelbtn {width: auto;padding: 10px 18px;margin: 10px 5px;}.container {padding: 25px;background-color: lightblue;}</style></head><body><center> <h1> Student Login Form </h1> </center><form><div class=\"container\"><label>Username : </label><input type=\"text\" placeholder=\"Enter Username\" name=\"username\" required><label>Password : </label><input type=\"password\" placeholder=\"Enter Password\" name=\"password\" required><button type=\"submit\">Login</button><input type=\"checkbox\" checked=\"checked\"> Remember me<button type=\"button\" class=\"cancelbtn\"> Cancel</button>Forgot <a href=\"#\"> password? </a></div></form></body></html>"
        //"<form action=\"\" method=\"post\"><div class=\"imgcontainer\"><img src=\"img_avatar2.png\" alt=\"Avatar\" class=\"avatar\"></div><div class=\"container\"><label for=\"uname\"><b>Username</b></label><input type=\"text\" placeholder=\"Enter Username\" name=\"uname\" required><label for=\"psw\"><b>Password</b></label><input type=\"password\" placeholder=\"Enter Password\" name=\"psw\" required><button type=\"submit\">Login</button><label><input type=\"checkbox\" checked=\"checked\" name=\"remember\"> Remember me</label></div><div class=\"container\" style=\"background-color:#f1f1f1\"><button type=\"button\" class=\"cancelbtn\">Cancel</button><span class=\"psw\">Forgot <a href=\"#\">password?</a></span></div</form>"

                // and send that buffer to client
        printf("response size: %d\n", sizeof(login_page));
        printf("sending reponse as %s \n", login_page);
        write(connfd, login_page, sizeof(login_page));
        printf("\n\nsent response.. listening again!\n\n");

        // if msg contains exit then server exits
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("server exit\n");
            break;
        }

    }
}

// driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    printf("hello world!\n");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //printf("%s", sockfd);

    // socket create and verification
    if (sockfd == -1)
    {
        printf("socket  creation failed\n");
        exit(0);
    }
    else
        printf("socket successfully created\n");
    bzero(&servaddr, sizeof(servaddr));
    printf("servaddr %s\n", servaddr);
    
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // printf("%s, %s, %s", servaddr.sin_family, servaddr.sin_addr.s_addr, servaddr.sin_port);
   
    // Bind newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0 )
    {
        printf("socket bind failed\n");
        exit(0);
    }
    else
        printf("socket successfully bound\n");

    // Now server is ready to listen and verify
    if ( (listen(sockfd, 5)) != 0) 
    {
        printf("listen failed\n");
        exit(0);
    }
    else
        printf("server listening\n");
    len = sizeof(cli);

    // accept the data packet from client and verify
    connfd = accept(sockfd, (SA*)&cli, &len);
    if ( connfd < 0 )
    {
        printf("server accept failed\n");
        exit(0);
    }
    else
        printf("server accept the client\n");
    
    // function for chatting between client and server
    transactions(connfd);

    // after chatting close the socket
    close(sockfd);

}


