package main

import (
	"encoding/xml"
	"fmt"
	"os"
	"strings"
)

type JflapStructure struct {
	XMLName   xml.Name       `xml:"structure"`
	Type      string         `xml:"type"`
	Automaton JflapAutomaton `xml:"automaton"`
}

type JflapAutomaton struct {
	States      []JflapState      `xml:"state"`
	Transitions []JflapTransition `xml:"transition"`
}

type JflapState struct {
	Id      int       `xml:"id,attr"`
	Name    string    `xml:"name,attr"`
	X       string    `xml:"x"`
	Y       string    `xml:"y"`
	Initial *struct{} `xml:"initial,omitempty"`
	Final   *struct{} `xml:"final,omitempty"`
}

type JflapTransition struct {
	From int    `xml:"from"`
	To   int    `xml:"to"`
	Read string `xml:"read"`
}

func ExportToJFLAP(automaton *Automaton, filename string, isAFN bool) error {
	jflap := JflapStructure{Type: "fa"}

	for i, name := range automaton.StateNames {
		state := JflapState{
			Id:   i,
			Name: name,
			X:    fmt.Sprintf("%d", 100+(i*80)),
			Y:    fmt.Sprintf("%d", 150+((i%2)*80)),
		}
		if i == automaton.InitState {
			state.Initial = &struct{}{}
		}
		if automaton.FinalStates.Has(i) {
			state.Final = &struct{}{}
		}
		jflap.Automaton.States = append(jflap.Automaton.States, state)
	}

	cols := len(automaton.Alphabet)
	if isAFN {
		cols += 1
	}

	for i := range automaton.TransitionFunction {
		for j := 0; j < cols; j++ {
			destinations := automaton.TransitionFunction[i][j]
			for k := 0; k < len(automaton.StateNames); k++ {
				if destinations.Has(k) {
					readSymbol := ""
					if j < len(automaton.Alphabet) {
						readSymbol = string(automaton.Alphabet[j])
					}
					jflap.Automaton.Transitions = append(jflap.Automaton.Transitions, JflapTransition{
						From: i,
						To:   k,
						Read: readSymbol,
					})
				}
			}
		}
	}

	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	file.WriteString("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n")
	encoder := xml.NewEncoder(file)
	encoder.Indent("", "    ")
	return encoder.Encode(jflap)
}

func PrintDefinitionAF(label string, a *Automaton, isAFN bool) {
	fmt.Printf("\n=== %s ===\n", label)

	fmt.Printf("Q = { %s }\n", strings.Join(a.StateNames, ", "))

	var alpha []string
	for _, r := range a.Alphabet {
		alpha = append(alpha, string(r))
	}
	fmt.Printf("Σ = { %s }\n", strings.Join(alpha, ", "))

	fmt.Printf("q0 = %s\n", a.StateNames[a.InitState])

	var finals []string
	for i, name := range a.StateNames {
		if a.FinalStates.Has(i) {
			finals = append(finals, name)
		}
	}
	fmt.Printf("F = { %s }\n", strings.Join(finals, ", "))

	fmt.Printf("\nTabla de transiciones:\n")
	fmt.Printf("%-10s", "Estado")
	for _, sym := range alpha {
		fmt.Printf("| %-15s", sym)
	}
	if isAFN {
		fmt.Printf("| %-15s", "λ")
	}
	fmt.Println()

	cols := len(a.Alphabet)
	if isAFN {
		cols += 1
	}

	for i, name := range a.StateNames {
		indicator := ""
		if a.InitState == i {
			indicator += "->"
		}
		if a.FinalStates.Has(i) {
			indicator += "*"
		}
		fmt.Printf("%-10s", indicator+name)

		for j := 0; j < cols; j++ {
			var dests []string
			for k := 0; k < len(a.StateNames); k++ {
				if a.TransitionFunction[i][j].Has(k) {
					dests = append(dests, a.StateNames[k])
				}
			}
			if len(dests) == 0 {
				fmt.Printf("| %-15s", "-")
			} else {
				fmt.Printf("| %-15s", strings.Join(dests, ","))
			}
		}
		fmt.Println()
	}
}
