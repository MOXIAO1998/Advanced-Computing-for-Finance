//
// Created by Moxiao Li on 4/5/26.
//

#ifndef ADVANCED_COMPUTING_FOR_FINANCE_ALIGNED_MOMORY_H
#define ADVANCED_COMPUTING_FOR_FINANCE_ALIGNED_MOMORY_H


#include <cstddef>


double* allocate_aligned_doubles(std::size_t count, std::size_t alignment = 64);
void free_aligned(double* ptr);

#endif //ADVANCED_COMPUTING_FOR_FINANCE_ALIGNED_MOMORY_H