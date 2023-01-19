#ifndef CGFX_MACROS_HPP
#define CGFX_MACROS_HPP

#define DELETE_COPY_AND_ASSIGN(TypeName)        \
  TypeName(const TypeName&) = delete;           \
  TypeName& operator=(const TypeName&) = delete;

#define DELETE_MOVE_AND_ASSIGN(TypeName)      \
  TypeName(TypeName&&) = delete;              \
  TypeName& operator=(TypeName&&) = delete;

#define DEFAULT_COPY_AND_ASSIGN(TypeName)        \
  TypeName(const TypeName&) = default;           \
  TypeName& operator=(const TypeName&) = default;

#define DEFAULT_MOVE_AND_ASSIGN(TypeName)            \
  TypeName(TypeName&&) noexcept = default;           \
  TypeName& operator=(TypeName&&) noexcept = default;

#define DEFAULT_CONSTRUCTOR_AND_DESTRUCTOR(TypeName) \
  TypeName() = default;                              \
  ~TypeName() = default;

#define INTERFACE(TypeName)                      \
  public:                                        \
  virtual ~TypeName() = default;                 \
  protected:                                     \
  TypeName() = default;                          \
  TypeName(const TypeName&) = default;           \
  TypeName(TypeName&&) = default;                \
  TypeName& operator=(const TypeName&) = default;\
  TypeName& operator=(TypeName&&) = default;     \
  private:                                       \

#endif //CGFX_MACROS_HPP
