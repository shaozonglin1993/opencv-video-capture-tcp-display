//  Client.cpp 主函数
//  基于OpenCV和Winsock的图像传输（发送）

#include "WinsockMatTransmissionClient.h"  
#include "test.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int client()
{
	WinsockMatTransmissionClient socketMat;
	if (socketMat.socketConnect("127.0.0.1", 6666) < 0) //地址自行设置
	{
		return 0;
	}

//	cv::VideoCapture capture(0);
	
	cv::VideoCapture capture("/home/john/Videos/raw.mp4");
        if (!capture.isOpened())
        {
                printf("capture open failed\n");
                return 0;
        }

	cv::Mat frame;

	while (1)
	{

		if (!capture.isOpened())
			return 0;

		capture >> frame;
		imshow("client", frame);
		cv::waitKey(30);
		if (frame.empty())
			return 0;

		socketMat.transmit(frame);
	}

	socketMat.socketDisconnect();
	return 0;
}
