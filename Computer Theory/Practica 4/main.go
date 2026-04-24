package main

import (
	"bufio"
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"os"
	"sync"
	"unicode/utf8"
)

type DFATemp struct {
	Alphabet           []string                     `json:"alphabet"`
	States             []string                     `json:"states"`
	InitState          string                       `json:"initState"`
	FinalStates        []string                     `json:"finalStates"`
	TransitionFunction map[string]map[string]string `json:"transitionFunction"`
}

type TransitionKey struct {
	State  string
	Symbol rune
}

type DFA struct {
	Alphabet           []rune              `json:"alphabet"`
	States             []string            `json:"states"`
	InitState          string              `json:"initState"`
	FinalStates        map[string]struct{} `json:"finalStates"`
	TransitionFunction map[TransitionKey]string
}
type ValidationResult struct {
	Text  string
	Value bool
}

func (a *DFA) validate(test string) bool {
	// Initializing on the init state
	current := TransitionKey{State: a.InitState}
	for _, v := range test {
		current.Symbol = v
		state, ok := a.TransitionFunction[current]
		if !ok {
			return false
		}
		current.State = state
	}
	_, ok := a.FinalStates[current.State]
	return ok
}

func reader(channel chan<- string, file string) {
	defer close(channel)
	f, err := os.Open(file)
	if err != nil {
		fmt.Println("Error al abrir el archivo " + file)
		return
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		channel <- scanner.Text()
	}
}

func (a *DFA) validateConc(receiver <-chan string, sender chan<- ValidationResult) {
	defer close(sender)
outer:
	for v := range receiver {
		current := TransitionKey{State: a.InitState}
		for _, k := range v {
			current.Symbol = k
			state, ok := a.TransitionFunction[current]
			if !ok {
				sender <- ValidationResult{Text: v, Value: false}
				continue outer
			}
			current.State = state
		}
		_, ok := a.FinalStates[current.State]

		sender <- ValidationResult{Text: v, Value: ok}
	}
}

func writer(wg *sync.WaitGroup, receiver <-chan ValidationResult, file string) {
	defer wg.Done()
	f, err := os.Create(file)
	if err != nil {
		return
	}
	defer f.Close()
	for k := range receiver {
		f.WriteString(fmt.Sprintf("%s\t %t \n", k.Text, k.Value))
	}
	f.Sync()
}

func LoadAutomaton(file string) (*DFA, error) {
	data, err := os.ReadFile(file)
	if err != nil {
		return nil, err
	}

	temp := &DFATemp{}
	err = json.Unmarshal(data, temp)
	if err != nil {
		return nil, err
	}
	DFAFinal := &DFA{
		States:             make([]string, 0, len(temp.States)),
		InitState:          temp.InitState,
		FinalStates:        make(map[string]struct{}, len(temp.FinalStates)),
		TransitionFunction: make(map[TransitionKey]string),
	}
	DFAFinal.States = temp.States
	for _, k := range temp.FinalStates {
		DFAFinal.FinalStates[k] = struct{}{}
	}
	for k, v := range temp.TransitionFunction {
		for alphabetKey, destinationState := range v {
			r, _ := utf8.DecodeRuneInString(alphabetKey)
			DFAFinal.TransitionFunction[TransitionKey{State: k, Symbol: r}] = destinationState
		}
	}
	return DFAFinal, nil
}

var job ParserList

func main() {
	flag.Var(&job, "job", " go run main.go -job \"auto1.json:test1.txt\" -job \"auto2.json:test2.txt\"")
	flag.Parse()
	// automatonsFiles := make([]string, 0, 5)
	// automatons := make([]*DFA, 0, 5)
	// responseFiles := make([]string, 0, 10)
	// for i := range automatonsFiles {
	// 	automaton, err := LoadAutomaton(automatonsFiles[i])
	// 	if err != nil {
	// 		fmt.Println(err)
	// 	}
	// 	automatons[i] = automaton
	// }
	automatons := make([]*DFA, len(job))
	var wgWritters sync.WaitGroup
	for i, v := range job {
		automaton, err := LoadAutomaton(v.Automata)
		automatons[i] = automaton
		if err != nil {
			log.Fatalf("No se pudo cargar el automata...")
		}
		for _, k := range v.Tests {
			comms := make(chan string)
			sender := make(chan ValidationResult)
			wgWritters.Add(1)
			go reader(comms, k)
			go automatons[i].validateConc(comms, sender)
			go writer(&wgWritters, sender, k+".res")

		}
	}
	// var wgValidators sync.WaitGroup
	// var wgReaders sync.WaitGroup
	// readerChannels := make([]chan string, 10)
	// responseChannels := make([]chan ValidationResult, 10)
	// for i := range readerChannels {
	// 	readerChannels[i] = make(chan string)
	// }
	// for i := range responseChannels {
	// 	responseChannels[i] = make(chan ValidationResult)
	// }
	// go func() {
	// 	for i, v := range responseFiles {
	// 		wgReaders.Add(1)
	// 		go reader(&wgReaders, readerChannels[i], v)
	// 	}
	// 	wgReaders.Wait()
	// 	for i := range readerChannels {
	// 		close(readerChannels[i])
	// 	}
	// }()
	// go func() {
	// 	for i, v := range automatons {
	// 		wgValidators.Add(1)
	// 		go v.validateConc(readerChannels[i], responseChannels[i], &wgValidators)
	// 	}
	// 	wgValidators.Wait()
	// 	for i := range responseChannels {
	// 		close(responseChannels[i])
	// 	}
	// }()
	// for i := range responseFiles {
	// 	wgWritters.Add(1)
	// 	go writer(&wgWritters, responseChannels[i], responseFiles[i])
	// }
	wgWritters.Wait()

	// dat, err := os.ReadFile(os.Args[1])
	// if err != nil {
	// 	log.Fatalf("No se pudo encontrar el archivo proporcionado")
	// }
	// file := &DFATemp{}
	// err = json.Unmarshal(dat, file)
	// if err != nil {
	// 	log.Fatalf("Ocurrió un error al leer el archivo, verifique su estructura como en el readme.md")
	// }
	// DFAs := &DFA{
	// 	States:             make([]string, 0, len(file.States)),
	// 	FinalStates:        make(map[string]struct{}, len(file.FinalStates)),
	// 	InitState:          file.InitState,
	// 	TransitionFunction: make(map[TransitionKey]string),
	// }
	// DFAs.States = file.States // It's not necessary to make an immutable slice, the DFA's struct acts as a read one
	// for _, k := range file.FinalStates {
	// 	DFAs.FinalStates[k] = struct{}{}
	// }
	// for k, v := range file.TransitionFunction {
	// 	for alphabetKey, destinationState := range v {
	// 		r, _ := utf8.DecodeRuneInString(alphabetKey)
	// 		DFAs.TransitionFunction[TransitionKey{State: k, Symbol: r}] = destinationState
	// 	}
	// }
	// fmt.Println(DFAs.validate("0"))
	// fmt.Println(DFAs.validate("11"))
	// fmt.Println(DFAs.validate("10"))
	// fmt.Println(DFAs.validate("12"))
	// fmt.Println(DFAs.validate("1200000022"))
	// fmt.Println(DFAs.validate("ab"))
	// fmt.Println(DFAs.validate(" abc"))
}