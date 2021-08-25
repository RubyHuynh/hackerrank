package main

import (
	"testing"
)


func climbStairs(n int) int {
    dp := make([]int, n+1)
    dp[0] = 1
    dp[1] = 1
    for i:= 2; i <= n; i++ {
        dp[i] = dp[i-1] + dp[i-2]
    }
    return dp[n]
}

func TestClimStairs(t *testing.T) {
	type args struct {
		x int
	}
	tests := []struct {
		name string
		x    args
		want int
	}{
		{name: "01 floor", x: args{1}, want: 1},
		{name: "02 floors", x: args{2}, want: 2},
		{name: "04 floors", x: args{4}, want: 5},
	}
	for _, tt := range tests {
		if got := climbStairs(tt.x.x); got != tt.want {
			t.Errorf("[KO] (%v, %v) = %v want %v", tt.name, tt.x.x, got, tt.want)
		} else {
			t.Logf("[OK] (%v, %v) = %v want %v", tt.name, tt.x.x, got, tt.want)
		}
	}
}

/*
=== RUN   TestClimStairs
    prog.go:35: [OK] (01 floor, 1) = 1 want 1
    prog.go:35: [OK] (02 floors, 2) = 2 want 2
    prog.go:35: [OK] (04 floors, 4) = 5 want 5
--- PASS: TestClimStairs (0.00s)
PASS
*/ 
