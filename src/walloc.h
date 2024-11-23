// walloc.h: a small malloc implementation for use in WebAssembly targets
// Copyright (c) 2020 Igalia, S.L.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef _WALLOC_H
#define _WALLOC_H

#ifndef	__int8_t_defined
#define uint8_t unsigned char
#endif

typedef __SIZE_TYPE__ size_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#define NULL ((void *) 0)

#define STATIC_ASSERT_EQ(a, b) _Static_assert((a) == (b), "eq")

#ifndef NDEBUG
#define ASSERT(x) do { if (!(x)) __builtin_trap(); } while (0)
#else
#define ASSERT(x) do { } while (0)
#endif
#define ASSERT_EQ(a,b) ASSERT((a) == (b))

#define ASSERT_ALIGNED(x, y) ASSERT((x) == align((x), y))

#define CHUNK_SIZE 256
#define CHUNK_SIZE_LOG_2 8
#define CHUNK_MASK (CHUNK_SIZE - 1)
STATIC_ASSERT_EQ(CHUNK_SIZE, 1 << CHUNK_SIZE_LOG_2);

#define PAGE_SIZE 65536
#define PAGE_SIZE_LOG_2 16
#define PAGE_MASK (PAGE_SIZE - 1)
STATIC_ASSERT_EQ(PAGE_SIZE, 1 << PAGE_SIZE_LOG_2);

#define CHUNKS_PER_PAGE 256
STATIC_ASSERT_EQ(PAGE_SIZE, CHUNK_SIZE * CHUNKS_PER_PAGE);

#define GRANULE_SIZE 8
#define GRANULE_SIZE_LOG_2 3
#define LARGE_OBJECT_THRESHOLD 256
#define LARGE_OBJECT_GRANULE_THRESHOLD 32

STATIC_ASSERT_EQ(GRANULE_SIZE, 1 << GRANULE_SIZE_LOG_2);
STATIC_ASSERT_EQ(LARGE_OBJECT_THRESHOLD,
                 LARGE_OBJECT_GRANULE_THRESHOLD * GRANULE_SIZE);

struct chunk {
  char data[CHUNK_SIZE];
};

// There are small object pages for allocations of these sizes.
#define FOR_EACH_SMALL_OBJECT_GRANULES(M) \
  M(1) M(2) M(3) M(4) M(5) M(6) M(8) M(10) M(16) M(32)

enum chunk_kind {
#define DEFINE_SMALL_OBJECT_CHUNK_KIND(i) GRANULES_##i,
  FOR_EACH_SMALL_OBJECT_GRANULES(DEFINE_SMALL_OBJECT_CHUNK_KIND)
#undef DEFINE_SMALL_OBJECT_CHUNK_KIND

  SMALL_OBJECT_CHUNK_KINDS,
  FREE_LARGE_OBJECT = 254,
  LARGE_OBJECT = 255
};

static const uint8_t small_object_granule_sizes[] =
{
#define SMALL_OBJECT_GRANULE_SIZE(i) i,
  FOR_EACH_SMALL_OBJECT_GRANULES(SMALL_OBJECT_GRANULE_SIZE)
#undef SMALL_OBJECT_GRANULE_SIZE
};


// Given a pointer P returned by malloc(), we get a header pointer via
// P&~PAGE_MASK, and a chunk index via (P&PAGE_MASK)/CHUNKS_PER_PAGE.  If
// chunk_kinds[chunk_idx] is [FREE_]LARGE_OBJECT, then the pointer is a large
// object, otherwise the kind indicates the size in granules of the objects in
// the chunk.
struct page_header {
  uint8_t chunk_kinds[CHUNKS_PER_PAGE];
};

struct page {
  union {
    struct page_header header;
    struct chunk chunks[CHUNKS_PER_PAGE];
  };
};

#define PAGE_HEADER_SIZE (sizeof (struct page_header))
#define FIRST_ALLOCATABLE_CHUNK 1
STATIC_ASSERT_EQ(PAGE_HEADER_SIZE, FIRST_ALLOCATABLE_CHUNK * CHUNK_SIZE);

struct freelist {
  struct freelist *next;
};

struct large_object {
  struct large_object *next;
  size_t size;
};

#define LARGE_OBJECT_HEADER_SIZE (sizeof (struct large_object))

static struct freelist *small_object_freelists[SMALL_OBJECT_CHUNK_KINDS];
static struct large_object *large_objects;

extern void __heap_base;
static size_t walloc_heap_size;

void* malloc(size_t size);

void free(void *ptr);

void* memcpy(void *dest, const void *src, size_t n);

void* realloc(void *ptr, size_t size);

void* memset(void *s, int c, size_t n);

void* calloc(size_t nmemb, size_t size);

#endif