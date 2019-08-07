#include <opencv2/opencv.hpp>  
#include <unistd.h>
#include <getopt.h>

using namespace std;
using namespace cv;
 
int main(int argc,char**argv)
{
    char ch;
    string path = "haarcascade_frontalface_alt2.xml";
    while((ch = getopt(argc, argv, "c:")) != EOF){
        switch(ch){
            case 'c':
                path = optarg;
                break;
            default:
                printf("请输入参数。");
                return 1;
        }
    }
	VideoCapture cap(0);    //打开默认摄像头  
	if (!cap.isOpened())
	{
		return -1;
	}
	Mat frame;
	Mat gray;
	//这个分类器是人脸检测所用
	CascadeClassifier cascade;
	
    //训练好的文件名称，放置在可执行文件同目录下  
	cascade.load(path);//感觉用lbpcascade_frontalface效果没有它好，注意哈！要是正脸
    printf("加载成功；请将摄像头对准检测对象！\n");
    while (1)
	{
		cap >> frame;
  
		vector<Rect> faces(0);//建立用于存放人脸的向量容器
		
		cvtColor(frame, gray, COLOR_RGB2GRAY);//测试图像必须为灰度图
		
		equalizeHist(gray, gray); //变换后的图像进行直方图均值化处理  
		//检测人脸
		cascade.detectMultiScale(gray, faces,
			1.1, 4, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT  
			// | CV_HAAR_DO_ROUGH_SEARCH,
			// | CV_HAAR_DO_CANNY_PRUNING,
			//| CV_HAAR_SCALE_IMAGE,
			,Size(30, 30), Size(500, 500));
		for (int i = 0; i < faces.size(); i++)
		{
			printf("x:%3d,y:%3d,w:%3d,h%3d\n",faces[i].x, faces[i].y,faces[i].width,faces[i].height);
			Scalar color = Scalar(255, 0, 255);//所取的颜色任意值
			rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), color, 1, 8);//放入缓存
		}
        if(true){
            imshow("face", frame);
            if(waitKey(200)==27){
                break;
            }
        }
        else
            usleep(200);
	}
 
	return 0;
}
 
