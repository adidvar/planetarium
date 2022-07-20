#include "PlanetsController.h"{

PlanetsController::PlanetsController(size_t count, number* mass, number* x, number* y, number* speed_x, number* speed_y, number* density, Options* planets_opts, const Options& global_opts) noexcept :
	count(count),
	mass(mass),
	x(x),
	y(y),
	speed_x(speed_x),
	speed_y(speed_y),
	density(density),
	planets_options(planets_opts),
	global_options(global_opts),
	time{},
	time_peer_frame(std::chrono::seconds(1)),
	accel_x(new number[count]),
	accel_y(new number[count])
{
}

PlanetsController::PlanetsController(PlanetsController&& from) noexcept :
	count(from.count),
	mass(std::move(from.mass)),
	x(std::move(from.x)),
	y(std::move(from.y)),
	speed_x(std::move(from.speed_x)),
	speed_y(std::move(from.speed_y)),
	density(std::move(from.density)),
	planets_options(std::move(from.planets_options)),
	global_options(std::move(from.global_options)),
	time(from.time),
	time_peer_frame(from.time_peer_frame),
	accel_x(std::move(from.accel_x)),
	accel_y(std::move(from.accel_y))
{
};

Planet PlanetsController::operator[](size_t index) const {
	return Planet(GetOption<std::string>(planets_options[index], "name"), mass[index], density[index], x[index], y[index], speed_x[index], speed_y[index], 0, 0);
}

void PlanetsController::SetPrecision(duration dtime) noexcept
{
	time_peer_frame = dtime;
}

void PlanetsController::Play(duration elapsed) {
	size_t takts = elapsed / time_peer_frame;
	duration least = elapsed - time_peer_frame * takts;
	for (size_t i = 0; i < takts; i++)
		NextFrame(time_peer_frame);
	NextFrame(least);
	time += elapsed;
}

void PlanetsController::NextFrame(duration elapsed) {
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

PlanetsController::duration PlanetsController::GetTime() const {
	return time;
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
