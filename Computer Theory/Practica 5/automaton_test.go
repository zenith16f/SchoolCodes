package main

import (
	"testing"
)

// func TestReadAutomaton(t *testing.T) {
// 	t.Run("cargando el automata 1 de AFN01.txt", func(t *testing.T) {
// 		automata, err := ReadAutomaton("data/AFN01.txt")
// 		if err != nil {
// 			t.Error(err)
// 		}
// 		fmt.Printf("%v\n", automata)
// 		fmt.Printf("%b", automata.FinalStates)
// 	})
// }

func BenchmarkConvertAFNToAFD_Slice(b *testing.B) {
	afn, err := ReadAutomaton("data/AFN03.txt")
	if err != nil {
		b.Fatalf("Error leyendo archivo: %v", err)
	}

	b.ResetTimer()
	for b.Loop() {
		ConvertAFNToAFD_slicing(afn)
	}
}

func BenchmarkConvertAFNToAFD_RingBuffer(b *testing.B) {
	afn, err := ReadAutomaton("data/AFN03.txt")
	if err != nil {
		b.Fatalf("Error leyendo archivo: %v", err)
	}

	b.ResetTimer()
	for b.Loop() {
		ConvertAFNToAFD(afn)
	}
}
