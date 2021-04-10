package main

/*
#cgo LDFLAGS: -ltestcode -L./
#include "testcode.h"
*/
import "C"

func main() {
	C.get_message()
}
