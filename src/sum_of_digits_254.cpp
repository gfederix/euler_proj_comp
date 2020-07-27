#include<limits>
#include<iterator>
#include<iostream>
#include<memory>
#include<cmath>
using namespace std;

// template<int n>
// struct Factorial{
//   enum{value = n * Factorial<n - 1>::value};
// };

// template<>
// struct Factorial<0> {
//   enum {
//        value = 0
//   };
// };

constexpr int factorial(int n){
  return n ? (n * factorial(n - 1)) : 1;
}

template<class Function, std::size_t... Indices>
constexpr auto make_array_helper(Function f, std::index_sequence<Indices...>)
  -> std::array<typename std::result_of<Function(std::size_t)>::type, sizeof...(Indices)>{
  return {{ f(Indices)... }};
}

template<int N, class Function>
constexpr auto make_array(Function f)
-> std::array<typename std::result_of<Function(std::size_t)>::type, N>
{
    return make_array_helper(f, std::make_index_sequence<N>{});
}

// constexpr array<int, 10> fact_table(){
//   constexpr array<int, 10> rez = array<int, 10>();
//   for (auto i = 0; i < 10; i++){
//     rez[i] = factorial(i);
//   };
//   return rez;
// }
// auto constexpr fact_array = make_array<10>(factorial);
auto constexpr fact_array = make_array_helper(factorial, make_index_sequence<10>{});

class F{
  int digit;
  unique_ptr<F>p;
  static constexpr int base = 10;
  // static auto constexpr fact_array = make_array<base>(factorial);
  // static auto constexpr fact_array = make_array_helper(factorial, make_index_sequence<10>{});

  // static constexpr array<int, 10> fact_table = fact_table();
public:
  explicit F(int digit): digit{digit}{}
  F& operator++(int) {
    digit ++;
    if (digit == base) {
      digit = 0;
      if (p) {
        (*p)++;
      } else {
        p = make_unique<F>(1);
      }
    }
    return *this;
  }
  long get_value() const {
    long value{digit};
    if (p) {
      value += p->get_value() * base;
    }
    return value;
  }
  long get_fact_sum() const {
    long rez = fact_array[digit];
    if (p) {
      rez += p->get_fact_sum();
    }
    return rez;
  }
};

class FGenerator{
public:
  class iterator: public  std::iterator<std::forward_iterator_tag, F>
  {
    F f;
  public:
    explicit iterator(int x) : f{x} {}
    iterator& operator++(){
      f++;
      return *this;}
    reference operator*()  {return f;}
    bool operator==(iterator &other) const { return f.get_value() == other.f.get_value();}
    bool operator!=(iterator &other) const { return !(*this == other);}
  };
  iterator begin() {return iterator(0);}
  iterator end() {return iterator(numeric_limits<int>::max());
  };
};

#ifndef TEST

int main(){
  auto f = FGenerator();
  for (auto &x: f ) {
    cout << x.get_value() << "\t" << x.get_fact_sum() << endl;
  };
  return 0;
}
#endif
