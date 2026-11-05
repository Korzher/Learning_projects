package cache

import (
	"sync"
	"testing"
)

func TestLRUCache(t *testing.T) {
	t.Run("Стандартное поведение", func(t *testing.T) {
		cache := NewCache[string, int](2)
		if cache == nil {
			t.Fatal("Кэш не должен быть пустым")
		}

		cache.Set("a", 1)
		cache.Set("b", 2)

		if val, ok := cache.Get("a"); !ok || val != 1 {
			t.Errorf("Ожидалось a=1, получено %d, ok=%t", val, ok)
		}
		if val, ok := cache.Get("b"); !ok || val != 2 {
			t.Errorf("Ожидалось b=2, получено %d, ok=%t", val, ok)
		}
	})

	t.Run("Удаление элемента при превышении вместимости", func(t *testing.T) {
		cache := NewCache[string, int](2)
		cache.Set("a", 1)
		cache.Set("b", 2)
		cache.Set("c", 3)

		if _, ok := cache.Get("a"); ok {
			t.Error("Ожидалось, что 'a' будет удалено")
		}
		if val, ok := cache.Get("b"); !ok || val != 2 {
			t.Errorf("Ожидалось b=2, получено %d, ok=%t", val, ok)
		}
		if val, ok := cache.Get("c"); !ok || val != 3 {
			t.Errorf("Ожидалось c=3, получено %d, ok=%t", val, ok)
		}
	})

	t.Run("Get перемещает элементы вперед", func(t *testing.T) {
		cache := NewCache[string, int](2)
		cache.Set("a", 1)
		cache.Set("b", 2)

		cache.Get("a")
		cache.Set("c", 3)

		if _, ok := cache.Get("b"); ok {
			t.Error("Ожидалось 'b' будет удалено")
		}
		if val, ok := cache.Get("a"); !ok || val != 1 {
			t.Errorf("Ожидалось a=1, получено %d, ok=%t", val, ok)
		}
	})

	t.Run("Set обновляет значение и двигает элемент вперед", func(t *testing.T) {
		cache := NewCache[string, int](2)
		cache.Set("a", 1)
		cache.Set("b", 2)
		cache.Set("a", 10)

		cache.Set("c", 3)

		if _, ok := cache.Get("b"); ok {
			t.Error("Ожидалось 'b' будет удалено")
		}
		if val, ok := cache.Get("a"); !ok || val != 10 {
			t.Errorf("Ожидалось a=10, получено %d, ok=%t", val, ok)
		}
	})

	t.Run("Get с несущещствующим ключом", func(t *testing.T) {
		cache := NewCache[string, int](2)
		cache.Set("a", 1)

		if val, ok := cache.Get("b"); ok || val != 0 {
			t.Errorf("Ожидалось нулевое значение и false, получено %d, ok=%t", val, ok)
		}
	})

	t.Run("Очистка кеша", func(t *testing.T) {
		cache := NewCache[string, int](2)
		cache.Set("a", 1)
		cache.Set("b", 2)

		cache.Clear()

		if _, ok := cache.Get("a"); ok {
			t.Error("Кэш должен быть очищен")
		}
		if _, ok := cache.Get("b"); ok {
			t.Error("Кэш должен быть очищен")
		}
	})

	t.Run("Конкурентность", func(t *testing.T) {
		cache := NewCache[int, int](10)
		var wg sync.WaitGroup

		for i := 0; i < 100; i++ {
			wg.Add(1)
			go func(i int) {
				defer wg.Done()
				cache.Set(i, i*2)
			}(i)
		}
		wg.Wait()

		for i := 0; i < 100; i++ {
			wg.Add(1)
			go func(i int) {
				defer wg.Done()
				cache.Get(i)
			}(i)
		}
		wg.Wait()

		if cache == nil {
			t.Error("Кеш не должен быть пустым после конкурентного доступа")
		}
	})

	t.Run("Нулевая вместимость", func(t *testing.T) {
		cache := NewCache[string, int](0)
		if cache != nil {
			t.Error("Кеш с нулевой вместимостью должен возвращать nil")
		}
	})
}
