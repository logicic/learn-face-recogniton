package main

import (
	"fmt"
	"image"
	"math"

	"gocv.io/x/gocv"
)

// detect face const content
const inScaleFactor = 1.0
const confidence_threshold = 0.7

var detect_size = image.Point{96, 96}
var mean = gocv.Scalar{}

const swapRB = true
const crop = false

//
const CV_PI = 3.1415926535897932384626433832795
const CV_32F = 5

const caffeConfigFile = "./model/models/deploy.prototxt"
const caffeWeightFile = "./model/models/res10_300x300_ssd_iter_140000_fp16.caffemodel"

const tensorflowConfigFile = "./model/models/opencv_face_detector.pbtxt"
const tensorflowWeightFile = "./model/models/opencv_face_detector_uint8.pb"

var rec_net gocv.Net = gocv.ReadNet("./model/nn4.small2.v1.t7", "")

var det_net gocv.Net = gocv.ReadNetFromCaffe(caffeConfigFile, caffeWeightFile)

func detectFaceOpencvDNN(net gocv.Net, frame gocv.Mat) gocv.Mat {
	// frameHeight := frame.Rows()
	// frameWidth := frame.Cols()

	// color := color.RGBA{0, 0, 255, 0}
	input := gocv.BlobFromImage(frame, inScaleFactor, detect_size, mean, swapRB, crop)

	var temp gocv.Mat
	net.SetInput(input, "data")
	detection := net.Forward("detection_out")
	detectionMat, _ := detection.FromPtr(detection.Size()[2], detection.Size()[3], CV_32F, detection.Rows(), detection.Cols())

	for i := 0; i < detectionMat.Rows(); i++ {
		// fmt.Println(detectionMat.Rows())
		// fmt.Println(i)
		confidence := detectionMat.GetFloatAt(i, 2)
		fmt.Println(confidence)
		if confidence > confidence_threshold {
			// x1 := int(detectionMat.GetFloatAt(i, 3) * float32(frameWidth))
			// y1 := int(detectionMat.GetFloatAt(i, 4) * float32(frameHeight))
			// x2 := int(detectionMat.GetFloatAt(i, 5) * float32(frameWidth))
			// y2 := int(detectionMat.GetFloatAt(i, 6) * float32(frameHeight))
			// rect := image.Rectangle{image.Point{x1, y1}, image.Point{x2, y2}}
			fmt.Println("$$$$$$$$$$$", confidence)
			// gocv.Rectangle(&frame, rect, color, 3)
			// temp = frame.Region(rect)
		}
	}
	return temp
}

func recognize_face(face gocv.Mat, net gocv.Net, fv *[]float32) {
	inputBlob := gocv.BlobFromImage(face, 1.0, image.Point{96, 96}, gocv.Scalar{}, true, false)
	net.SetInput(inputBlob, "")
	feature := net.Forward("")
	vec := feature.Reshape(1, 1)
	// fmt.Printf("vec rows : %d, vec cols: %d \n", vec.Rows(), vec.Cols())
	for i := 0; i < vec.Cols(); i++ {
		// fmt.Println(float32(vec.GetFloatAt(0, i)))
		*fv = append(*fv, float32(vec.GetFloatAt(0, i)))
	}
	// fmt.Println("fv : ", fv)
}

func compare(fv1 []float32, fv2 []float32) float32 {
	var dot float64 = 0
	var sum2 float64 = 0
	var sum3 float64 = 0

	for i := 0; i < len(fv1); i++ {
		dot += float64(fv1[i] * fv2[i])
		sum2 += math.Pow(float64(fv1[i]), 2)
		sum3 += math.Pow(float64(fv2[i]), 2)
	}

	norm := math.Sqrt(sum2) * math.Sqrt(sum3)
	similary := dot / norm
	distance := float32(math.Acos(similary) / CV_PI)
	return distance
}

func main() {
	// var fv1, fv2 []float32
	window := gocv.NewWindow("Hello")
	img := gocv.IMRead("./pic/obama.jpg", 1)
	// img2 := gocv.IMRead("./pic/rena.jpg", 1)
	temp := detectFaceOpencvDNN(det_net, img)
	// cvnet := gocv.ReadNetFromTensorflow("./model/20180408-102900.pb")
	// cvnet := gocv.ReadNet("./model/nn4.small2.v1.t7", "")
	// recognize_face(img, cvnet, &fv1)
	// recognize_face(img2, cvnet, &fv2)
	// dist := compare(fv1, fv2)
	// fmt.Println(dist)
	// fmt.Println("fv : ", fv)
	// fmt.Println(cvnet)
	// mean := gocv.Scalar{1.0, 1.0, 1.0, 1.0}
	// fmt.Println(mat.Norm(uint64(feature)-uint64(feature2), 1))
	for {
		window.IMShow(temp)
		window.WaitKey(1)
	}
}
