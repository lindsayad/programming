#include <iostream>
#include <map>
#include <type_traits>
#include <utility>

template <typename T> class A {
public:
  A() : _data() { std::cout << "Default constructor is being called\n"; }

  A(const T &in) : _data(in) {
    std::cout << "Single argument conversion constructor is being called\n";
  }

  A(const A<T> &a) : _data(a._data) {
    std::cout << "Copy constructor being called\n";
  }

  A(const A<T> &&a) : _data(a._data) {
    std::cout << "Move constructor being called\n";
  }

  template <typename U,
            typename std::enable_if<!std::is_same<T, U>::value, int>::type = 0>
  A(A<U> &a) : _data(&a._data) {
    std::cout << "Single A conversion constructor being called\n";
  }

  A<T> &operator=(const A<T> &a) {
    _data = a._data;
    std::cout << "Copy assignment operator being called\n";
    return *this;
  }

  T _data;
};

class MyInt {
public:
  MyInt(int x) : _x(x) { std::cout << "Calling int conversion constructor\n"; }

  MyInt(const MyInt &my_int) : _x(my_int._x) {
    std::cout << "Calling copy constructor\n";
  }

  MyInt &operator=(const MyInt &my_int) {
    std::cout << "Calling copy assignment operator\n";
    _x = my_int._x;
    return *this;
  }

private:
  int _x;
};

class MyDouble {
public:
  operator MyInt() {
    std::cout << "Calling operator MyInt conversion\n";
    return MyInt(_x);
  }

  MyDouble(double x) : _x(x) {
    std::cout << "Calling double conversion constructor\n";
  }

private:
  double _x;
};

int main() {
  std::map<unsigned, A<double>> m;
  m[0] = A<double>{2};
  m[1] = {2};

  A<double> a;
  A<double *> ref(a);
  A<double> copya(a);
  A<double> movea(std::move(copya));

  std::cout << a._data << std::endl;
  *ref._data = 5;
  std::cout << a._data << std::endl;
  std::cout << std::is_same<decltype(a), decltype(ref)>::value << std::endl;

  int d = 0;
  int &b = d;
  int c = 1;
  b = c;
  const int &e = d;
  int f = e;

  A<double> a2;
  ref = a2;
  std::cout << "a data before is " << a._data << std::endl;
  std::cout << "a2 data before is " << a2._data << std::endl;
  *ref._data = 10;
  std::cout << "a data after is " << a._data << std::endl;
  std::cout << "a2 data after is " << a2._data << std::endl;

  MyDouble my_double(5);
  MyInt my_int(my_double);
}
