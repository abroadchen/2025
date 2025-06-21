package designmode



type Merkletree struct {
	Root *Node  //root
	merkleRoot []byte //hash sum
	leafs []*Node
}

type NodeX struct {
	Parent *Node
	Left *Node
	Right *Node
	leaf bool
	dup bool
	Hash []byte
	Content Content
}

type Content interface {
	CalclateHash()([]byte, error)
	Equal(other Content) (bool, error)
}

type MerkleTree interface{
	verifycode()([]byte, error)
	calcNodehash()([]byte, error)
	NewTree
}
