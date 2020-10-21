//  WinsockMatTransmissionClient.h
//  ����OpenCV��Winsock��ͼ���䣨���ͣ�


#ifndef __WINSOCKMATTRANSMISSIONCLIENT_H__  
#define __WINSOCKMATTRANSMISSIONCLIENT_H__  
#include <opencv2/opencv.hpp>  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/core/core.hpp"  
#include <stdio.h>  



//������ͼ��Ĭ�ϴ�СΪ 640*480�����޸�  
#define IMG_WIDTH 1280   // �贫��ͼ��Ŀ�  
#define IMG_HEIGHT 676  // �贫��ͼ��ĸ�  
//Ĭ�ϸ�ʽΪCV_8UC3  
#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/32  

struct sentbuf
{
	char buf[BUFFER_SIZE];
	int flag;
};

class WinsockMatTransmissionClient
{
public:
	WinsockMatTransmissionClient(void);
	~WinsockMatTransmissionClient(void);

private:
	int sockClient;
	struct sentbuf data;

public:

	// ��socket����  
	// params : IP      ��������ip��ַ  
	//          PORT    ����˿�  
	// return : -1      ����ʧ��  
	//          1       ���ӳɹ�  
	int socketConnect(const char* IP, int PORT);


	// ����ͼ��  
	// params : image ������ͼ��  
	// return : -1      ����ʧ��  
	//          1       ����ɹ�  
	int transmit(cv::Mat &image);


	// �Ͽ�socket����  
	void socketDisconnect(void);
};

#endif  
