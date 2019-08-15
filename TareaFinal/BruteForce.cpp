#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;
using uint = uint32_t;


vector<string> obtenerSubsecuencias(string secuencia)
{
  //n size of String
  uint n = secuencia.size();

  auto numeroDeSubsecuencias = static_cast<uint>(pow(2, n));

  vector<string> subsecuencias(0);
  subsecuencias.resize(numeroDeSubsecuencias);

  for(uint i = 1; i < numeroDeSubsecuencias; ++i) 
  {
    string subsecuencia;
    for(uint j = 0; j < n; ++j)
    {
      if(i & (1 << j))
      {
        subsecuencia += secuencia[j];
      }
    }
    subsecuencias[i-1] = subsecuencia;
  }
  return subsecuencias;
}

string compararSubsecuencias(vector<string> subsecuencias1,
                             vector<string> subsecuencias2) 
{
  string lcs;
  for(const auto& i : subsecuencias1) 
  {
    for(const auto& j : subsecuencias2) 
    {
      if(i == j) 
      {
        if(lcs.size() < i.size()) 
        {
          lcs = i;
        }
      }
    }
  }
  return lcs;
}

int main() 
{
  //Se declaran secuencias
  string secuencia1 = "TTCGCATCGGGTTG";
  string secuencia2 = "TGACCGTGTGTCACG";
  
  //Se obtienen ambas secuencias
  vector<string> subsecuencias1 = obtenerSubsecuencias(secuencia1);
  vector<string> subsecuencias2 = obtenerSubsecuencias(secuencia2);

  //Se toma el tiempo actual
  time_point<steady_clock> start = high_resolution_clock::now();

  //Comparamos las secuencias usando fuerza bruta
  string lcs = compararSubsecuencias(subsecuencias1, subsecuencias2);

  cout << "---Brute Force---" << endl;
  cout << "La subsecuencia mas larga comun de " << secuencia1.c_str() <<
    " y de " << secuencia2.c_str() << " es " << lcs.c_str() << endl;

  //Se toma el tiempo final
  time_point<steady_clock> end = high_resolution_clock::now();

  //Se saca el delta tiempo interno
  cout << "Terminado en: " << duration_cast<nanoseconds>(end - start).count() / 1e+9 <<
    " segundos." << endl;
  return 0;
}
