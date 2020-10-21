//  WinsockMatTransmissionServer.cpp
//  基于OpenCV和Winsock的图像传输（接收）


//  基于OpenCV和Winsock的图像传输（接收）


#include <iostream>
#include "WinsockMatTransmissionServer.h" 
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> 


WinsockMatTransmissionServer::WinsockMatTransmissionServer(void)
{
}


WinsockMatTransmissionServer::~WinsockMatTransmissionServer(void)
{
}


int WinsockMatTransmissionServer::socketConnect(int PORT)
{
	struct sockaddr_in server_addr,client_addr;
	socklen_t cliaddr_len;
	int sockfd;
	char str[INET_ADDRSTRLEN];
	int i,n;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

	listen(sockfd,20);

	cliaddr_len = sizeof(client_addr);
	sockConn = accept(sockfd,(struct sockaddr *)&client_addr,&cliaddr_len);

	printf("Accepting connectionos ...\n");
	int nRecvBuf = 1024 * 1024 * 10;
	setsockopt(sockConn, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	return 1;
}


void WinsockMatTransmissionServer::socketDisconnect(void)
{
	close(sockConn);
}

int WinsockMatTransmissionServer::receive(cv::Mat& image)
{
	cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));

	int needRecv = sizeof(recvbuf);  //28804
	int count = 0;
	extern int errno;

	while (1)
	{
		for (int i = 0; i < 32; i++)
		{
			printf("i = %d\n", i);
			int pos = 0;
			int len0 = 0;

			while (pos < needRecv)
			{
				len0 = recv(sockConn, (char*)(&data) + pos, needRecv - pos, 0);
				if (len0 < 0)
				{
					printf("Server Recieve Data Failed!\n");
					return -1;
				}
				pos += len0;
			}

			count = count + data.flag;

			int num1 = IMG_HEIGHT / 32 * i;
			for (int j = 0; j < IMG_HEIGHT / 32; j++)
			{
				int num2 = j * IMG_WIDTH * 3;
				printf("j+num1 = %d\n", j + num1);
				uchar* ucdata = img.ptr<uchar>(j + num1);
				for (int k = 0; k < IMG_WIDTH * 3; k++)
				{
					ucdata[k] = data.buf[num2 + k];
				}
			}

			if (data.flag == 2)
			{
				if (count == 33)
				{
					image = img;
					return 1;
					count = 0;
				}
				else
				{
					count = 0;
					i = 0;
				}
			}
		}
	}
}
