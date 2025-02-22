/*
 *
 * Copyright 2016 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPCPP_IMPL_CODEGEN_CORE_CODEGEN_H
#define GRPCPP_IMPL_CODEGEN_CORE_CODEGEN_H

// IWYU pragma: private

// This file should be compiled as part of grpcpp.

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/impl/codegen/grpc_types.h>
#include <grpcpp/impl/codegen/core_codegen_interface.h>

namespace grpc {

/// Implementation of the core codegen interface.
class CoreCodegen final : public CoreCodegenInterface {
 private:
  grpc_call_error grpc_call_start_batch(grpc_call* call, const grpc_op* ops,
                                        size_t nops, void* tag,
                                        void* reserved) override;
  grpc_call_error grpc_call_cancel_with_status(grpc_call* call,
                                               grpc_status_code status,
                                               const char* description,
                                               void* reserved) override;
  int grpc_call_failed_before_recv_message(const grpc_call* c) override;
  void grpc_call_ref(grpc_call* call) override;
  void grpc_call_unref(grpc_call* call) override;
  void* grpc_call_arena_alloc(grpc_call* call, size_t length) override;
  const char* grpc_call_error_to_string(grpc_call_error error) override;

  grpc_byte_buffer* grpc_byte_buffer_copy(grpc_byte_buffer* bb) override;
  void grpc_byte_buffer_destroy(grpc_byte_buffer* bb) override;
  size_t grpc_byte_buffer_length(grpc_byte_buffer* bb) override;

  int grpc_byte_buffer_reader_init(grpc_byte_buffer_reader* reader,
                                   grpc_byte_buffer* buffer) override;
  void grpc_byte_buffer_reader_destroy(
      grpc_byte_buffer_reader* reader) override;
  int grpc_byte_buffer_reader_next(grpc_byte_buffer_reader* reader,
                                   grpc_slice* slice) override;
  int grpc_byte_buffer_reader_peek(grpc_byte_buffer_reader* reader,
                                   grpc_slice** slice) override;

  grpc_byte_buffer* grpc_raw_byte_buffer_create(grpc_slice* slice,
                                                size_t nslices) override;
  grpc_slice grpc_slice_new_with_user_data(void* p, size_t len,
                                           void (*destroy)(void*),
                                           void* user_data) override;
  grpc_slice grpc_slice_new_with_len(void* p, size_t len,
                                     void (*destroy)(void*, size_t)) override;
  grpc_slice grpc_empty_slice() override;
  grpc_slice grpc_slice_malloc(size_t length) override;
  void grpc_slice_unref(grpc_slice slice) override;
  grpc_slice grpc_slice_ref(grpc_slice slice) override;
  grpc_slice grpc_slice_split_tail(grpc_slice* s, size_t split) override;
  grpc_slice grpc_slice_split_head(grpc_slice* s, size_t split) override;
  grpc_slice grpc_slice_sub(grpc_slice s, size_t begin, size_t end) override;
  void grpc_slice_buffer_add(grpc_slice_buffer* sb, grpc_slice slice) override;
  void grpc_slice_buffer_pop(grpc_slice_buffer* sb) override;
  void grpc_slice_buffer_add_indexed(grpc_slice_buffer* sb,
                                     grpc_slice slice) override;
  grpc_slice grpc_slice_from_static_buffer(const void* buffer,
                                           size_t length) override;
  grpc_slice grpc_slice_from_copied_buffer(const void* buffer,
                                           size_t length) override;
  void grpc_metadata_array_init(grpc_metadata_array* array) override;
  void grpc_metadata_array_destroy(grpc_metadata_array* array) override;

  gpr_timespec gpr_inf_future(gpr_clock_type type) override;
  gpr_timespec gpr_time_0(gpr_clock_type type) override;

  const Status& ok() override;
  const Status& cancelled() override;

  void assert_fail(const char* failed_assertion, const char* file,
                   int line) override;
};

}  // namespace grpc

#endif  // GRPCPP_IMPL_CODEGEN_CORE_CODEGEN_H
