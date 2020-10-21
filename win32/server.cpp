//  Server.cpp 主函数
//  基于OpenCV和Winsock的图像传输（接收）


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