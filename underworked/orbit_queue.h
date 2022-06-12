#ifndef ORBIT_QUEUE_H
#define ORBIT_QUEUE_H
#include <vector2f.h>
#include <vector>
/**
 * @brief Класс зберігає орбіту
 */
class orbit_queue
{
    std::vector<Vector2f> data;
    int max_element_count;
public:
    orbit_queue(int max_element_count):
        max_element_count(max_element_count){}
    void push(Vector2f element);
    void clear();
    using iterator = std::vector<Vector2f>::reverse_iterator;
    using const_iterator = std::vector<Vector2f>::const_reverse_iterator;

    const_iterator begin() const { return data.crbegin(); }
    const_iterator end() const { return data.crend(); }
};

#endif // ORBIT_QUEUE_H
