package main

func fibonacci() func() int {
    first, second := 0, 1
    return func() int {
        ret := first
        first, second = second, first+second
        return ret
    }
}
