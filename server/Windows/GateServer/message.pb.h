// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: message.proto
// Protobuf C++ Version: 5.28.3

#ifndef GOOGLE_PROTOBUF_INCLUDED_message_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_message_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5028003
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_message_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_message_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_message_2eproto;
namespace message {
class GetVarifyReq;
struct GetVarifyReqDefaultTypeInternal;
extern GetVarifyReqDefaultTypeInternal _GetVarifyReq_default_instance_;
class GetVarifyRsp;
struct GetVarifyRspDefaultTypeInternal;
extern GetVarifyRspDefaultTypeInternal _GetVarifyRsp_default_instance_;
}  // namespace message
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace message {

// ===================================================================


// -------------------------------------------------------------------

class GetVarifyRsp final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:message.GetVarifyRsp) */ {
 public:
  inline GetVarifyRsp() : GetVarifyRsp(nullptr) {}
  ~GetVarifyRsp() PROTOBUF_FINAL;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetVarifyRsp(
      ::google::protobuf::internal::ConstantInitialized);

  inline GetVarifyRsp(const GetVarifyRsp& from) : GetVarifyRsp(nullptr, from) {}
  inline GetVarifyRsp(GetVarifyRsp&& from) noexcept
      : GetVarifyRsp(nullptr, std::move(from)) {}
  inline GetVarifyRsp& operator=(const GetVarifyRsp& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVarifyRsp& operator=(GetVarifyRsp&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const GetVarifyRsp& default_instance() {
    return *internal_default_instance();
  }
  static inline const GetVarifyRsp* internal_default_instance() {
    return reinterpret_cast<const GetVarifyRsp*>(
        &_GetVarifyRsp_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(GetVarifyRsp& a, GetVarifyRsp& b) { a.Swap(&b); }
  inline void Swap(GetVarifyRsp* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(GetVarifyRsp* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetVarifyRsp* New(::google::protobuf::Arena* arena = nullptr) const PROTOBUF_FINAL {
    return ::google::protobuf::Message::DefaultConstruct<GetVarifyRsp>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const GetVarifyRsp& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const GetVarifyRsp& from) { GetVarifyRsp::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(GetVarifyRsp* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "message.GetVarifyRsp"; }

 protected:
  explicit GetVarifyRsp(::google::protobuf::Arena* arena);
  GetVarifyRsp(::google::protobuf::Arena* arena, const GetVarifyRsp& from);
  GetVarifyRsp(::google::protobuf::Arena* arena, GetVarifyRsp&& from) noexcept
      : GetVarifyRsp(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const PROTOBUF_FINAL;
  static const ::google::protobuf::Message::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kEmailFieldNumber = 2,
    kCodeFieldNumber = 3,
    kErrorFieldNumber = 1,
  };
  // string email = 2;
  void clear_email() ;
  const std::string& email() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_email(Arg_&& arg, Args_... args);
  std::string* mutable_email();
  PROTOBUF_NODISCARD std::string* release_email();
  void set_allocated_email(std::string* value);

  private:
  const std::string& _internal_email() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_email(
      const std::string& value);
  std::string* _internal_mutable_email();

  public:
  // string code = 3;
  void clear_code() ;
  const std::string& code() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_code(Arg_&& arg, Args_... args);
  std::string* mutable_code();
  PROTOBUF_NODISCARD std::string* release_code();
  void set_allocated_code(std::string* value);

  private:
  const std::string& _internal_code() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_code(
      const std::string& value);
  std::string* _internal_mutable_code();

  public:
  // int32 error = 1;
  void clear_error() ;
  ::int32_t error() const;
  void set_error(::int32_t value);

  private:
  ::int32_t _internal_error() const;
  void _internal_set_error(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:message.GetVarifyRsp)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      38, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_GetVarifyRsp_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const GetVarifyRsp& from_msg);
    ::google::protobuf::internal::ArenaStringPtr email_;
    ::google::protobuf::internal::ArenaStringPtr code_;
    ::int32_t error_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_message_2eproto;
};
// -------------------------------------------------------------------

class GetVarifyReq final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:message.GetVarifyReq) */ {
 public:
  inline GetVarifyReq() : GetVarifyReq(nullptr) {}
  ~GetVarifyReq() PROTOBUF_FINAL;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetVarifyReq(
      ::google::protobuf::internal::ConstantInitialized);

  inline GetVarifyReq(const GetVarifyReq& from) : GetVarifyReq(nullptr, from) {}
  inline GetVarifyReq(GetVarifyReq&& from) noexcept
      : GetVarifyReq(nullptr, std::move(from)) {}
  inline GetVarifyReq& operator=(const GetVarifyReq& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVarifyReq& operator=(GetVarifyReq&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const GetVarifyReq& default_instance() {
    return *internal_default_instance();
  }
  static inline const GetVarifyReq* internal_default_instance() {
    return reinterpret_cast<const GetVarifyReq*>(
        &_GetVarifyReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(GetVarifyReq& a, GetVarifyReq& b) { a.Swap(&b); }
  inline void Swap(GetVarifyReq* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(GetVarifyReq* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetVarifyReq* New(::google::protobuf::Arena* arena = nullptr) const PROTOBUF_FINAL {
    return ::google::protobuf::Message::DefaultConstruct<GetVarifyReq>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const GetVarifyReq& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const GetVarifyReq& from) { GetVarifyReq::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(GetVarifyReq* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "message.GetVarifyReq"; }

 protected:
  explicit GetVarifyReq(::google::protobuf::Arena* arena);
  GetVarifyReq(::google::protobuf::Arena* arena, const GetVarifyReq& from);
  GetVarifyReq(::google::protobuf::Arena* arena, GetVarifyReq&& from) noexcept
      : GetVarifyReq(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const PROTOBUF_FINAL;
  static const ::google::protobuf::Message::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kEmailFieldNumber = 1,
  };
  // string email = 1;
  void clear_email() ;
  const std::string& email() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_email(Arg_&& arg, Args_... args);
  std::string* mutable_email();
  PROTOBUF_NODISCARD std::string* release_email();
  void set_allocated_email(std::string* value);

  private:
  const std::string& _internal_email() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_email(
      const std::string& value);
  std::string* _internal_mutable_email();

  public:
  // @@protoc_insertion_point(class_scope:message.GetVarifyReq)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      34, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_GetVarifyReq_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const GetVarifyReq& from_msg);
    ::google::protobuf::internal::ArenaStringPtr email_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_message_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// GetVarifyReq

// string email = 1;
inline void GetVarifyReq::clear_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.ClearToEmpty();
}
inline const std::string& GetVarifyReq::email() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVarifyReq.email)
  return _internal_email();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void GetVarifyReq::set_email(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVarifyReq.email)
}
inline std::string* GetVarifyReq::mutable_email() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:message.GetVarifyReq.email)
  return _s;
}
inline const std::string& GetVarifyReq::_internal_email() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.email_.Get();
}
inline void GetVarifyReq::_internal_set_email(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(value, GetArena());
}
inline std::string* GetVarifyReq::_internal_mutable_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.email_.Mutable( GetArena());
}
inline std::string* GetVarifyReq::release_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVarifyReq.email)
  return _impl_.email_.Release();
}
inline void GetVarifyReq::set_allocated_email(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.email_.IsDefault()) {
          _impl_.email_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:message.GetVarifyReq.email)
}

// -------------------------------------------------------------------

// GetVarifyRsp

// int32 error = 1;
inline void GetVarifyRsp::clear_error() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.error_ = 0;
}
inline ::int32_t GetVarifyRsp::error() const {
  // @@protoc_insertion_point(field_get:message.GetVarifyRsp.error)
  return _internal_error();
}
inline void GetVarifyRsp::set_error(::int32_t value) {
  _internal_set_error(value);
  // @@protoc_insertion_point(field_set:message.GetVarifyRsp.error)
}
inline ::int32_t GetVarifyRsp::_internal_error() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.error_;
}
inline void GetVarifyRsp::_internal_set_error(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.error_ = value;
}

// string email = 2;
inline void GetVarifyRsp::clear_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.ClearToEmpty();
}
inline const std::string& GetVarifyRsp::email() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVarifyRsp.email)
  return _internal_email();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void GetVarifyRsp::set_email(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVarifyRsp.email)
}
inline std::string* GetVarifyRsp::mutable_email() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:message.GetVarifyRsp.email)
  return _s;
}
inline const std::string& GetVarifyRsp::_internal_email() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.email_.Get();
}
inline void GetVarifyRsp::_internal_set_email(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(value, GetArena());
}
inline std::string* GetVarifyRsp::_internal_mutable_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.email_.Mutable( GetArena());
}
inline std::string* GetVarifyRsp::release_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVarifyRsp.email)
  return _impl_.email_.Release();
}
inline void GetVarifyRsp::set_allocated_email(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.email_.IsDefault()) {
          _impl_.email_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:message.GetVarifyRsp.email)
}

// string code = 3;
inline void GetVarifyRsp::clear_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.ClearToEmpty();
}
inline const std::string& GetVarifyRsp::code() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVarifyRsp.code)
  return _internal_code();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void GetVarifyRsp::set_code(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVarifyRsp.code)
}
inline std::string* GetVarifyRsp::mutable_code() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_code();
  // @@protoc_insertion_point(field_mutable:message.GetVarifyRsp.code)
  return _s;
}
inline const std::string& GetVarifyRsp::_internal_code() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.code_.Get();
}
inline void GetVarifyRsp::_internal_set_code(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.Set(value, GetArena());
}
inline std::string* GetVarifyRsp::_internal_mutable_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.code_.Mutable( GetArena());
}
inline std::string* GetVarifyRsp::release_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVarifyRsp.code)
  return _impl_.code_.Release();
}
inline void GetVarifyRsp::set_allocated_code(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.code_.IsDefault()) {
          _impl_.code_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:message.GetVarifyRsp.code)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace message


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_message_2eproto_2epb_2eh
