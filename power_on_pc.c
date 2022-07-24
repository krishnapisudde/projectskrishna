// program to remotely power on pc over the internet using wake_on_LAN protocol
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>

int main()
{
    int i;
    unsigned char toSend[102],mac[6];
    struct sockaddr_in udpClient , udpServer;
    int broadcast =1;

    // udp socket creation
    int udpSocket = socket(AF_INET, SOCK_DGRAM,0);
    // manipulating the socket
    if(setsockopt(udpSocket , SOL_SOCKET,SO_BROADCAST, &broadcast , sizeof broadcast) == -1)
    {
        perror("setsockopt(SO_BROADCAST)");
        exit(EXIT_FAILURE);
    }
    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = INADDR_ANY;
    udpClient.sin_port = 0;

    // binding the socket
    bind(udpSocket,(struct sockaddr*)&udpClient,sizeof(udpClient));
    for (int  i = 0; i < 6; i++)
    {
        toSend[i] = 0xFF;
    }
    // let the MAC address be ab:cd:ef:gh:ij:kl
    mac[0] = 0xab;
    mac[1] = 0xcd;
    mac[2] = 0xef;
    mac[3] = 0xgh;
    mac[4] = 0xij;
    mac[5] = 0xkl;

    for (int  i = 1; i <= 16; i++)
    {
        memcpy(&toSend[i*6],&mac,6*sizeof(unsigned char));
    }
    udpServer.sin_family = AF_INET;
    // broadcast address
    udpServer.sin_addr.s_addr = inet_addr("10.89.255.255");
    udpServer.sin_port = htons(9);

    sendto(udpSocket , &toSend, sizeof(unsigned char)* 102,0,(struct sockaddr*)&udpServer,
                             sizeof(udpServer));

    return 0;
    
    
}






