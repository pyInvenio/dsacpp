/**
    if n % 3 == 0 and n % 5 == 0, return "FizzBuzz"
    else if n % 3 == 0, return "Fizz"
    else if n % 5 == 0, return "Buzz"
    else return n

   we would like to implement a template struct that takes an integer N and
   returns the string representation of the number N according to the rules
   above.
*/

#include <iostream>

using namespace std;

template <char... Chars> struct String {
  static constexpr const char value[] = {Chars..., '\0'};
};

template <char... Chars> constexpr const char String<Chars...>::value[];

template <int N, int mod> struct Modulo {
  static constexpr int value = N % mod;
};

template <int N> struct Fizz {
  using type = String<>;
};

template <> struct Fizz<0> {
  using type = String<'F', 'i', 'z', 'z'>;
};

template <int N> struct Buzz {
  using type = String<>;
};

template <> struct Buzz<0> {
  using type = String<'B', 'u', 'z', 'z'>;
};

template <typename T1, typename T2> struct Concat {
  using type = String<>;
};

template <char... Chars1, char... Chars2>
struct Concat<String<Chars1...>, String<Chars2...>> {
  using type = String<Chars1..., Chars2...>;
};

template <int N> struct Digit {
  static constexpr char value = N + '0';
};

template <int N> struct NumberToString {
  using type = typename Concat<typename NumberToString<N / 10>::type,
                               String<Digit<N % 10>::value>>::type;
};

template <> struct NumberToString<0> {
  using type = String<>;
};

template <bool Condition, typename TrueType, typename FalseType>
struct Conditional {
  using type = FalseType;
};

template <typename TrueType, typename FalseType>
struct Conditional<true, TrueType, FalseType> {
  using type = TrueType;
};

struct SpaceType {
  using type = String<' '>;
};

template <int N> struct FizzBuzz {
  using Fizz = typename Fizz<Modulo<N, 3>::value>::type;
  using Buzz = typename Buzz<Modulo<N, 5>::value>::type;
  using FizzBuzzStr = typename Concat<Fizz, Buzz>::type;
  using Result = typename Conditional < (sizeof(FizzBuzzStr::value) > 1),
        FizzBuzzStr, typename NumberToString<N>::type > ::type;

  using type =
      typename Concat<typename FizzBuzz<N - 1>::type,
                      typename Concat<Result, String<' '>>::type>::type;
};

template <> struct FizzBuzz<0> {
  using Result = String<>;
  using type = String<>;
};

int main() { std::cout << FizzBuzz<100>::type::value << std::endl; }