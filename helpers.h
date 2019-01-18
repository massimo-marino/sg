//
// helpers.h
//
// Created by massimo on 10/1/18.
//
#pragma once

#include <iostream>
//#include <type_traits>
#include <tuple>
////////////////////////////////////////////////////////////////////////////////
// Helper functions for printing tuples based upon example from
// The C++ Programming Language By Bjarne Stroustrup, page 817
template<size_t N>
struct print_tuple
{
  // print non-empty tuple
  template<typename... T>
  static typename std::enable_if<(N<sizeof...(T))>::type
  print(std::ostream& os, const std::tuple<T...>& t)
  {
    //std::string_view quote = (std::is_convertible<decltype(std::get<N>(t)), std::string>::value) ? "\"" : "";
    std::string quote = (std::is_convertible<decltype(std::get<N>(t)), std::string>::value) ? "\"" : "";

    if ( sizeof(std::get<N>(t)) == sizeof(char) )
    {
      os << ", " << quote << static_cast<int16_t>(std::get<N>(t)) << quote;
    }
    else
    {
      os << ", " << quote << std::get<N>(t) << quote;
    }
    print_tuple<N+1>::print(os,t);
  }

  // empty tuple
  template<typename... T>
  static typename std::enable_if<!(N<sizeof...(T))>::type
  print(std::ostream&, const std::tuple<T...>&)
  {}
};

// non-empty tuple
template<typename T0, typename ...T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T0, T...>& t)
{
  //std::string_view quote = (std::is_convertible<T0, std::string>::value) ? "\"" : "";
  std::string quote = (std::is_convertible<T0, std::string>::value) ? "\"" : "";

  if ( sizeof(std::get<0>(t)) == sizeof(char) )
  {
    os << '{' << quote << static_cast<int16_t>(std::get<0>(t)) << quote;
  }
  else
  {
    os << '{' << quote << std::get<0>(t) << quote;
  }
  print_tuple<1>::print(os,t);
  return os << '}';
}

std::ostream& operator<<(std::ostream& os, const std::tuple<>&);
////////////////////////////////////////////////////////////////////////////////
//
// helper function to print a tuple of any size from:
// https://en.cppreference.com/w/cpp/utility/tuple/tuple

//template<class Tuple, std::size_t N>
//struct TuplePrinter {
//  static void print(const Tuple& t, std::ostream& os = std::cout)
//  {
//    TuplePrinter<Tuple, N - 1>::print(t);
//    if ( sizeof(std::get<N - 1>(t)) == sizeof(char) )
//    {
//      os << ", " << static_cast<int16_t>(std::get<N - 1>(t));
//    }
//    else
//    {
//      os << ", " << std::get<N - 1>(t);
//    }
//  }
//};
//
//template<class Tuple>
//struct TuplePrinter<Tuple, 1>
//{
//  static void print(const Tuple& t, std::ostream& os = std::cout)
//  {
//    if ( sizeof(std::get<0>(t)) == sizeof(char) )
//    {
//      os << static_cast<int16_t>(std::get<0>(t));
//    }
//    else
//    {
//      os << std::get<0>(t);
//    }
//  }
//};
//
//template<class... Args>
//void print(const std::tuple<Args...>& t, std::ostream& os = std::cout)
//{
//  os << "(";
//  TuplePrinter<decltype(t), sizeof...(Args)>::print(t, os);
//  os << ")\n";
//}
// end helper function

////////////////////////////////////////////////////////////////////////////////
/// string tokenizer
/// example:
//{
//  using container = std::vector<std::string>;
//  const std::string s {"21-256-5-3-500x500"};
//  container tokens {};

//  tokens = utilities::strTokenize<container>(s, "-x");
//  for(auto&& t : tokens)
//  {
//    std::cout << "'" << t << "'\n";
//  }
//  ASSERT_EQ(tokens[0], "21");
//  ASSERT_EQ(tokens[1], "256");
//  ASSERT_EQ(tokens[2], "5");
//  ASSERT_EQ(tokens[3], "3");
//  ASSERT_EQ(tokens[4], "500");
//  ASSERT_EQ(tokens[5], "500");
//}
template <class Container>
Container
strTokenize(const std::string& str,
            const std::string& delims = " ") noexcept;

template <class Container>
Container
strTokenize(const std::string& str,
            const std::string& delims) noexcept
{
  Container container {};

  if ( str.empty() )
  {
    return container;
  }
  if ( delims.empty() )
  {
    container.push_back(str);
    return container;
  }
  std::size_t previous {0};
  std::size_t current {str.find_first_of(delims)};
  while ( std::string::npos != current )
  {
    container.push_back(str.substr(previous, current - previous));
    previous = current + 1;
    current = str.find_first_of(delims, previous);
  }
  container.push_back(str.substr(previous, current - previous));
  return container;
}
