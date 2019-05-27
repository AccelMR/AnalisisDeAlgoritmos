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

std::vector<int>
merge(std::vector<int>& left, std::vector<int>& right);
std::vector<int>
mergeSort(std::vector<int>& m);

int
partition(std::vector<int>& v,
          unsigned int start,
          unsigned int stop,
          unsigned int position);
void
quickSort(std::vector<int>& v,
          unsigned int low = 0,
          unsigned int high = std::numeric_limits<int>::max());

int
linearSearch(std::vector<int>& vec, int x);

int
binarySearch(std::vector<int> numbers,
             int x,
             int left = 0,
             int right = std::numeric_limits<int>::max());

/** 
 * @brief Take time of function
 */
using callBackFunc = std::vector<int>(*)(std::vector<int>&);

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

//   for(int i = 1000; i < 10000; i += 200)
//   {
//     std::vector<int> best = createtVectorInc(i);
//     std::vector<int> worst = createtVectorDes(i);
//     std::vector<int> avarage = createtVectorRan(i, 0, i + 1);
// 
//     timeTakenInFunc(insertionSort, best);
//     timeTakenInFunc(insertionSort, worst);
//     timeTakenInFunc(insertionSort, avarage);
// 
//   }
  for(int i = 1000; i < 3000; i+=10)
  {
    std::vector<int> best = createtVectorInc(i);
    std::vector<int> worst = createtVectorDes(i);
    std::vector<int> avarage = createtVectorRan(i, 0, i + 1);

    timeTakenInFunc(mergeSort, best);
    timeTakenInFunc(mergeSort, worst);
    timeTakenInFunc(mergeSort, avarage);
  }

//   for(int i = 1000; i < 2000; i += 200)
//   {
//     std::vector<int> best = createtVectorInc(i);
//     std::vector<int> worst = createtVectorDes(i);
//     std::vector<int> avarage = createtVectorRan(i, 0, i + 1);
// 
// 
// 
//   }

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
 * @brief helper to merge sort
 * @param left part of vector 
 * @param right part of vector
 */
std::vector<int>
merge(std::vector<int>& left, std::vector<int>& right)
{
  std::vector<int> result;
  while((int) left.size() > 0 || (int) right.size() > 0) {
    if((int) left.size() > 0 && (int) right.size() > 0) {
      if((int) left.front() <= (int) right.front()) {
        result.push_back((int) left.front());
        left.erase(left.begin());
      }
      else {
        result.push_back((int) right.front());
        right.erase(right.begin());
      }
    }
    else if((int) left.size() > 0) {
      for(int i = 0; i < (int) left.size(); i++)
        result.push_back(left[i]);
      break;
    }
    else if((int) right.size() > 0) {
      for(int i = 0; i < (int) right.size(); i++)
        result.push_back(right[i]);
      break;
    }
  }
  return result;
}

/** 
 * @brief Function that will sort a vector using merge method
 * @param vector to sort
 * @return a new vector sorted
 */
std::vector<int>
mergeSort(std::vector<int>& m)
{
  if(m.size() <= 1)
  {
    return m;
  }

  std::vector<int> left, right, result;
  int middle = ((int) m.size() + 1) / 2;

  for(int i = 0; i < middle; i++) 
  {
    left.push_back(m[i]);
  }

  for(int i = middle; i < (int) m.size(); i++)
  {
    right.push_back(m[i]);
  }

  left = mergeSort(left);
  right = mergeSort(right);
  result = merge(left, right);

  m = result;

  return result;
}

/** 
 * @brief function to find the new pivot of vector
 * @param vector to look in
 * @param start point
 * @param end point
 */
// int
// partition(std::vector<int>& a, int start, int end) {
//   unsigned int pivot = a[start];
//   unsigned int from_left = start + 1;
//   unsigned int from_right = end;
//   unsigned int tmp;
// 
//   while(from_left != from_right) {
//     if(a[from_left] <= pivot) from_left++;
//     else {
//       while((from_left != from_right) && (pivot < a[from_right])) from_right--;
//       tmp = a[from_right];
//       a[from_right] = a[from_left];
//       a[from_left] = tmp;
//     }
//   }
// 
//   if(a[from_left] > pivot) from_left--;
//   a[start] = a[from_left];
//   a[from_left] = pivot;
// 
//   return from_left;
// }

int 
partition(std::vector<int>& v, 
          unsigned int start,
          unsigned int stop, 
          unsigned int position)
{
  std::swap(v[start], v[position]);

  // partition values
  unsigned int low = start + 1;
  unsigned int high = stop;
  while(low < high)
    if(v[low] < v[start])
      low++;
    else if(v[--high] < v[start])
      std::swap(v[low], v[high]);

  // then swap pivot back into place
  std::swap(v[start], v[--low]);
  return low;
}

/** 
 * @brief Quick sorting of a vector
 * @param vector that is going to be sorted
 * @param Start index in vector. 
 * NOTE: if you don't send anything then index will be 0, which is good for default sort
 * @param ending index
 * NOTE: if you don't send anything it'll be the size of your vector.
 *
 * FINAL NOTE: if just want to sort, send just the vector, don't worry about params
 */
// void
// quickSort(std::vector<int>& a, int p, int r)
// {
//   if(r == std::numeric_limits<int>::max())
//   {
//     r = a.size() - 1;
//   }
// 
//   if(p < r)
//   {
//     int q = partition(a, p, r);
//     quickSort(a, p, q - 1);
//     quickSort(a, q + 1, r);
//   }
// }
void 
quickSort(std::vector<int>& v, unsigned int low, unsigned int high)
{
  if(high == std::numeric_limits<int>::max())
  {
    high = v.size() - 1;
  }
  // no need to sort a vector of zero or one elements
  if(low >= high)
    return;

  // select the pivot value
  unsigned int pivotIndex = (low + high) / 2;

  // partition the vector
  pivotIndex = partition(v, low, high, pivotIndex);

  // sort the two sub vectors
  if(low < pivotIndex)
    quickSort(v, low, pivotIndex);
  if(pivotIndex < high)
    quickSort(v, pivotIndex + 1, high);
}


/** 
 * @brief Search for [param] X in vector, if search finds it then returns its index
 *        otherwise returns -1
 * @param[in] number looking for
 */
int
linearSearch(std::vector<int>& vec, int x)
{
  int i = 0;
  for(auto& it : vec)
  {
    if(it == x)
    {
      return i;
    }

    ++i;
  }

  return -1;
}

/**
 * @brief Search for [param] X in vector, if search finds it then returns its index
 *        otherwise returns -1
 * @param[in] number looking for
 */
int
binarySearch(std::vector<int> numbers,
             int x,
             int left,
             int right)
{
  if (right == std::numeric_limits<int>::max())
  {
    right = numbers.size() - 1;
  }

  if(right >= left)
  {
    int mid = left + (right - left) / 2;

    if(numbers[mid] == x)
      return mid;

    if(numbers[mid] > x)
      return binarySearch(numbers, x, left, mid - 1);

    return binarySearch(numbers, x, mid + 1, right);
  }

  return -1;
}



double
_timeTakenInFunc(callBackFunc pfunc, std::vector<int>& vec, 
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

  fs << elapsed.count() << "   Tomo en " << s2  << " " << vec.size() << " iteraciones\n";

  /*std::cout << "Took " << elapsed.count() << " sec.\n" << std::endl;*/

  fs.close();

  return elapsed.count();
}

