package main

const (
	byteSize  = 4
	blockSize = 64
)

type Byte256 [byteSize]uint64

func (b *Byte256) Set(state int) {
	b[state/blockSize] |= 1 << (state % blockSize)
}

func (b *Byte256) Has(state int) bool {
	return (b[state/blockSize] & (1 << (state % blockSize))) != 0
}

func (b *Byte256) Or(other Byte256) {
	for i := 0; i < byteSize; i++ {
		b[i] |= other[i]
	}
}

func (b *Byte256) IsEmpty() bool {
	for i := 0; i < byteSize; i++ {
		if b[i] != 0 {
			return false
		}
	}
	return true
}

func (b *Byte256) Equals(other Byte256) bool {
	for i := 0; i < byteSize; i++ {
		if b[i] != other[i] {
			return false
		}
	}
	return true
}
