package morestrings

import "testing"

// TestReverseRunes, run it by "go test" at terminal, or ":GoTest" in vim.
func TestReverseRunes(t *testing.T) {
	cases := []struct {
		in, want string
	}{
		{"Hello, world", "dlrow ,olleH"},
		{`Hello, 世界`, `界世 ,olleH`}, // both of `` and "" are all correct at here.
		{"", ""},
	}

	for _, c := range cases {
		got := ReverseRunes(c.in)
		if got != c.want {
			t.Errorf("ReserveRunes(%s) == (%s), want %q", c.in, got, c.want)
		}
	}
}
