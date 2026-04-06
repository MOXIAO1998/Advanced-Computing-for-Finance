#include "../includes/aligned_memory.h"

#include <cstdlib>
#include <new>
#include <stdexcept>

static std::size_t round_up_to_multiple(std::size_t x, std::size_t alignment) {
    return ((x + alignment - 1) / alignment) * alignment;
}

double* allocate_aligned_doubles(std::size_t count, std::size_t alignment) {
    if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
        throw std::invalid_argument("alignment must be a power of two");
    }

    std::size_t bytes = count * sizeof(double);
    std::size_t padded_bytes = round_up_to_multiple(bytes, alignment);

    void* ptr = std::aligned_alloc(alignment, padded_bytes);
    if (!ptr) {
        throw std::bad_alloc();
    }

    return static_cast<double*>(ptr);
}

void free_aligned(double* ptr) {
    std::free(ptr);
}