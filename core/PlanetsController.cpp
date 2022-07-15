#include "PlanetsController.h"{

EXPORT void PlanetsController::Play(duration elapsed) {
		size_t takts = elapsed / time_peer_frame;
		duration least = elapsed - time_peer_frame * takts;
		for (size_t i = 0; i < takts; i++)
			NextFrame(time_peer_frame);
		NextFrame(least);
        time += elapsed;
	}

EXPORT void PlanetsController::NextFrame(duration elapsed) {
	for (size_t i = 0; i < count; i++) {
		accel_x[i] = 0; accel_y[i] = 0;
	}
	for (size_t i = 0; i < count; i++) {
		for (size_t j = 0; j < count; j++) {
			if (i == j) continue;
			number dx = x[j] - x[i], dy = y[j] - y[i];
			number distance_squad = dx * dx + dy * dy;
			number accel = mass[j] * gravity / distance_squad;
			number distance = sqrt(distance_squad);
			accel_x[i] += accel * dx / distance;
			accel_y[i] += accel * dy / distance;
		}
	}

	for (size_t i = 0; i < count; i++) {
		speed_x[i] += accel_x[i] * elapsed.count();
		speed_y[i] += accel_y[i] * elapsed.count();
		x[i] += speed_x[i] * elapsed.count();
		y[i] += speed_y[i] * elapsed.count();
	}
}

EXPORT std::string PlanetsController::GetTimeDump() const{
	size_t second = time.count();
	size_t minutes = second / 60;
	size_t hours = minutes / 60;
	size_t days = hours / 24;
	size_t years = days / 365;

	second %= 60;
	minutes %= 60;
	hours %= 24;
	days %= 365;

	std::stringstream ss;
	ss  << "Y:" << years << std::endl
		<< "D:" << days << std::endl
		<< "H:" << hours << std::endl
		<< "M:" << minutes << std::endl
		<< "S:" << second << std::endl;
	return ss.str();
}

//#include <boost/filesystem.hpp>
/*
//загружає з файлу конфігурації
init_result file_init(std::string filename)
{
    init_result planets;
    std::ifstream file(filename);

    int orbit_len;
    file >> planets.delta_time >> orbit_len >> planets.vector_scale >> planets.default_scale;
    do
    {
        std::string name;
        long double mass;
        long double density;
        Vector2f position(0,0);
        Vector2f speed(0,0);
        file >> name >> mass >> density >> position.x >> position.y >> speed.x >> speed.y;
        if(!file)break;
        if(name.front()=='_')
        {
            Ship* ship = new Ship(name,mass,density,position,speed,orbit_len);
            planets.planets.push_back(ship);
            planets.trackingStar = ship;
        }
        else
            planets.planets.push_back(new Planet(name,mass,density,position,speed,orbit_len));
    } while(file);
    file.close();
    return planets;
}

init_result random_init()
{
    init_result vect;
    for(int i=0;i<100;i++)
        vect.planets.push_back(new Planet( "None" , pow(10,rand()%10)*10000 , 5500 , Vector2f(rand()%2000-1000 , rand()%2000-1000 ) , Vector2f(0,0),-1));
    return vect;
}
//просто загружає
init_result initplanets()
{
    std::vector<std::string> configs;
    boost::filesystem::directory_iterator dir(boost::filesystem::current_path());
    for( const boost::filesystem::path &p : dir)
        if(p.filename().string().front()=='=')
            configs.push_back(p.filename().string());
    unsigned counter = 0;
    for(const auto &i : configs)
        std::cout << '(' << counter++ << ')' << "Finded new config---" << i << std::endl;
    std::cout << "Enter configuration number:";
    std::cin >> counter;

    return file_init(configs.at(counter));
}
*/
