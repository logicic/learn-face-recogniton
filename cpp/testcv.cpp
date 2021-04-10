#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace cv;

const size_t inWidth = 300;
const size_t inHeight = 300;
const double inScaleFactor = 1.0;
const float confidenceThreshold = 0.7;
const cv::Scalar meanVal(104.0, 177.0, 123.0);
#define IMGNORHEIGHT 112
#define IMGNORWIDTH 96
#define CAFFE

const std::string caffeConfigFile = "./model/models/deploy.prototxt";
const std::string caffeWeightFile = "./model/models/res10_300x300_ssd_iter_140000_fp16.caffemodel";

const std::string tensorflowConfigFile = "./model/models/opencv_face_detector.pbtxt";
const std::string tensorflowWeightFile = "./model/models/opencv_face_detector_uint8.pb";


// dnn::Net rec_net = dnn::readNetFromTorch("./model/nn4.v1.t7");
// dnn::Net net = dnn::readNetFromTensorflow("./model/20180408-102900.pb");
dnn::Net rec_net = dnn::readNet("./model/nn4.small2.v1.t7");

#ifdef CAFFE
	dnn::Net det_net = cv::dnn::readNetFromCaffe(caffeConfigFile, caffeWeightFile);
#else
	dnn::Net det_net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif

Mat detectFaceOpenCVDNN(dnn::Net net, Mat &frameOpenCVDNN)
{
	int frameHeight = frameOpenCVDNN.rows;
	int frameWidth = frameOpenCVDNN.cols;
#ifdef CAFFE
	cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, false, false);
#else
	cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, true, false);
#endif
    Mat temp;
	net.setInput(inputBlob, "data");
	cv::Mat detection = net.forward("detection_out");

	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    // cout<<detectionMat.rows<<endl;
	for (int i = 0; i < detectionMat.rows; i++)
	{
		float confidence = detectionMat.at<float>(i, 2);
        // cout<<"confidence:  "<<confidence<<endl;
		if (confidence > confidenceThreshold)
		{
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);
            // cout<<cv::Point(x1, y1)<<"\t"<<cv::Point(x1, y1)<<endl;
			cv::rectangle(frameOpenCVDNN, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2, 4);
            Rect rect(cv::Point(x1, y1), cv::Point(x2, y2));
            temp = frameOpenCVDNN(rect);
            // imwrite("./pic/save2.jpg", temp);
		}
	}
    return temp;
}

double CosineSimilarity(Mat& a, Mat& b)
{
    double ab = a.dot(b);
    double norma=norm(a);
    double normb=norm(b); 
    if(norma!=0 && normb!=0){
        return ab / (norma * normb);
    }
    return -1;
}

double euclidean_distance(Mat baseImg, Mat targetImg)
{
    double sumDescriptor = 0;
    for (int i = 0; i < baseImg.cols; i++)
    {
        double numBase = abs(baseImg.at<float>(0, i));
        double numTarget = abs(targetImg.at<float>(0, i));
        sumDescriptor += pow(numBase-numTarget, 2);
    }
    double simility = sqrt(sumDescriptor);
    return simility;
}

double cos_distance(Mat baseImg, Mat targetImg)
{
    double squSumB = 0;
    double squSumT = 0;
    double innerPro = 0;
    for (int i = 0; i < baseImg.cols; i++)
    {
        double numBase = abs(baseImg.at<float>(0, i));
        double numTarget = abs(targetImg.at<float>(0, i));
        squSumB = squSumB + numBase*numBase;
        squSumT = squSumT + numTarget*numTarget;

        innerPro = innerPro + numBase*numTarget;
    }
    double modB = sqrt(squSumB);
    double modT = sqrt(squSumT);
    double simility = innerPro / (modB*modT);
    return simility;
}


Mat recognize(Mat face) {
    // Mat inputBlob = dnn::blobFromImage(face, 1./255, Size(96,96), Scalar(), true, false);
    cout<<"channel: "<<face.channels()<<endl;
    cout<<"rows: "<<face.rows<<endl;
    cout<<"cols: "<<face.cols<<endl;
    Mat inputBlob = dnn::blobFromImage(face, 1./255, Size(96, 96), Scalar(), true, false);
    rec_net.setInput(inputBlob);
    Mat feature = rec_net.forward().clone();
    Mat result(IMGNORHEIGHT, IMGNORWIDTH, CV_8UC3);

    feature.copyTo(result);
    return result;
}

void recognize_face(Mat& face, dnn::Net net, vector<float> &fv) {
	Mat blob = dnn::blobFromImage(face, 1 / 255.0, Size(96, 96), Scalar(0, 0, 0), true, false);
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


int main(){
    Mat img = imread("./pic/rena.jpg");
    Mat img2 = imread("./pic/jj.jpg");

    Mat temp = detectFaceOpenCVDNN(det_net, img);
    Mat temp2 = detectFaceOpenCVDNN(det_net, img2);
    
    vector<float> fa;
    vector<float> fa2;
    recognize_face(temp, rec_net, fa);
    recognize_face(temp2, rec_net, fa2);
    float similar = compare(fa, fa2);
    // Mat fa = recognize(temp);
    // Mat fa2 = recognize(temp2);

    // double similar = euclidean_distance(fa, fa2);
    // double similar = norm(fa, fa2);
    if(similar == -1){
        cout<<"error"<<endl;
        return 0;
    }
    cout<<similar<<endl;
    if (similar > 0.6) {
        cout<<"匹配"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
    while(1){
        imshow("sd", temp);
        waitKey(1);
    }
    
    return 0;
}


// int main()
// {
//     Mat img = imread("./pic/save3.jpg");
//     Mat img_temp = detectFaceOpenCVDNN(det_net, img);
//     Mat fa = recognize(img_temp);
//     VideoCapture cap(0);
//     Mat save;
//     cap>>save;
//     imwrite("./pic/save3.jpg",save);
//     while(1){
//         Mat src;
//         cap>>src;
//         if(src.empty()){
//             continue;
//         }
//         Mat temp = detectFaceOpenCVDNN(det_net, src);
//         if(temp.empty()){
//             continue;
//         }
//         Mat fa2 = recognize(temp);
//         double similar = euclidean_distance(fa, fa2);
//         // double similar = norm(fa, fa2);
//         if(similar == -1){
//             cout<<"error"<<endl;
//             return 0;
//         }
//         cout<<similar<<endl;
//         if (similar > 0.6) {
//             cout<<"匹配"<<endl;
//         }else{
//             cout<<"NO"<<endl;
//         }
//         imshow("imm", src);
//         waitKey(1);
//     }
// }