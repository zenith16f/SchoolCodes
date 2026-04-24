package main

import (
	"errors"
	"fmt"
	"strings"
)

type Parser struct {
	Automata string
	Tests    []string
}
type ParserList []Parser

func (p *ParserList) String() string {
	return fmt.Sprint(*p)
}

func (p *ParserList) Set(value string) error {
	chunks := strings.SplitN(value, ":", 2)
	if len(chunks) < 2 {
		return errors.New("formato invalido, debe ser de la siguiente forma: go run main.go -job \"auto1.json:test1.txt\" -job \"auto2.json:test2.txt\"")
	}

	object := Parser{
		Automata: chunks[0],
		Tests:    strings.Split(chunks[1], ","),
	}
	*p = append(*p, object)
	return nil
}