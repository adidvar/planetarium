#include "ship_utils.h"
#include <sstream>

std::string ship_stat(init_result &res)
{
    if(res.trackingStar == nullptr)
        return "";

    std::stringstream ss;
    ss << "Speed: " << res.trackingStar->GetSpeed().Module() << " m/s" << std::endl
       << "Acceleration: " << res.trackingStar->GetAccel().Module() << " m/s" << std::endl
       << "Average speed: " << res.trackingStar->AverageSpeed() << " m/s" << std::endl
       << "Distance: " << res.trackingStar->Distance()/1000.0 << " km" << std::endl;
    return ss.str();
}
