package main

import (
	"testing"
)

// cheapest price to get to the top
func paidStairCases(n int, p []int) int {
    dp := make([]int, n+1)
    dp[0] = 0
    dp[1] = p[1]
    for i:= 2; i <= n; i++ {
        dp[i] = p[i] + min(dp[i-1], dp[i-2])
    }
    return dp[n]
}

func min(a, b int) int {
    if a < b {
	return a
    }
    return b	
}

func TestPaidStaircase(t *testing.T) {
	type args struct {
		x int
		p []int
	}
	tests := []struct {
		name string
		x    args
		want int
	}{
		{name: "01 floor", x: args{x:1, p: []int{0,3,2,4,1}}, want: 3},
		{name: "02 floors", x: args{x:2, p: []int{0,3,2,4,3}}, want: 2},
		{name: "04 floors", x: args{x:4, p: []int{0,3,4,2,3}}, want: 7},
	}
	for _, tt := range tests {
		if got := paidStairCases(tt.x.x, tt.x.p); got != tt.want {
			t.Errorf("[KO] (%v, %v) = %v want %v", tt.name, tt.x.x, got, tt.want)
		} else {
			t.Logf("[OK] (%v, %v) = %v want %v", tt.name, tt.x.x, got, tt.want)
		}
	}
}

/*
=== RUN   TestClimStairs
    prog.go:43: [OK] (01 floor, 1) = 3 want 3
    prog.go:43: [OK] (02 floors, 2) = 2 want 2
    prog.go:43: [OK] (04 floors, 4) = 7 want 7
--- PASS: TestClimStairs (0.00s)
PASS
*/ 
