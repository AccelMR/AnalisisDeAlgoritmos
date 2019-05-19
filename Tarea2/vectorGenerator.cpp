/*************************************************************************/
/**
 * @file vectorGenerator.cpp
 * @author AccelMR
 * @date 2019/05/09
 * @brief Vector generator
 */
 /************************************************************************/

/************************************************************************/
/*
 * Includes
 */                                                                     
/************************************************************************/
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>

/************************************************************************/
/*
 * Forward declarations
 */                                                                     
/************************************************************************/
std::vector<int>
createtVectorDes(int n);
std::vector<int>
createtVectorInc(int n);
std::vector<int>
createtVectorRan(int n, int minRange, int maxRange);
void
printVector(std::vector<int>&);
void
buubleSort(std::vector<int>&);
void
insertionSort(std::vector<int>&);

/** 
 * @brief Take time of function
 */
using callBackFunc = void(*)(std::vector<int>&);
double
_timeTakenInFunc(callBackFunc pfunc, 
               std::vector<int>&, 
               std::string,
               std::string);
#define timeTakenInFunc(a,b) _timeTakenInFunc(a, b, #a, #b)


int main()
{
//   for(int i = 1000; i < 10000; i += 200)
//   {
//     std::vector<int> a = createtVectorInc(i);
//     std::vector<int> b = createtVectorDes(i);
//     std::vector<int> c = createtVectorRan(i, 0, i + 1);
// 
//     timeTakenInFunc(buubleSort, a, "BubbleMejor.txt");
//     timeTakenInFunc(buubleSort, b, "BubblePeor.txt");
//     timeTakenInFunc(buubleSort, c, "BubblePromedio.txt");
//   
//   }

  for(int i = 1000; i < 10000; i += 200)
  {
    std::vector<int> best = createtVectorInc(i);
    std::vector<int> worst = createtVectorDes(i);
    std::vector<int> avarage = createtVectorRan(i, 0, i + 1);

    timeTakenInFunc(insertionSort, best);
    timeTakenInFunc(insertionSort, worst);
    timeTakenInFunc(insertionSort, avarage);

  }

  //buubleSort(a);
  //insertionSort(a);

  return 0;
}

/** 
 * @brief Function that creates a vector and fills it decreasing 
 * @param int how long the vector is going to be
 */
std::vector<int>
createtVectorDes(int n)
{
  std::vector<int> vec;
  vec.resize(n);

  for(int i = n - 1; i > 0; i--)
  {
    vec[std::abs(i - n +1)] = i;
  }
  return vec;
}

/**
 * @brief Function that creates a vector and fills increasing 
 */
std::vector<int>
createtVectorInc(int n)
{
  std::vector<int> vec;
  vec.resize(n);

  for(int i = 0; i < n; i++)
  {
    vec[i] = i;
  }
  return vec;
}

/**
 * @brief Function that creates a vector and fills it with random numbers
 * @param int how long the vector is going to be
 */
std::vector<int>
createtVectorRan(int n, int minRange, int maxRange)
{
  std::random_device dev;
  std::mt19937 rng(dev());

  std::vector<int> vec;
  vec.resize(n);

  for(int i = 0; i < n; i++)
  {
    std::uniform_int_distribution<std::mt19937::result_type> dist6(minRange, maxRange);
    vec[i] = dist6(rng);
  }
  return vec;

}

/** 
 * @brief prints vector 
 * @param reference of vector that's going to print
 */
void
printVector(std::vector<int>& vec)
{
  for (auto& it: vec)
  {
    std::cout << it << ", ";
  }
  std::cout << std::endl;
}

/** 
 * @brief sort the vector from min to max using bubble technique
 * @param reference of vector that's going to sort
 */
void
buubleSort(std::vector<int>& vec)
{
  bool swapp = true;
  while(swapp) {
    swapp = false;
    for(size_t i = 0; i < vec.size() - 1; i++) {
      if(vec[i] > vec[i + 1]) {
        vec[i] += vec[i + 1];
        vec[i + 1] = vec[i] - vec[i + 1];
        vec[i] -= vec[i + 1];
        swapp = true;
      }
    }
  }
}

/**
 * @brief sort the vector from min to max using insertion technique
 * @param reference of vector that's going to sort
 */
void
insertionSort(std::vector<int>& arr)
{
  int i, key, j;
  for(i = 1; i < arr.size(); i++)
  {
    key = arr[i];
    j = i - 1;

    while(j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

/**
 * @brief it will return the time elapsed in function
 * @param function ptr
 * @param num that will be passed for pointer function
 * @param[out] ref where result will be allocated
 */
double
_timeTakenInFunc(callBackFunc pfunc, std::vector<int>& vec, std::string s,
                 std::string s2)
{
  // Record start time
  auto start = std::chrono::high_resolution_clock::now();

  pfunc(vec);

  // Record end time
  auto finish = std::chrono::high_resolution_clock::now();

  //delta time
  std::chrono::duration<double> elapsed = finish - start;



  std::fstream fs;
  fs.open(s, std::fstream::app);

  fs << elapsed.count() << "   Tomo en " << s2  << vec.size() << " iteraciones\n\n";

  /*std::cout << "Took " << elapsed.count() << " sec.\n" << std::endl;*/

  fs.close();

  return elapsed.count();
}

