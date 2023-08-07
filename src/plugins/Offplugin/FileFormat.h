#include <fstream>
#include <iostream>

#include <boost/dll.hpp>

#include <FileFormat.h>

class OldFileFormat : public FileFormat {
public:
	OldFileFormat() {
	};

	virtual ~OldFileFormat() {
	};

	virtual std::vector<std::string> Formats()
	{
		return { ".oldsystem" };
	};

	virtual PlanetsController Load(const std::string & file_name) override
	{
        std::ifstream file;
        file.open(file_name.c_str());

        size_t count;
        file >> count;
        std::string delta_time, orbit_len, vector_scale, default_scale;
        file >> delta_time >> orbit_len >>vector_scale >> default_scale;
		Options global;
		global.Set("orbit_len", orbit_len);
		global.Set("start_speed", delta_time);
		global.Set("vector_scale", vector_scale);
		global.Set("default_scale", default_scale);

		std::string* name = new std::string[count];
		Options *options = new Options[count];
		number *mass = new number[count];
		number *density = new number[count];
		number *x = new number[count];
		number *y = new number[count];
		number *speed_x = new number[count];
		number *speed_y = new number[count];

        for (size_t i = 0; i < count; i++) {
            if (!file)std::exit(1);
            file >> name[i] >> mass[i] >>density[i] >> x[i] >> y[i] >> speed_x[i] >> speed_y[i];
			options[i].Set("name", name[i]);
        }
        file.close();
        return PlanetsController(count,mass,x,y,speed_x,speed_y,density,options,global);
	};
	
	virtual void Save(const PlanetsController & , const std::string & file_name) override
	{
	
	};
};

