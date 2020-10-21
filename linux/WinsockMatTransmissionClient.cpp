//  WinsockMatTransmissionClient.cpp
//  基于OpenCV和Winsock的图像传输（发送）


#include "WinsockMatTransmissionClient.h"  
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

WinsockMatTransmissionClient::WinsockMatTransmissionClient(void)
{
}

WinsockMatTransmissionClient::~WinsockMatTransmissionClient(void)
{
}

int WinsockMatTransmissionClient::socketConnect(const char* IP, int PORT)
{
	struct sockaddr_in server_addr;
	int n;

	sockClient = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &server_addr.sin_addr);
	server_addr.sin_port = htons(PORT);

	connect(sockClient,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	return 1;
}


void WinsockMatTransmissionClient::socketDisconnect(void)
{
	close(sockClient);
}

int WinsockMatTransmissionClient::transmit(cv::Mat &image)
{
	if (image.empty())
	{
		printf("empty image\n\n");
		return -1;
	}

	if (image.cols != IMG_WIDTH || image.rows != IMG_HEIGHT || image.type() != CV_8UC3)
	{
		printf("the image must satisfy : cols == IMG_WIDTH（%d）  rows == IMG_HEIGHT（%d） type == CV_8UC3\n\n", IMG_WIDTH, IMG_HEIGHT);
		return -1;
	}

	for (int k = 0; k < 32; k++)
	{
		int num1 = IMG_HEIGHT / 32 * k;
		for (int i = 0; i < IMG_HEIGHT / 32; i++)
		{
			int num2 = i * IMG_WIDTH * 3;
			uchar* ucdata = image.ptr<uchar>(i + num1);
			for (int j = 0; j < IMG_WIDTH * 3; j++)
			{
				data.buf[num2 + j] = ucdata[j];
			}
		}

		if (k == 31)
			data.flag = 2;
		else
			data.flag = 1;

		if (send(sockClient, (char *)(&data), sizeof(data), 0) < 0)
		{
			printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
			return -1;
		}
	}
}
