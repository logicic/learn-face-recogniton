#include <opencv2/opencv.hpp>
#include<opencv2/dnn.hpp>
#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const string FILEPATH = "./lfw";

void recognize_face(Mat& face, Net net, vector<float> &fv);
float compare(vector<float> &fv1, vector<float> &fv2);
vector<string> find_file(string path);

int main(int argc, char** argv) {
	string facenet_model = "./model/nn4.small2.v1.t7";
    string pb_model = "./model/models/opencv_face_detector_uint8.pb";
    string pb_txt = "./model/models/opencv_face_detector.pbtxt";
    // 载入模型
    Net net = readNetFromTensorflow(pb_model, pb_txt);   //人脸检测模型
    Net face_net = readNetFromTorch(facenet_model);      //人脸识别模型
    // 设置计算后台
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);

    face_net.setPreferableBackend(DNN_BACKEND_OPENCV);
    face_net.setPreferableTarget(DNN_TARGET_CPU);

    // 载入采集的样本数据
    vector<vector<float>> face_data;   //每张人脸的特征向量信息
    vector<string> labels;     //人脸对应名字
    vector<string> faces;      //采集的人脸图片名称 （含有路径）
    vector<string> filenames;
    // glob(FILEPATH, faces);    //遍历文件夹下所有的采集的人脸照片 存储其路径
    filenames = find_file(FILEPATH);
    //分析每张照片  计算每张人脸照片的特征向量 为每张照片对应名称
    for (auto fn : filenames) {
        string facespath = FILEPATH + "/" + fn;
        cout<<"facespath:"<<facespath<<endl;
        glob(facespath, faces);
        for(auto filename : faces) {
            cout<<"filename:"<<filename<<endl;
            vector<float> fv;
            Mat sample = imread(filename);
            if(sample.empty()){
                cout<<"li no pic"<<endl;
                continue;
            }
            recognize_face(sample, face_net, fv);
            face_data.push_back(fv);
            labels.push_back(fn);
        }
        cout<<"fn:"<<fn<<endl;
    }

    VideoCapture capture(0);     //打开摄像头
    Mat frame;
    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        flip(frame, frame, 1);   //画面镜像

        // 构建输入 (人脸检测模型)
        Mat blob = blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
        net.setInput(blob, "data");
        // 执行推理
        Mat detection = net.forward("detection_out");
        //将推理数据 进行格式化
        Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
        float confidence_threshold = 0.5;
        float* curr_row;
        // 解析输出数据
        for (int i = 0; i < detectionMat.rows; i++) {
            curr_row = detectionMat.ptr<float>(i);
            curr_row+=2;    //获取图片id信息 用不到 只是为了让指针指向下一个数据
            float score = *curr_row++;                //获取可信度
            if (score > confidence_threshold) {    //可信度大于一定范围才进行处理
                //获取人脸矩形框的左上角 右下角坐标
                float tl_x = (*curr_row++) * frame.cols;
                float tl_y = (*curr_row++) * frame.rows;
                float br_x = (*curr_row++) * frame.cols;
                float br_y = (*curr_row++) * frame.rows;

                //根据坐标生成 矩形
                Rect box((int)tl_x, (int)tl_y, (int)(br_x - tl_x), (int)(br_y - tl_y));
                // 获取人脸ROI
                Mat face = frame(box);    //截取人脸部分
                // 人脸比对与识别
                vector<float> curr_fv;      //计算当前人脸的特征向量
                recognize_face(face, face_net, curr_fv);
                // 遍历计算与采样图片余弦相似度最小的人脸照片 并给出索引
                float minDist = 10;
                int index = 0;
                for (size_t i = 0; i < face_data.size(); i++) {
                    float dist = compare(face_data[i], curr_fv);
                    if (minDist > dist) {
                        minDist = dist;
                        index = i;
                    }
                }
                // 显示比较结果
                printf("index : %d, min distance : %.2f \n", index, minDist);
                if (minDist < 0.1 && index >= 0)   //阈值限定  显示人名
                {
                    putText(frame, format("%s", labels[index].c_str()), Point(box.x-10,box.y-10), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2, 8);
                }
                rectangle(frame, box, Scalar(255, 0, 255), 1, 8, 0);
            }
        }
        imshow("face-detection-demo", frame);
        char c = waitKey(1);
        if (c == 27) { // ESC
            break;
        }
    }
    // 释放资源
    capture.release();
    destroyAllWindows();
    waitKey(0);
    return 0;
}

void recognize_face(Mat& face, Net net, vector<float> &fv) {
	Mat blob = blobFromImage(face, 1 / 255.0, Size(96, 96), Scalar(0, 0, 0), true, false);
	net.setInput(blob);
	Mat probMat = net.forward();
	Mat vec = probMat.reshape(1, 1);
	// printf("vec rows : %d, vec cols: %d \n", vec.rows, vec.cols);
	for (int i = 0; i < vec.cols; i++) {
		fv.push_back(vec.at<float>(0, i));
	}
}

float compare(vector<float> &fv1, vector<float> &fv2) {
	float dot = 0;
	float sum2 = 0;
	float sum3 = 0;
	for (int i = 0; i < fv1.size(); i++) {
		dot += fv1[i] * fv2[i];
		sum2 += pow(fv1[i], 2);
		sum3 += pow(fv2[i], 2);
	}
	float norm = sqrt(sum2)*sqrt(sum3);
	float similary = dot / norm;
	float dist = acos(similary) / CV_PI;
	return dist;
}

vector<string> find_file(string path){
    cout<<path<<endl;
    struct dirent *ptr;  
    DIR *dir;
    string PATH = path;
    dir=opendir(PATH.c_str()); 
    vector<string> files;
    cout << "文件列表: "<< endl;
    while((ptr=readdir(dir))!=NULL)
    {
    
        //跳过'.'和'..'两个目录
        if(ptr->d_name[0] == '.')
        continue;
        //cout << ptr->d_name << endl;
        files.push_back(ptr->d_name);
    }
    
    for (int i = 0; i < files.size(); ++i)
    {
        cout << files[i] << endl;
    }

    closedir(dir);
    return files;
}
