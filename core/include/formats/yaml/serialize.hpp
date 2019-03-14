#pragma once

#include <iosfwd>

#include <formats/yaml/value.hpp>

namespace formats {
namespace yaml {

formats::yaml::Value FromString(const std::string& doc);
formats::yaml::Value FromStream(std::istream& is);
formats::yaml::Value FromFile(const std::string& path);

void Serialize(const formats::yaml::Value& doc, std::ostream& os);
std::string ToString(const formats::yaml::Value& doc);

}  // namespace yaml
}  // namespace formats
