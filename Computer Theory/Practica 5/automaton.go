package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode/utf8"
)

type Automaton struct {
	StateNames         []string
	StatesMap          map[string]int
	TransitionFunction [][]Byte256
	FinalStates        Byte256
	InitState          int
	Alphabet           []rune
}

func ReadAutomaton(file string) (*Automaton, error) {
	f, err := os.Open(file)
	if err != nil {
		return nil, err
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)

	readLine := func() (string, error) {
		for scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if line != "" {
				return line, nil
			}
		}
		return "", fmt.Errorf("error al leer el archivo")
	}

	// 1) Leer estados
	line, _ := readLine()
	statesLine := strings.Fields(line)
	res := &Automaton{
		StateNames: statesLine,
		StatesMap:  make(map[string]int, len(statesLine)),
	}
	for i, v := range statesLine {
		res.StatesMap[v] = i
	}

	// 2) Leer estado inicial
	initStateLine, _ := readLine()
	res.InitState = res.StatesMap[initStateLine]

	// 3) Leer estados finales
	line, _ = readLine()
	finalStatesLine := strings.FieldsSeq(line)
	for v := range finalStatesLine {
		res.FinalStates.Set(res.StatesMap[v])
	}

	// 4) Leer alfabeto
	line, _ = readLine()
	alphabetLine := strings.Fields(line)
	res.Alphabet = make([]rune, len(alphabetLine))
	for i, v := range alphabetLine {
		res.Alphabet[i], _ = utf8.DecodeRuneInString(v)
	}

	// 5) Iniciar funcion de transicion
	numStates := len(res.StateNames)
	numCols := len(res.Alphabet) + 1
	res.TransitionFunction = make([][]Byte256, numStates)
	for i := range res.TransitionFunction {
		res.TransitionFunction[i] = make([]Byte256, numCols)
	}

	// 6) Leer transiciones
	stateRow := 0
	for scanner.Scan() {
		line = strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		cols := strings.Fields(line)
		for colIdx, v := range cols {
			if v == "-" {
				continue
			}
			destinations := strings.SplitSeq(v, ",")
			for dest := range destinations {
				if destID, ok := res.StatesMap[dest]; ok {
					res.TransitionFunction[stateRow][colIdx].Set(destID)
				}
			}
		}
		stateRow++
	}

	return res, nil
}
