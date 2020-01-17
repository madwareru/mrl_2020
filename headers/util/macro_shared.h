#ifndef MACRO_SHARED_H
#define MACRO_SHARED_H

#include <iostream>

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION_INNER __FILE__ " : " S2(__LINE__)
#define LOCATION " (" LOCATION_INNER ")"

#define REPEAT_2(x) (x), (x)
#define REPEAT_4(x) REPEAT_2(x), REPEAT_2(x)
#define REPEAT_8(x) REPEAT_4(x), REPEAT_4(x)
#define REPEAT_16(x) REPEAT_8(x), REPEAT_8(x)
#define REPEAT_32(x) REPEAT_16(x), REPEAT_16(x)

#define ROW_4_ASCENDING(x) (x), (x) + 1, (x) + 2, (x) + 3
#define ROW_8_ASCENDING(x) ROW_4_ASCENDING(x), ROW_4_ASCENDING((x + 4))
#define ROW_16_ASCENDING(x) ROW_8_ASCENDING(x), ROW_8_ASCENDING((x + 8))
#define ROW_32_ASCENDING(x) ROW_16_ASCENDING(x), ROW_16_ASCENDING((x + 16))
#define ROW_64_ASCENDING(x) ROW_32_ASCENDING(x), ROW_32_ASCENDING((x + 32))

#define LOG(message_sequence) std::cout << message_sequence << LOCATION << std::endl
#define LOG_ERROR(message_sequence) std::cerr << message_sequence << LOCATION << std::endl

#define LOG_ASSERT_ON

#ifdef LOG_ASSERT_ON
    #define LOG_ASSERT(cond)                          \
        if(!(cond)) {                                 \
            LOG_ERROR("Assertion failed: " << #cond); \
            abort();                                  \
        }
#else
    #define LOG_ASSERT(cond)
#endif

#endif // MACRO_SHARED_H
