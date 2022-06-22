#include <random>
#define TIME static_cast<long int>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())

long int shbRandom(long int);