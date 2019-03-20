#pragma once

#include <formats/parse/to.hpp>

#include <utils/meta.hpp>

#include <boost/optional.hpp>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace formats::parse {

namespace impl {

template <typename ArrayType, typename T, class Value>
ArrayType ParseArray(const Value& value) {
  value.CheckArrayOrNull();

  ArrayType response;
  auto inserter = std::inserter(response, response.end());
  for (const auto& subitem : value) {
    *inserter = subitem.template As<T>();
    inserter++;
  }
  return response;
}

template <typename ObjectType, typename T, class Value>
ObjectType ParseObject(const Value& value) {
  value.CheckObjectOrNull();

  ObjectType result;

  for (auto it = value.begin(); it != value.end(); ++it)
    result.emplace(it.GetName(), it->template As<T>());

  return result;
}

}  // namespace impl

template <class Value, typename T>
std::unordered_set<T> Parse(const Value& value, To<std::unordered_set<T>>) {
  return impl::ParseArray<std::unordered_set<T>, T>(value);
}

template <class Value, typename T>
std::set<T> Parse(const Value& value, To<std::set<T>>) {
  return impl::ParseArray<std::set<T>, T>(value);
}

template <class Value, typename T>
std::enable_if_t<meta::is_vector<T>::value, T> Parse(const Value& value,
                                                     To<T>) {
  return impl::ParseArray<T, typename T::value_type>(value);
}

template <class Value, typename T>
std::unordered_map<std::string, T> Parse(
    const Value& value, To<std::unordered_map<std::string, T>>) {
  return impl::ParseObject<std::unordered_map<std::string, T>, T>(value);
}

template <class Value, typename T>
std::map<std::string, T> Parse(const Value& value,
                               To<std::map<std::string, T>>) {
  return impl::ParseObject<std::map<std::string, T>, T>(value);
}

template <class Value, typename T>
boost::optional<T> Parse(const Value& value, To<boost::optional<T>>) {
  if (value.IsMissing()) {
    return boost::none;
  }

  return value.template As<T>();
}

}  // namespace formats::parse
