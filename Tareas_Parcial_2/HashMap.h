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
     int hashed = 0;

     int street = 0;
     int house = 0;
     int person = 0;
     int digits = 0;

     float precision = 0.0f;

     street = key % m_map.size();
     house = std::abs(std::floor(key / m_map.size()));

     precision = static_cast<float>(key) / static_cast<float>(m_map.size());
     precision = std::fabs(precision) - house;

     person = static_cast<int>(precision * 1000);

     digits = street > 0 ? static_cast<int>(log10(static_cast<double>(street))) + 1 : 1;

     std::string toConcat;
     toConcat += std::to_string(digits);
     toConcat += std::to_string(street);
     toConcat += std::to_string(house);

     if(person < 10) { toConcat += std::to_string(0); }
     toConcat += std::to_string(person);

     toConcat += key > 0 ? std::to_string(1) : std::to_string(2);

     hashed = atoi(toConcat.c_str());
     return hashed;
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

