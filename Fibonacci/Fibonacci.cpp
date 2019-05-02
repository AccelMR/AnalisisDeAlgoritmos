/************************************************************************/
/**
 * @file Fibonacci.cpp
 * @author AccelMR
 * @date 2019/05/02
 * @brief Translation from Fibonacci code used in class to cpp style
 */
 /************************************************************************/

/************************************************************************/
/*
 * Includes
 */                                                                     
/************************************************************************/
#include <iostream>
#include <chrono>
#include <string>

//defined pointer function
typedef int(*callBackFunc)(int);

int FibonacciRecursiva(int n);
int FibonacciNORecursiva(int n);
double timeTookInFunc(callBackFunc pfunc, int num, int& res);
void LogInfo(int res, double time, std::string str = "NO recursive ");

int main()
{
  int num = 0, res = 0;
  double timeTook = 0.0;

  std::cout << "Fibonacci sequence number: ";
  std::cin >> num;

  timeTook = timeTookInFunc(&FibonacciNORecursiva, num, res);
  LogInfo(res, timeTook);

  timeTook = timeTookInFunc(&FibonacciRecursiva, num, res);
  LogInfo(res, timeTook,"");

  return 0;
}

/** 
 * @brief Fibonacci algorithm using recursive
 */
int
FibonacciRecursiva(int n)
{
  if (n <= 1)
  {
    return n;
  }
  else
  {
    return FibonacciRecursiva(n - 1) + FibonacciRecursiva(n - 2);
  }
}

/** 
 * @brief Fibonacci algorithms using no recursive
 */
int
FibonacciNORecursiva(int n)
{
  //initialize variable
  int n1 = 0, n2 = 1;

  if(n <= 1)
  {
    return n;
  }
  else
  {
    int tmp = 0;
    for(int i = 0; i < n - 1; ++i)
    {
      tmp = n1 + n2;
      n1 = n2;
      n2 = tmp;
    }
    return tmp;
  }
}

/** 
 * @brief it will return the time elapsed in function
 * @param function ptr
 * @param num that will be passed for pointer function
 * @param[out] ref where result will be allocated
 */
double 
timeTookInFunc(callBackFunc pfunc, int num, int& res)
{
  // Record start time
  auto start = std::chrono::high_resolution_clock::now();

  //execute function
  res = pfunc(num);

  // Record end time
  auto finish = std::chrono::high_resolution_clock::now();

  //delta time
  std::chrono::duration<double> elapsed = finish - start;

  return elapsed.count();
}

/** 
 * @brief It'll print info in console
 * @param the result from ptr function
 * @param Time elapsed 
 * @param if it was recursive or not, default = NO
 */
void
LogInfo(int res, double time, std::string str)
{
  std::string  s = "The result using " + str + " Fibonacci was " + 
    std::to_string(res) + " and took " + std::to_string(time) + "\n";
  std::cout << s << std::endl;
}
