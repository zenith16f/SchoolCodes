package main

import "fmt"

type IntRingBuffer struct {
	buffer []int
	head   int
	tail   int
	count  int
	cap    int
}

func NewIntRingBuffer(size int) *IntRingBuffer {
	return &IntRingBuffer{
		buffer: make([]int, size),
		cap:    size,
	}
}

func (rb *IntRingBuffer) Push(val int) {
	if rb.count == rb.cap {
		rb.resize()
	}
	rb.buffer[rb.tail] = val
	rb.tail = (rb.tail + 1) % rb.cap
	rb.count++
}

func (rb *IntRingBuffer) Pop() int {
	if rb.count == 0 {
		return -1 // Cola vacía
	}
	val := rb.buffer[rb.head]
	rb.head = (rb.head + 1) % rb.cap
	rb.count--
	return val
}

func (rb *IntRingBuffer) IsEmpty() bool {
	return rb.count == 0
}

func (rb *IntRingBuffer) resize() {
	newCap := rb.cap * 2
	newBuffer := make([]int, newCap)

	if rb.tail > rb.head {
		copy(newBuffer, rb.buffer[rb.head:rb.tail])
	} else {
		n := copy(newBuffer, rb.buffer[rb.head:])
		copy(newBuffer[n:], rb.buffer[:rb.tail])
	}

	rb.buffer = newBuffer
	rb.head = 0
	rb.tail = rb.count
	rb.cap = newCap
}

func epsilonClosure(states Byte256, afn *Automaton) Byte256 {
	closure := states
	stack := make([]int, 0)

	for i := 0; i < len(afn.StateNames); i++ {
		if states.Has(i) {
			stack = append(stack, i)
		}
	}

	epsilonCol := len(afn.Alphabet)

	for len(stack) > 0 {
		curr := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		destinations := afn.TransitionFunction[curr][epsilonCol]
		for i := 0; i < len(afn.StateNames); i++ {
			if destinations.Has(i) && !closure.Has(i) {
				closure.Set(i)
				stack = append(stack, i)
			}
		}
	}
	return closure
}

func move(states Byte256, symbolIndex int, afn *Automaton) Byte256 {
	var result Byte256
	for i := 0; i < len(afn.StateNames); i++ {
		if states.Has(i) {
			result.Or(afn.TransitionFunction[i][symbolIndex])
		}
	}
	return result
}

func ConvertAFNToAFD(afn *Automaton) *Automaton {
	afd := &Automaton{
		StatesMap: make(map[string]int),
		Alphabet:  afn.Alphabet,
	}

	var dfaStates []Byte256
	stateSetToID := make(map[Byte256]int)
	transitionsMap := make(map[int]map[int]int)

	// Estado inicial del AFD = e-closure(q0)
	var q0 Byte256
	q0.Set(afn.InitState)
	q0Closure := epsilonClosure(q0, afn)

	dfaStates = append(dfaStates, q0Closure)
	stateSetToID[q0Closure] = 0

	queue := NewIntRingBuffer(32)
	queue.Push(0)

	for !queue.IsEmpty() {
		currID := queue.Pop()
		currStateSet := dfaStates[currID]

		transitionsMap[currID] = make(map[int]int)

		// Evaluar cada símbolo del alfabeto
		for symIdx := range afn.Alphabet {
			reachableSet := move(currStateSet, symIdx, afn)
			if reachableSet.IsEmpty() {
				continue
			}

			closureSet := epsilonClosure(reachableSet, afn)

			destID, exists := stateSetToID[closureSet]
			if !exists {
				destID = len(dfaStates)
				dfaStates = append(dfaStates, closureSet)
				stateSetToID[closureSet] = destID

				queue.Push(destID)
			}
			transitionsMap[currID][symIdx] = destID
		}
	}

	numDfaStates := len(dfaStates)
	afd.TransitionFunction = make([][]Byte256, numDfaStates)
	for i := range afd.TransitionFunction {
		afd.TransitionFunction[i] = make([]Byte256, len(afd.Alphabet))
	}

	for i, stateSet := range dfaStates {
		name := fmt.Sprintf("D%d", i)
		afd.StateNames = append(afd.StateNames, name)
		afd.StatesMap[name] = i

		for j := 0; j < len(afn.StateNames); j++ {
			if stateSet.Has(j) && afn.FinalStates.Has(j) {
				afd.FinalStates.Set(i)
				break
			}
		}

		if trans, ok := transitionsMap[i]; ok {
			for symIdx, destID := range trans {
				afd.TransitionFunction[i][symIdx].Set(destID)
			}
		}
	}

	afd.InitState = 0
	return afd
}

func ConvertAFNToAFD_slicing(afn *Automaton) *Automaton {
	afd := &Automaton{
		StatesMap: make(map[string]int),
		Alphabet:  afn.Alphabet,
	}

	var dfaStates []Byte256
	stateSetToID := make(map[Byte256]int)
	transitionsMap := make(map[int]map[int]int)

	// e-closure(q0) -> A
	var q0 Byte256
	q0.Set(afn.InitState)
	q0Closure := epsilonClosure(q0, afn)

	dfaStates = append(dfaStates, q0Closure)
	stateSetToID[q0Closure] = 0
	worklist := []int{0}

	for len(worklist) > 0 {
		currID := worklist[0]
		worklist = worklist[1:]
		currStateSet := dfaStates[currID]

		transitionsMap[currID] = make(map[int]int)

		// Ir_A por cada elemento de la cola con cada simbolo del alfabeto
		for symIdx := range afn.Alphabet {
			reachableSet := move(currStateSet, symIdx, afn)
			if reachableSet.IsEmpty() {
				continue
			}

			closureSet := epsilonClosure(reachableSet, afn)

			destID, exists := stateSetToID[closureSet]
			if !exists {
				destID = len(dfaStates)
				dfaStates = append(dfaStates, closureSet)
				stateSetToID[closureSet] = destID
				worklist = append(worklist, destID)
			}
			transitionsMap[currID][symIdx] = destID
		}
	}

	numDfaStates := len(dfaStates)
	afd.TransitionFunction = make([][]Byte256, numDfaStates)
	for i := range afd.TransitionFunction {
		afd.TransitionFunction[i] = make([]Byte256, len(afd.Alphabet))
	}

	for i, stateSet := range dfaStates {
		name := fmt.Sprintf("D%d", i)
		afd.StateNames = append(afd.StateNames, name)
		afd.StatesMap[name] = i

		// Asignación de estados finales
		for j := 0; j < len(afn.StateNames); j++ {
			if stateSet.Has(j) && afn.FinalStates.Has(j) {
				afd.FinalStates.Set(i)
				break
			}
		}

		// Poblar matriz de transiciones
		if trans, ok := transitionsMap[i]; ok {
			for symIdx, destID := range trans {
				afd.TransitionFunction[i][symIdx].Set(destID)
			}
		}
	}

	afd.InitState = 0
	return afd
}
