#include <map>
#include <list>
#include <string>
#include <iostream>
#include <stdexcept>

template <class K, class V>
class Cache {
 public:
  Cache(unsigned int capacity) : capacity_(capacity) {}
  ~Cache() {}
  bool set(const K &key, const V &value) {}
  V get(const K &key) {}
  void get(const K &key, V &value) {}
  unsigned int get_capacity() const { return capacity_; }
 private:
  const unsigned int capacity_;
};

template <class K, class V>
class LRUCache : public Cache<K, V> {
 public:
  LRUCache(unsigned int capacity) : Cache<K, V>(capacity) {}
  ~LRUCache() {}

  V get(const K &key) {
    V value;
    get(key, value);
    return value;
  }
  
  void get(const K &key, V &value) {
    if (existed(key)) {
      promoted(key);
      table_[key] = std::make_pair(table_[key].first, list_.begin());
      value = table_[key].first;
    } else {
      throw std::out_of_range("item not contained in this table!");
    }
  }

  bool set(const K &key, const V &value) {
    unsigned int max_size = this->get_capacity();
    if (!max_size) return 1;
    if (existed(key)) {
      promoted(key);
      table_[key] = std::make_pair(value, list_.begin()); 
    } else {
      if (table_.size() >= max_size) {
        table_.erase(list_.back());
        list_.pop_back();
      }
      list_.push_front(key);
      table_[key] = std::make_pair(value, list_.begin()); 
    }
    return 0;
  }
 private:
  void promoted(const K &key) {
    list_.erase(table_[key].second);
    list_.push_front(key);
  }
  bool existed(const K &key) {
    return (table_.find(key) != table_.end());
  }
 private:
  std::map<K, std::pair<V, typename std::list<K>::iterator> > table_;
  std::list<K> list_;
};

int main() {
  LRUCache<std::string, std::string> lc(2);
  lc.set("2", "1");
  lc.set("2","2");
  std::cout << lc.get("2") << std::endl;
  lc.set("1","3");
  lc.set("4","1");
  std::cout << lc.get("2") << std::endl;
  return 0;
}
