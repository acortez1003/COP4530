#include <iostream>

template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size) : currentSize{0}
{
    if(size == 0)
        size = default_capacity;
    table.resize(prime_below(size));
}

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const
{
    size_t index = myhash(k);
    auto &bucket = table[index];

    for(auto &pair : bucket)
    {
        if(pair.first == k)
            return true;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
{
    size_t index = myhash(kv.first);
    auto &bucket = table[index];

    for(auto &pair : bucket)
    {
        if(pair.first == kv.first && pair.second == kv.second)
            return true;
    }
    return false;
}

template<typename K, typename V>
size_t HashTable<K, V>::size() const
{
    return currentSize;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> &kv)
{
    size_t index = myhash(kv.first);
    auto &bucket = table[index];
    for(auto itr = bucket.begin(); itr != bucket.end(); ++itr)
    {
        if(itr->first == kv.first)
        {
            if(itr->second == kv.second)
            // pair exists
                return false;  
            else            
            // update value
                itr->second = kv.second;
        }
    }
    bucket.push_back(kv);   // add kv to list
    ++currentSize;
    if(currentSize > table.size())
        rehash();

    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> &&kv)
{
    size_t index = myhash(kv.first);
    auto &bucket = table[index];
    for(auto itr = bucket.begin(); itr != bucket.end(); ++itr)
    {
        if(itr->first == kv.first)
            if(itr->second == kv.second)
                return false;
            
            else
                itr->second = std::move(kv.second);
    }

    bucket.push_back(std::move(kv));
    
    if(++currentSize > table.size())
        rehash();
    
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K &k)
{
    size_t index = myhash(k);
    auto &bucket = table[index];
    for(auto itr = bucket.begin(); itr != bucket.end(); ++itr)
    {
        if(itr->first == k)
        {
            bucket.erase(itr);
            --currentSize;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear()
{
    makeEmpty();
}

template<typename K, typename V>
void HashTable<K, V>::dump() const
{
    int i = 0;
    int index = 0;
    for(auto &bucket : table)
    {
        std::cout << "\n[" << index << "] ";
        for(auto &pair : bucket)
        {
            if(i != 0) // first pair
                std::cout << " : ";
            std::cout << pair.first << " " << pair.second;
            ++i;
        }
        ++index;
    }
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
        return false;
    std::string line;
    while(std::getline(file, line))
    {
        std::istringstream iss(line);
        K key;
        V value;
        if(!(iss >> key >> value))
            return false;
        insert(std::make_pair(key, value));
    }

    file.close();
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename)
{
    std::ofstream file;
    file.open(filename);
    if(!file)
        return false;
    
    int i = 0;
    int index = 0;
    for(auto &bucket : table)
    {
        std::cout << "\n[" << index << "] ";
        for(auto &pair : bucket)
        {
            if(i != 0) // first pair
                std::cout << " : ";
            std::cout << pair.first << " " << pair.second;
            ++i;
        }
        ++index;
    }
    
    file.close();
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
    for(auto &list : table)
        list.clear();
    currentSize = 0;
}

template<typename K, typename V>
void HashTable<K, V>::rehash()
{
    size_t newSize = table.size() * 2;
    std::vector<std::list<std::pair<K, V>>> newTable(newSize);

    for(auto &bucket : table)
    {
        for(auto &pair : bucket)
        {
            size_t newIndex = myhash(pair.first);
            newTable[newIndex].push_back(pair);
        }
    }

    table = std::move(newTable);    
    currentSize = 0;

    for(auto &bucket : table)
        currentSize += bucket.size();
}

template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
    static std::hash<K> hf;
    return hf(k) % table.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

