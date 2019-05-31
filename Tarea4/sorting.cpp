#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>


std::vector<int>
createtVectorDes(int n);
std::vector<int>
createtVectorInc(int n);
std::vector<int>
createtVectorRan(int n, int minRange, int maxRange);


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


void countingSort(std::vector<int>& vec)
{
  int maxValue = vec.size();
  int* counting = new int[maxValue];
  int k = 0;
  for(int i = 0; i < maxValue; i++)
    counting[i] = 0;
  for(int i = 0; i < vec.size(); i++)
    counting[vec[i]]++;
  for(int i = 0; i < maxValue; i++)
  {
    int count = counting[i];
    for(int j = 0; j < count; j++)
    {
      vec[k] = i;
      k++;
    }
  }
}

std::vector<int> radixHelper(std::vector<int>& arr, int spot)
{
  std::vector<int> count(10, 0);

  std::vector<int> retVal(arr.size(), 0);

  for(int i = 0; i < arr.size(); ++i)//Fill count array
  {
    int temp = arr[i];
    for(int j = 0; j < spot; ++j)
    {
      temp /= 10;
    }
    count[temp % 10]++;
  }

  for(int i = 1; i < count.size(); ++i)//Sum count array
  {
    count[i] += count[i - 1];
  }

  for(int i = arr.size() - 1; i >= 0; --i)//Find which values match what spots //complicated part
  {
    int temp = arr[i];
    for(int j = 0; j < spot; ++j)
    {
      temp /= 10;
    }

    temp = temp % 10;

    for(int j = 0; j < count.size(); ++j)
    {
      if(j == temp)
      {
        retVal[--count[j]] = arr[i];
      }
    }
  }
  return retVal;
}

void radixSort(std::vector<int>& arr)
{
  for(int i = 0; i < 10; ++i)
  {
    arr = radixHelper(arr, i);
  }
}

void BucketSort(std::vector<int>& data) {
  int minValue = data[0];
  int maxValue = data[0];

  for(int i = 1; i < data.size() -1; i++)
  {
    if(data[i] > maxValue)
      maxValue = data[i];
    if(data[i] < minValue)
      minValue = data[i];
  }

  int bucketLength = maxValue - minValue + 1;
  std::vector<int>* bucket = new std::vector<int>[bucketLength];

  for(int i = 0; i < bucketLength; i++)
  {
    bucket[i] = std::vector<int>();
  }

  for(int i = 0; i < data.size() - 1; i++)
  {
    bucket[data[i] - minValue].push_back(data[i]);
  }

  int k = 0;
  for(int i = 0; i < bucketLength; i++)
  {
    int bucketSize = bucket[i].size();

    if(bucketSize > 0)
    {
      for(int j = 0; j < bucketSize; j++)
      {
        data[k] = bucket[i][j];
        k++;
      }
    }
  }
}


int main()
{
  for(int i = 1000; i < 10000; i += 200)
  {
    std::vector<int> best     = createtVectorInc(i);
    std::vector<int> worst    = createtVectorDes(i);
    std::vector<int> avarage  = createtVectorRan(i, 0, i + 1);

    timeTakenInFunc(radixSort, best);
    timeTakenInFunc(radixSort, worst);
    timeTakenInFunc(radixSort, avarage);
  
  }
  return 0;
}

double
_timeTakenInFunc(callBackFunc pfunc,
                 std::vector<int>& vec,
                 std::string s,
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
  fs.open(s + s2, std::fstream::app);

  fs << elapsed.count() << "\t\tTomo en " << s2 << " " << vec.size() << " iteraciones\n";

  /*std::cout << "Took " << elapsed.count() << " sec.\n" << std::endl;*/

  fs.close();

  return elapsed.count();
}