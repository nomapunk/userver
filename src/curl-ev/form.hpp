/**
        curl-ev: wrapper for integrating libcurl with libev applications
        Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
        See COPYING for license information.

        C++ wrapper for constructing libcurl forms
*/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "config.hpp"
#include "initialization.hpp"
#include "native.hpp"

namespace curl {

class CURLASIO_API form : public std::enable_shared_from_this<form> {
 public:
  form();
  form(const form&) = delete;
  form(form&&) = delete;
  ~form();

  inline native::curl_httppost* native_handle() { return post_; };

  void add_content(const std::string& key, const std::string& content);
  void add_content(const std::string& key, const std::string& content,
                   std::error_code& ec);
  void add_content(const std::string& key, const std::string& content,
                   const std::string& content_type);
  void add_content(const std::string& key, const std::string& content,
                   const std::string& content_type, std::error_code& ec);
  void add_file(const std::string& key, const std::string& file_path);
  void add_file(const std::string& key, const std::string& file_path,
                std::error_code& ec);
  void add_file(const std::string& key, const std::string& file_path,
                const std::string& content_type);
  void add_file(const std::string& key, const std::string& file_path,
                const std::string& content_type, std::error_code& ec);
  void add_file_using_name(const std::string& key, const std::string& file_path,
                           const std::string& file_name);
  void add_file_using_name(const std::string& key, const std::string& file_path,
                           const std::string& file_name, std::error_code& ec);
  void add_file_using_name(const std::string& key, const std::string& file_path,
                           const std::string& file_name,
                           const std::string& content_type);
  void add_file_using_name(const std::string& key, const std::string& file_path,
                           const std::string& file_name,
                           const std::string& content_type,
                           std::error_code& ec);
  void add_file_content(const std::string& key, const std::string& file_path);
  void add_file_content(const std::string& key, const std::string& file_path,
                        std::error_code& ec);
  void add_file_content(const std::string& key, const std::string& file_path,
                        const std::string& content_type);
  void add_file_content(const std::string& key, const std::string& file_path,
                        const std::string& content_type, std::error_code& ec);

  void add_buffer(const std::string& key, const std::string& file_name,
                  const std::shared_ptr<std::string>& buffer);
  void add_buffer(const std::string& key, const std::string& file_name,
                  const std::shared_ptr<std::string>& buffer,
                  std::error_code& ec);

 private:
  void add_buffer(const std::string& key, const std::string& file_name,
                  const char* buffer, size_t buffer_len, std::error_code& ec);

 private:
  initialization::ptr initref_;
  native::curl_httppost* post_;
  native::curl_httppost* last_;
  std::vector<std::shared_ptr<std::string>> buffers_;
};

}  // namespace curl
