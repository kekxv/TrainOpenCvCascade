#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <getopt.h>
#include <dirent.h>
#include <vector>
#include <sys/stat.h>


using namespace cv;
using namespace std;

void putData(const string &file,const string &data){
    auto fp=fopen(file.c_str(),"a+");
    fwrite(data.c_str(),sizeof(char),data.size(),fp);
    fclose(fp);
}

bool GetFileList(const string &basePath, vector<string> &pathList) {
    DIR *dir;
    struct dirent *ptr;
    if ((dir = opendir(basePath.c_str())) == nullptr) {
        return false;
    }

    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
            continue;
        else if (ptr->d_type == 8) {    ///file
            pathList.push_back(basePath + "/" + ptr->d_name);
        } else if (ptr->d_type == 10) {    ///link file
            // printf("d_name:%s/%s\n", basePath, ptr->d_name);
        } else if (ptr->d_type == 4)    ///dir
        {
            GetFileList(basePath + "/" + ptr->d_name, pathList);
        }
    }
    closedir(dir);
    return true;
}

int main(int argc,char *argv[]){
    string file;
    string path;
    string savePath;
    string saveInfoPath;
    int width=0;
    int height=0;
    char ch;
    bool sortFlag = false;

    while((ch = getopt(argc, argv, "p:f:w:h:so:O:")) != EOF)
    {
        switch(ch)
        {
            case 'f':
                file = optarg;
                break;
            case 'p':
                path = optarg;
                break;
            case 'o':
                savePath = optarg;
                break;
            case 'O':
                saveInfoPath = optarg;
                break;
            case 'w':
                width = strtol(optarg,nullptr,10);
                break;
            case 'h':
                height = strtol(optarg,nullptr,10);
                break;
            case 's':
                sortFlag = true;
                break;
            default:
                printf("请传入参数：-p 文件夹 -f 文件 -w 宽度 -h 高度 -s 排序 -o 输出文件");
                return 1;
        }
    }
    if(file.empty() && path.empty()){
        return 1;
    }
    if(width <=0 || height <=0){
        return 2;
    }
    if(path.empty()){
        Mat img = imread(file);
        resize(img,img,Size(width,height));
        imwrite(file,img);
        printf("%d\n",1);
    }else{
        vector<string> fileList;
        vector<Mat> imgList;
        GetFileList(path,fileList);
        for(size_t i=0;i< fileList.size();i++ ){
            auto f = fileList[i];
            Mat img = imread(f);
            resize(img,img,Size(width,height));
            if(sortFlag){
                remove(f.c_str());
                imgList.push_back(img);
            }else{
                imwrite(f,img);
                if(!savePath.empty())
                    putData(savePath,f + " 1 0 0 "+to_string(width)+" "+to_string(height)+"\r\n");
                if(!saveInfoPath.empty())
                    putData(saveInfoPath,f + "\r\n");
            }
        }
        if(sortFlag){
            for(size_t j=0;j<imgList.size();j++){
                Mat img = imgList[j];
                string ex = ".png";
                char _path[256 * 4];
                memset(_path,0x00,sizeof(_path));
                //string newF = path + "/" + to_string(j) + ex;
                sprintf(_path,"%s/%04ld%s",path.c_str(),j,ex.c_str());
                bool flag = imwrite(_path,img);
                if(!savePath.empty())
                    putData(savePath,string(_path) + " 1 0 0 "+to_string(width)+" "+to_string(height)+"\r\n");
                if(!saveInfoPath.empty())
                    putData(saveInfoPath,string(_path) + "\r\n");
            }
        }
        printf("%ld\n",fileList.size());
    }

    return 0;
}
