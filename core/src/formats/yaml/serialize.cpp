#include <formats/yaml/serialize.hpp>

#include <array>
#include <fstream>
#include <memory>
#include <sstream>

#include <formats/yaml/exception.hpp>
#include <formats/yaml/value_detail.hpp>

#include <yaml-cpp/yaml.h>

namespace formats {
namespace yaml {

formats::yaml::Value FromString(const std::string& doc) {
  if (doc.empty()) {
    throw ParseException("JSON document is empty");
  }

  try {
    return YAML::Load(doc);
  } catch (const YAML::ParserException& e) {
    throw ParseException(e.what());
  }
}

formats::yaml::Value FromStream(std::istream& is) {
  if (!is) {
    throw BadStreamException(is);
  }

  try {
    return YAML::Load(is);
  } catch (const YAML::ParserException& e) {
    throw ParseException(e.what());
  }
}

formats::yaml::Value FromFile(const std::string& path) {
  std::ifstream is(path);
  return FromStream(is);
}

void Serialize(const formats::yaml::Value& doc, std::ostream& os) {
  os << doc.GetNative();
  if (!os) {
    throw BadStreamException(os);
  }
}

std::string ToString(const formats::yaml::Value& doc) {
  std::ostringstream os;
  Serialize(doc, os);
  return os.str();
}

}  // namespace yaml
}  // namespace formats
