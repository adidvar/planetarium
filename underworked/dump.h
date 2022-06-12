#ifndef DUMP_H
#define DUMP_H
#include "planet.h"
#include <vector>

/**
 * @brief зберігає стан системи в файл csv
 * @param planets список планет
 */
void dump(std::vector<Planet*> planets);

#endif // DUMP_H
