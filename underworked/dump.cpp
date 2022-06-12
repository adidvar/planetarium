#include "dump.h"
#include <fstream>

using namespace std;

void dump(std::vector<Planet *> planets)
{
    ofstream file;
    static int dump_id = 1;
    file.open("dump"+to_string(dump_id)+".csv");

    file << "sep =," << endl;
    for(auto i : planets)
    {
        file << i->GetName() << ','
         << i->GetMass() << ','
         << i->GetDestiny() << ','
         << i->GetPosition().x << ','
         << i->GetPosition().y << ','
         << i->GetSpeed().x << ','
         << i->GetSpeed().y << ','
         << i->GetAccel().x << ','
         << i->GetAccel().y << endl;
    }
    dump_id++;

    file.close();
}
