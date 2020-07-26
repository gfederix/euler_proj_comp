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
  int num;
  int pos;
  unique_ptr<F>p;
  static constexpr int base = 10;
  // static auto constexpr fact_array = make_array<base>(factorial);
  // static auto constexpr fact_array = make_array_helper(factorial, make_index_sequence<10>{});

  // static constexpr array<int, 10> fact_table = fact_table();
public:
  explicit F(int num, int pos = 0): num{num}, pos{pos}{}
  F& operator++(int) {
    num ++;
    if (num == base) {
      num = 0;
      if (!p) {
        p = make_unique<F>(1, pos + 1);
      } else {
        (*p)++;
      }
    }
    return *this;
  }
  long get_value() const {
    long rez{num * static_cast<long>(powl(base, pos))};
    if (p) {
      rez += p->get_value();
    }
    return rez;
  }
  long get_fact_sum() const {
    long rez = fact_array[num];
    // long rez = 0;
    // cout << fact_array.size() << "\n";
    if (p) {
      rez += p->get_fact_sum();
    }
    return rez;
  }
};

class FIter{
public:
  class iterator: public  std::iterator<std::forward_iterator_tag, F>
  {
    F f;
  public:
    explicit iterator(int x) : f{x, 0} {}
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
  auto f = FIter();
  for (auto &x: f ) {
    cout << x.get_value() << "\t" << x.get_fact_sum() << endl;
  };
  return 0;
}
#endif
