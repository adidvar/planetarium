#include "orbit_queue.h"

long double step = 1000.0;

void orbit_queue::push(Vector2f element)
{
    if( data.size() !=0 && (data.back()-element).Module() < step )
        return;


    if((int)data.size()==max_element_count)
        data.erase(data.begin());

    data.push_back(element);
}
