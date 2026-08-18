package datasource

import (
	"testing"

	"github.com/google/uuid"
)

func TestGetShardIndex(t *testing.T) {
	tests := []struct {
		name string
		uuid string
		want int
	}{
		{"first hex digit 0 -> shard 0", "00000000-0000-0000-0000-000000000000", 0},
		{"first hex digit 3 -> shard 0", "30000000-0000-0000-0000-000000000000", 0},
		{"first hex digit 4 -> shard 1", "40000000-0000-0000-0000-000000000000", 1},
		{"first hex digit 7 -> shard 1", "70000000-0000-0000-0000-000000000000", 1},
		{"first hex digit 8 -> shard 2", "80000000-0000-0000-0000-000000000000", 2},
		{"first hex digit b -> shard 2", "b0000000-0000-0000-0000-000000000000", 2},
		{"first hex digit c -> shard 3", "c0000000-0000-0000-0000-000000000000", 3},
		{"first hex digit f -> shard 3", "f0000000-0000-0000-0000-000000000000", 3},
	}

	s := &ImageStorage{}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			id := uuid.MustParse(tt.uuid)
			if got := s.getShardIndex(id); got != tt.want {
				t.Fatalf("getShardIndex(%q) = %d, want %d", id.String(), got, tt.want)
			}
		})
	}
}

func TestGetShardIndexInRange(t *testing.T) {
	s := &ImageStorage{}
	for i := 0; i < 1000; i++ {
		idx := s.getShardIndex(uuid.New())
		if idx < 0 || idx >= 4 {
			t.Fatalf("getShardIndex = %d and out of possible range", idx)
		}
	}
}
