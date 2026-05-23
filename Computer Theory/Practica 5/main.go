package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("go run . archivo.txt")
		return
	}

	inputFile := os.Args[1]

	afn, err := ReadAutomaton(inputFile)
	if err != nil {
		fmt.Printf("Error leyendo el AFN: %v\n", err)
		return
	}

	PrintDefinitionAF("Autómata Finito No Determinista (AFN)", afn, true)

	afd := ConvertAFNToAFD(afn)

	PrintDefinitionAF("Autómata Finito Determinista (AFD)", afd, false)

	err = ExportToJFLAP(afn, inputFile+"AFN"+".jff", true)
	if err != nil {
		fmt.Println("Error generando AFN.jff:", err)
	}

	err = ExportToJFLAP(afd, inputFile+"AFD"+".jff", false)
	if err != nil {
		fmt.Println("Error generando AFD.jff:", err)
	}
}
