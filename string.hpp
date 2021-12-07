#ifndef FILE_STRING_HPP
#define FILE_STRING_HPP
#include <string_view>

// constexpr string

auto copy(auto* dest, const auto* src, const std::size_t len) {
   for (std::size_t i = 0; i < len; ++i) {
      dest[i] = src[i];
   }
   return dest;
}

class String {
private:
   std::size_t len{}, cap{};
   char* buffer{};
public:
   constexpr String() noexcept = default;

   constexpr String(const String& s)
      : len(s.len), cap(s.cap), buffer(new char[cap]) {
      copy(buffer, s.buffer, s.len + 1);
   }

   constexpr String(String&& s) noexcept
      : len(s.len), cap(s.cap), buffer(s.buffer) {
      s = String();
   }

   constexpr String(std::string_view s)
      : len(s.size()), cap(s.size() + 1), buffer(new char[cap]) {
      copy(buffer, s.data(), len);
      buffer[len] = '\0';
   }

   constexpr ~String() noexcept {
      delete[] buffer;
      len = cap = 0;
      buffer = nullptr;
   }

   constexpr String& operator=(const String& s) {
      reserve(s.len + 1, false);
      len = s.len;
      copy(buffer, s.buffer, len + 1);
      return *this;
   }
   constexpr String& operator=(String&& s) noexcept {
      delete[] buffer;
      len = s.len;
      cap = s.cap;
      buffer = s.buffer;
      s.buffer = nullptr;
      s.len = s.cap = 0;
      return *this;
   }
   constexpr String& operator=(std::string_view s) {
      len = s.size();
      reserve(len + 1, false);
      copy(buffer, s.data(), s.size());
      buffer[len] = '\0';
      return *this;
   }

   constexpr String& operator+=(const String& s) {
      reserve(len + s.len + 1, true);
   }

   constexpr void reserve(std::size_t num, bool do_copy = true) {
      if (cap < num) {
         cap = num;
         char* new_buffer = new char[cap];
         if (do_copy)
            copy(new_buffer, buffer, len);
         delete[] buffer;
         buffer = new_buffer;
      }
   }

};

#endif /* FILE_STRING_HPP */
