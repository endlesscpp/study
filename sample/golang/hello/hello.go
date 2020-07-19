package main

import (
	"fmt"
	"github.com/google/go-cmp/cmp"
	"oak.com/user/hello/morestrings"
)

func main() {
	fmt.Println(morestrings.ReverseRunes("!oG ,olleH"))
	fmt.Println(cmp.Diff("Hello world", "Hello, go"))
}
