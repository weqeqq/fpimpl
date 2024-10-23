#ifndef FPIMPL
#define FPIMPL

#include <cstdint>
#include <utility>

template <typename Type,
          std::size_t Size      = 0,
          std::size_t Alignment = 0>
class FPImpl {
 public:
  template <typename... Args>
  FPImpl(Args &&...args) {
    static_assert(sizeof(Type) <= Size);
    static_assert(alignof(Type) <= Alignment);
    new (GetStorage()) Type(std::forward<Args>(args)...);
  }
  FPImpl(const FPImpl<Type, Size, Alignment> &rhs) {
    new (GetStorage()) Type(*rhs);
  }

  FPImpl(FPImpl<Type, Size, Alignment> &&rhs) {
    new (GetStorage()) Type(std::move(*rhs));
  }

  ~FPImpl() { GetStorage()->~Type(); }

  FPImpl<Type, Size, Alignment> &
  operator=(const FPImpl<Type, Size, Alignment> &rhs) {
    if (this != &rhs) {
      *GetStorage() = *rhs;
    }
    return *this;
  }
  FPImpl<Type, Size, Alignment> &
  operator=(FPImpl<Type, Size, Alignment> &&rhs) {
    if (this != &rhs) {
      *GetStorage() = std::move(*rhs);
    }
    return *this;
  }
  Type       *operator->() { return GetStorage(); }
  const Type *operator->() const { return GetStorage(); }
  Type       &operator*() { return *GetStorage(); }
  const Type &operator*() const { return *GetStorage(); }

 private:
  alignas(Alignment) std::uint8_t storage[Size];
  Type       *GetStorage() { return reinterpret_cast<Type *>(&storage); }
  const Type *GetStorage() const { return reinterpret_cast<const Type *>(&storage); }
};

#define FPIMPL_DECLARE_IMPL(size, alignment)     \
  class Impl;                                    \
  static constexpr std::size_t  size, alignment; \
  FPImpl<Impl, Size, Alignment> impl_

#define FPIMPL_DECLARE_DEFAULT(class_name)   \
  class_name();                              \
  class_name(const class_name &);            \
  class_name(class_name &&);                 \
  ~class_name();                             \
  class_name &operator=(const class_name &); \
  class_name &operator=(class_name &&)

#define FPIMPL_DEFINE_DEFAULT(class_name)                          \
  class_name::class_name()                              = default; \
  class_name::class_name(const class_name &)            = default; \
  class_name::class_name(class_name &&)                 = default; \
  class_name::~class_name()                             = default; \
  class_name &class_name::operator=(const class_name &) = default; \
  class_name &class_name::operator=(class_name &&)      = default;

#endif
