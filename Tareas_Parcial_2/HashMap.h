/************************************************************************/
/**
 * @file HashMap.h
 * @author AccelMR
 * @date 2019/07/04
 * @brief Small HashMap class 
 */
 /************************************************************************/
#pragma once

/************************************************************************/
/*
 * Includes
 */                                                                     
/************************************************************************/
#include <vector>
#include <optional>

/* =^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=   =^..^=  */
/* =^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=   =^..^=  */

// template <typename T>
// struct HashCompute
// {
//   size_t operator()(const T& key, const int& hashSize = 1000) const
//   {
//     return std::hash<T>() (key) % hashSize;
//   }
// };

 template <typename K,typename V>
 class HashMap
 {
 public:

   /** 
    * @brief Actual constructor
    * @param size of map. DEFAULT = 100
    */
   HashMap(size_t size = 100): m_map(size), m_currSize(0){}

   /** 
    * @brief Destructor
    */
   ~HashMap() {}

   /** 
    * @brief Insert function
    * @param Key, how you gonna recognize the value send
    * @param Value, which value is going to be saved
    */
   bool insert(const K& key, const V& value);

   /** 
    * @brief removes a value and key
    * @param key of which value gonna delete
    */
   bool remove(const K& key);

   /** 
    * @brief returns the value
    * @param key of which value gonna return
    */
   V& operator[](const K& key);

 private:

   /** 
    * @brief function where hash occurs
    * @param key that will be transformed into a int 
    */
   int myhash(const K& key) const {
     static std::hash<K> hash_fn;
     return (hash_fn(key) % m_map.size());
   }

   /** 
    * @brief the actual container where it'll be saved
    */
   std::vector<std::pair<K, V>> m_map;

   /** 
    * @brief Actual size of table
    */
   unsigned int m_currSize;

   typedef typename std::pair<K, V> mapIterator;

 };


 template <typename K, typename V>
 V& HashMap<K, V>::operator[](const K& key)
 {
   mapIterator& it = m_map[myhash(key)];

   if (it.first == key)
   {
     return it.second;
   }
 }

 template <typename K, typename V>
 bool HashMap<K, V>::insert(const K& key, const V& value)
 {
   mapIterator& it = m_map[myhash(key)];

   if(it.first != "")
   {
     it.first = key;
     it.second = value;
     return true;
   }

   //There's already a key like this one
   return false;
 }

