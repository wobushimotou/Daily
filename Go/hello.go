package main

import "fmt"

func main() {
    const (
        a = 1<<iota
        b = 2<<iota
        c
    )
    
    fmt.Println(a,b,c)
    fmt.Println("Hello,World")
}
