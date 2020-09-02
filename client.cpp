//  Client.cpp ������
//  ����OpenCV��Winsock��ͼ���䣨���ͣ�

#include "WinsockMatTransmissionClient.h"  
#include "test.h"

int client()
{
	WinsockMatTransmissionClient socketMat;
	if (socketMat.socketConnect("127.0.0.1", 6666) < 0) //��ַ��������
	{
		return 0;
	}

	cv::VideoCapture capture(0);
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