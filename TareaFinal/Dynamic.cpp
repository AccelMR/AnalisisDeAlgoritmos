#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;
using uint = uint32_t;

void lcs(string X, string Y, uint m, uint n) 
{
  vector<vector<uint>> L(0);
  L.resize(m + 1);

  for(auto& it : L) 
  {
    it.resize(n + 1);
  }

  for(uint i = 0; i < m + 1; ++i) 
  {
    for(uint j = 0; j < n + 1; ++j) 
    {
      if(i == 0 || j == 0) 
      {
        L[i][j] = 0;
      }
      else 
      {
        if(X[i - 1] == Y[j - 1]) 
        {
          L[i][j] = L[i - 1][j - 1] + 1;
        }
        else 
        {
          L[i][j] = static_cast<uint>(fmax(L[i - 1][j], L[i][j - 1]));
        }
      }
    }
  }

  uint index = L[m][n];
  string lcs("");
  lcs.resize(index + 1);

  uint i = m;
  uint j = n;
  while((i > 0) && (j > 0)) 
  {
    if(X[i - 1] == Y[j - 1]) {
      lcs[index - 1] = X[i - 1];
      --i;
      --j;
      --index;
    }
    else 
    {
      if(L[i - 1][j] > L[i][j - 1]) 
      {
        --i;
      }
      else {
        --j;
      }
    }
  }

  cout << "La subsecuencia mas larga comun de " << X.c_str() << " y de " << Y.c_str() << 
    " es " << lcs.c_str() << endl;
}

int main()
{
  //Se declaran secuencias
  string X("TTCGCATCGGGTTG");
  string Y("TGACCGTGTGTCACG");

  //Se toma el tiempo actual
  time_point< steady_clock> start =  high_resolution_clock::now();

  std::cout << "---Dynamic Programming---" << std::endl;
  lcs(X, Y, X.size(), Y.size());

  //Se toma el tiempo final
  time_point< steady_clock> end = high_resolution_clock::now();

  //Se saca delta interno
  cout << "Terminado en: " << duration_cast< nanoseconds>(end - start).count() / 1e+9 <<
    " segundos." << endl;

  return 0;
}
