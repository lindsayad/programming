#include <iostream>

int main()
{
  for (int i = 0; i <= 5; i++)
    std::cout << i << std::endl;

  for (int i = 0; i <= 5; ++i)
    std::cout << i << std::endl;
}
