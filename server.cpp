//  Server.cpp ������
//  ����OpenCV��Winsock��ͼ���䣨���գ�


#include "WinsockMatTransmissionServer.h"  
#include "test.h"

int server()
{
	WinsockMatTransmissionServer socketMat;
	if (socketMat.socketConnect(6666) < 0)
	{
		return 0;
	}

	cv::Mat image;
	while (1)
	{
		if (socketMat.receive(image) > 0)
		{
			cv::imshow("server", image);
			cv::waitKey(30);
		}
	}

	socketMat.socketDisconnect();
	return 0;
}