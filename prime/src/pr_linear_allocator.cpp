
#include "prime/pr_linear_allocator.h"
#include "prime/pr_memory.h"

struct PrAllocator
{
	u64 total_size = 0;
	u64 allocated = 0;
	void* memory = nullptr;
};

PrAllocator*
prAllocatorCreate(u64 size)
{
	if (size < PR_MEMORY_MAX) {
		PrAllocator* allocator = nullptr;
		allocator = (PrAllocator*)prMemAlloc(sizeof(PrAllocator));
		allocator->allocated = 0;
		allocator->total_size = size;
		allocator->memory = prMemAlloc(size);
		return allocator;
	}
	PR_ASSERT_MSG(false, "Cannot allocation more than 10 megabyte");
	return nullptr;
}

void
prAllocatorDestroy(PrAllocator* allocator)
{
	PR_ASSERT_MSG(allocator, "Linear Allocator is null");
	prMemFree(allocator->memory, allocator->total_size);

	allocator->memory = nullptr;
	allocator->total_size = 0;
	allocator->allocated = 0;
	prMemFree(allocator, sizeof(PrAllocator));
}

void*
prAllocatorAlloc(PrAllocator* allocator, u64 size)
{
	PR_ASSERT_MSG(allocator, "Linear Allocator is null");
	if (allocator->allocated + size > allocator->total_size) {
		u64 remaining = allocator->total_size - allocator->allocated;
		PrString* msg = prStringFormat("Tried to allocate %lluB, only %lluB remaining.", size, remaining);
		PR_ASSERT_MSG(false, prStringGetBuffer(msg));
		prStringDestroy(msg);
	}

	void* block = ((u8*)allocator->memory) + allocator->allocated;
	allocator->allocated += size;
	return block;
}

void
prAllocatorClear(PrAllocator* allocator)
{
	PR_ASSERT_MSG(allocator, "Linear Allocator is null");
	allocator->allocated = 0;
	prMemZero(allocator->memory, allocator->total_size);
}