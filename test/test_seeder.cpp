
#include <iostream>

#include <biomesh_seeder.hpp>

int main()
{
  biomesh::seeder s(2);

  /* Range-based for loop test. */
  try
  {
    for(const auto& e : s)
    {
      e.print();
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << "Range based compatibility failed." << '\n';
  }

  /* STL algorithm compatibility test. */
  try
  {
    std::for_each(s.begin(), s.end(), [](auto& e){ e.print(); });
  }
  catch(const std::exception& e)
  {
    std::cerr << "STL algortihm compatibility failed." << '\n';
  }

  /* C++98 style loop compatibility test. */
  try
  {
    for(biomesh::seeder::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
      auto v = *itr;
      v.print();
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << "C++98 iterator loop compatibility failed." << '\n';
  }

  return EXIT_SUCCESS;
}