package main

import (
	"fmt"
	"image"

	"gocv.io/x/gocv"
	"gonum.org/v1/gonum/mat"
)

func main() {
	window := gocv.NewWindow("Hello")
	img := gocv.IMRead("./pic/rena.jpg", 1)
	img2 := gocv.IMRead("./pic/jj.jpg", 1)
	// cvnet := gocv.ReadNetFromTensorflow("./model/20180408-102900.pb")
	cvnet := gocv.ReadNet("./model/nn4.small2.v1.t7", "")
	// fmt.Println(cvnet)
	// mean := gocv.Scalar{1.0, 1.0, 1.0, 1.0}
	inputBlob := gocv.BlobFromImage(img, 1.0, image.Point{96, 96}, gocv.Scalar{}, true, false)
	inputBlob2 := gocv.BlobFromImage(img2, 1.0, image.Point{96, 96}, gocv.Scalar{}, true, false)
	cvnet.SetInput(inputBlob, "")
	feature := cvnet.Forward("")
	cvnet.SetInput(inputBlob2, "")
	feature2 := cvnet.Forward("")
	fmt.Println(feature)
	fmt.Println(feature2)
	fmt.Println(mat.Norm(uint64(feature)-uint64(feature2), 1))
	for {
		window.IMShow(img)
		window.WaitKey(1)
	}
}
