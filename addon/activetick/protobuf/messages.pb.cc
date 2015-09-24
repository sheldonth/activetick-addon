// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messages.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "messages.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace nodeactivetick {

namespace {

const ::google::protobuf::Descriptor* ATLoginResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ATLoginResponse_reflection_ = NULL;
const ::google::protobuf::Descriptor* ATServerTime_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ATServerTime_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_messages_2eproto() {
  protobuf_AddDesc_messages_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "messages.proto");
  GOOGLE_CHECK(file != NULL);
  ATLoginResponse_descriptor_ = file->message_type(0);
  static const int ATLoginResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATLoginResponse, loginresponsetype_),
  };
  ATLoginResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ATLoginResponse_descriptor_,
      ATLoginResponse::default_instance_,
      ATLoginResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATLoginResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATLoginResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ATLoginResponse));
  ATServerTime_descriptor_ = file->message_type(1);
  static const int ATServerTime_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATServerTime, year_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATServerTime, month_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATServerTime, dayofweek_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATServerTime, day_),
  };
  ATServerTime_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ATServerTime_descriptor_,
      ATServerTime::default_instance_,
      ATServerTime_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATServerTime, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ATServerTime, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ATServerTime));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_messages_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ATLoginResponse_descriptor_, &ATLoginResponse::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ATServerTime_descriptor_, &ATServerTime::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_messages_2eproto() {
  delete ATLoginResponse::default_instance_;
  delete ATLoginResponse_reflection_;
  delete ATServerTime::default_instance_;
  delete ATServerTime_reflection_;
}

void protobuf_AddDesc_messages_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016messages.proto\022\016nodeactivetick\",\n\017ATLo"
    "ginResponse\022\031\n\021loginResponseType\030\001 \002(\005\"K"
    "\n\014ATServerTime\022\014\n\004year\030\001 \002(\005\022\r\n\005month\030\002 "
    "\002(\005\022\021\n\tdayOfWeek\030\003 \002(\005\022\013\n\003day\030\004 \002(\005", 155);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "messages.proto", &protobuf_RegisterTypes);
  ATLoginResponse::default_instance_ = new ATLoginResponse();
  ATServerTime::default_instance_ = new ATServerTime();
  ATLoginResponse::default_instance_->InitAsDefaultInstance();
  ATServerTime::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_messages_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_messages_2eproto {
  StaticDescriptorInitializer_messages_2eproto() {
    protobuf_AddDesc_messages_2eproto();
  }
} static_descriptor_initializer_messages_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ATLoginResponse::kLoginResponseTypeFieldNumber;
#endif  // !_MSC_VER

ATLoginResponse::ATLoginResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:nodeactivetick.ATLoginResponse)
}

void ATLoginResponse::InitAsDefaultInstance() {
}

ATLoginResponse::ATLoginResponse(const ATLoginResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:nodeactivetick.ATLoginResponse)
}

void ATLoginResponse::SharedCtor() {
  _cached_size_ = 0;
  loginresponsetype_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ATLoginResponse::~ATLoginResponse() {
  // @@protoc_insertion_point(destructor:nodeactivetick.ATLoginResponse)
  SharedDtor();
}

void ATLoginResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ATLoginResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ATLoginResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ATLoginResponse_descriptor_;
}

const ATLoginResponse& ATLoginResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_messages_2eproto();
  return *default_instance_;
}

ATLoginResponse* ATLoginResponse::default_instance_ = NULL;

ATLoginResponse* ATLoginResponse::New() const {
  return new ATLoginResponse;
}

void ATLoginResponse::Clear() {
  loginresponsetype_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ATLoginResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:nodeactivetick.ATLoginResponse)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 loginResponseType = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &loginresponsetype_)));
          set_has_loginresponsetype();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:nodeactivetick.ATLoginResponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:nodeactivetick.ATLoginResponse)
  return false;
#undef DO_
}

void ATLoginResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:nodeactivetick.ATLoginResponse)
  // required int32 loginResponseType = 1;
  if (has_loginresponsetype()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->loginresponsetype(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:nodeactivetick.ATLoginResponse)
}

::google::protobuf::uint8* ATLoginResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:nodeactivetick.ATLoginResponse)
  // required int32 loginResponseType = 1;
  if (has_loginresponsetype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->loginresponsetype(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:nodeactivetick.ATLoginResponse)
  return target;
}

int ATLoginResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 loginResponseType = 1;
    if (has_loginresponsetype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->loginresponsetype());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ATLoginResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ATLoginResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ATLoginResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ATLoginResponse::MergeFrom(const ATLoginResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_loginresponsetype()) {
      set_loginresponsetype(from.loginresponsetype());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ATLoginResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ATLoginResponse::CopyFrom(const ATLoginResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ATLoginResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void ATLoginResponse::Swap(ATLoginResponse* other) {
  if (other != this) {
    std::swap(loginresponsetype_, other->loginresponsetype_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ATLoginResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ATLoginResponse_descriptor_;
  metadata.reflection = ATLoginResponse_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ATServerTime::kYearFieldNumber;
const int ATServerTime::kMonthFieldNumber;
const int ATServerTime::kDayOfWeekFieldNumber;
const int ATServerTime::kDayFieldNumber;
#endif  // !_MSC_VER

ATServerTime::ATServerTime()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:nodeactivetick.ATServerTime)
}

void ATServerTime::InitAsDefaultInstance() {
}

ATServerTime::ATServerTime(const ATServerTime& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:nodeactivetick.ATServerTime)
}

void ATServerTime::SharedCtor() {
  _cached_size_ = 0;
  year_ = 0;
  month_ = 0;
  dayofweek_ = 0;
  day_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ATServerTime::~ATServerTime() {
  // @@protoc_insertion_point(destructor:nodeactivetick.ATServerTime)
  SharedDtor();
}

void ATServerTime::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ATServerTime::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ATServerTime::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ATServerTime_descriptor_;
}

const ATServerTime& ATServerTime::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_messages_2eproto();
  return *default_instance_;
}

ATServerTime* ATServerTime::default_instance_ = NULL;

ATServerTime* ATServerTime::New() const {
  return new ATServerTime;
}

void ATServerTime::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<ATServerTime*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(year_, day_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ATServerTime::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:nodeactivetick.ATServerTime)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 year = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &year_)));
          set_has_year();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_month;
        break;
      }

      // required int32 month = 2;
      case 2: {
        if (tag == 16) {
         parse_month:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &month_)));
          set_has_month();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_dayOfWeek;
        break;
      }

      // required int32 dayOfWeek = 3;
      case 3: {
        if (tag == 24) {
         parse_dayOfWeek:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &dayofweek_)));
          set_has_dayofweek();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_day;
        break;
      }

      // required int32 day = 4;
      case 4: {
        if (tag == 32) {
         parse_day:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &day_)));
          set_has_day();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:nodeactivetick.ATServerTime)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:nodeactivetick.ATServerTime)
  return false;
#undef DO_
}

void ATServerTime::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:nodeactivetick.ATServerTime)
  // required int32 year = 1;
  if (has_year()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->year(), output);
  }

  // required int32 month = 2;
  if (has_month()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->month(), output);
  }

  // required int32 dayOfWeek = 3;
  if (has_dayofweek()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->dayofweek(), output);
  }

  // required int32 day = 4;
  if (has_day()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->day(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:nodeactivetick.ATServerTime)
}

::google::protobuf::uint8* ATServerTime::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:nodeactivetick.ATServerTime)
  // required int32 year = 1;
  if (has_year()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->year(), target);
  }

  // required int32 month = 2;
  if (has_month()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->month(), target);
  }

  // required int32 dayOfWeek = 3;
  if (has_dayofweek()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->dayofweek(), target);
  }

  // required int32 day = 4;
  if (has_day()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->day(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:nodeactivetick.ATServerTime)
  return target;
}

int ATServerTime::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 year = 1;
    if (has_year()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->year());
    }

    // required int32 month = 2;
    if (has_month()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->month());
    }

    // required int32 dayOfWeek = 3;
    if (has_dayofweek()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->dayofweek());
    }

    // required int32 day = 4;
    if (has_day()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->day());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ATServerTime::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ATServerTime* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ATServerTime*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ATServerTime::MergeFrom(const ATServerTime& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_year()) {
      set_year(from.year());
    }
    if (from.has_month()) {
      set_month(from.month());
    }
    if (from.has_dayofweek()) {
      set_dayofweek(from.dayofweek());
    }
    if (from.has_day()) {
      set_day(from.day());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ATServerTime::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ATServerTime::CopyFrom(const ATServerTime& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ATServerTime::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void ATServerTime::Swap(ATServerTime* other) {
  if (other != this) {
    std::swap(year_, other->year_);
    std::swap(month_, other->month_);
    std::swap(dayofweek_, other->dayofweek_);
    std::swap(day_, other->day_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ATServerTime::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ATServerTime_descriptor_;
  metadata.reflection = ATServerTime_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace nodeactivetick

// @@protoc_insertion_point(global_scope)
