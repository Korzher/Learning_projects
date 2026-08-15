package cache

import (
	"fmt"
	"sync"
)

type Cache[K comparable, V any] struct {
	capacity int
	items    map[K]*node[K, V]
	head     *node[K, V]
	tail     *node[K, V]
	mutex    sync.RWMutex
}

type node[K comparable, V any] struct {
	value V
	key   K
	next  *node[K, V]
	prev  *node[K, V]
}

func NewCache[K comparable, V any](capacity int) *Cache[K, V] {
	if capacity <= 0 {
		fmt.Println("Capacity must be positive")
		return nil
	}
	return &Cache[K, V]{
		capacity: capacity,
		items:    make(map[K]*node[K, V]),
		head:     nil,
		tail:     nil,
	}
}

func (c *Cache[K, V]) Set(key K, value V) {
	c.mutex.Lock()
	defer c.mutex.Unlock()
	node, exists := c.items[key]
	if exists {
		node.value = value
		c.moveFront(node)
	} else {
		if len(c.items) < c.capacity {
			c.addNode(key, value)
		} else {
			delete(c.items, c.tail.key)
			c.tail = c.tail.prev
			if c.tail != nil {
				c.tail.next = nil
			}
			c.addNode(key, value)
		}
	}
}

func (c *Cache[K, V]) addNode(key K, value V) {
	newNode := &node[K, V]{value: value, key: key, next: c.head, prev: nil}
	c.items[key] = newNode
	if c.head != nil {
		c.head.prev = newNode
	}
	c.head = newNode
	if c.tail == nil {
		c.tail = newNode
	}
}

func (c *Cache[K, V]) Get(key K) (V, bool) {
	c.mutex.RLock()
	defer c.mutex.RUnlock()
	node, exists := c.items[key]
	if !exists {
		var res V
		return res, false
	}
	if node == c.head {
		return node.value, true
	}

	c.moveFront(node)
	return node.value, true
}

func (c *Cache[K, V]) moveFront(node *node[K, V]) {

	if node.prev != nil {
		node.prev.next = node.next
	}

	if node.next != nil {
		node.next.prev = node.prev
	}

	if node == c.tail {
		c.tail = node.prev
		if c.tail != nil {
			c.tail.next = nil
		}
	}

	node.next = c.head
	node.prev = nil
	if c.head != nil {
		c.head.prev = node
	}
	c.head = node
	if c.tail == nil {
		c.tail = node
	}
}

func (c *Cache[K, V]) Clear() {
	c.mutex.Lock()
	defer c.mutex.Unlock()
	c.items = make(map[K]*node[K, V])
	c.head = nil
	c.tail = nil
}
