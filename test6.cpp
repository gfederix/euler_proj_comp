#include<limits>
#include<iterator>
#include<iostream>
#include<memory>
#include<cmath>
using namespace std;

class F{
  long num;
  int pos;
  F *p = nullptr;
  int const base = 10;
  // unique_ptr<F> p;
  // unique_ptr<F>p = make_unique<F>(nullptr);
  // unique_ptr<F>p = nullptr;
  // unique_ptr<F> xx = make_unique<F>(F(0));
public:
  explicit F(long x, int pos=0): num{x}, pos{pos}{
  };
  // F(const F&) = delete;
  // F& operator=(const F&) = delete;
  ~F() = default;
  F& operator++(int) {
    num ++;
    if (num == base){
      num = 0;
      if (p == nullptr) {
        p = new F(1, pos + 1);
      } else{
        (*p)++;
      }
    }
    return *this;
  }
  long get_value() const {
    long rez{num * static_cast<long>(powl(base, pos))};
    if (p!=nullptr) {
      rez += p->get_value();
    }
    return rez;
  }
  bool operator==(F other) const { return get_value() == other.get_value();};
};

class FIter{
public:
  // class iterator: public std::iterator <
  // std::forward_iterator_tag,   // iterator_category
  // F,                      // value_type
  // long,                      // difference_type
  // F*,               // pointer
  // F&                       // reference
  // >
    // std::forward_iterator_tag,   // iterator_category
    // long,                      // value_type
    // long,                      // difference_type
    // const long*,               // pointer
    // long                       // reference
    // >
  class iterator: public  std::iterator<std::forward_iterator_tag, F>
  {
    F num;
  public:
    explicit iterator(long x) : num{x} {}
    iterator& operator++(){
      num++;
      return *this;}
    reference operator*()  {return num;}
    bool operator==(iterator other) const { return num == other.num;}
    bool operator!=(iterator other) const { return !(*this == other);}
    // reference operator*() const {return num;}
  };
  iterator begin() {return iterator(0);}
  iterator end() {return iterator(numeric_limits<long>::max());
  };
};

int main() {
  auto f = FIter();
  for (auto &x: f ) {
    cout << x.get_value() << endl;
  };
  return 0;
}
