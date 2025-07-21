/*
Package Interpreter

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Interpreter

import (
	"strconv"
	"strings"
)

type Parser struct {
	exp   []string
	index int
	prev  Node
}

func (p *Parser) Result() Node {
	return p.prev
}

func (p *Parser) Parse(exp string) {
	p.exp = strings.Split(exp, " ")
	for {
		if p.index >= len(p.exp) {
			break
		}
		switch p.exp[p.index] {
		case "+":
			p.prev = p.newAddNode()
		default:
			p.prev = p.newValNode()
		}
	}
}

func (p *Parser) newAddNode() Node {
	p.index++
	return &AddNode{p.prev, p.newValNode()}
}

func (p *Parser) newValNode() Node {
	v, _ := strconv.Atoi(p.exp[p.index])
	p.index++
	return &ValNode{v}
}
