#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>
#include "plane.h"
using namespace std;

void Plane::inputPlane()
{
  cout << "Name: ";
  cin >> name;
  cout << "Passengers: ";
  cin >> passengers;
  cout << "Fuel capacity (in U.S. gallons): ";
  cin >> fuel;
  cout << "Range (in miles): ";
  cin >> range;
  cout << "Speed (in mph): ";
  cin >> speed;
  cout << "Price: ";
  cin >> price;
  ofstream planeFile("planes.dat", ios::app | ios::binary );
  planeFile.write((char*)this, sizeof(Plane));
  planeFile.close();
} //input

int Plane::getCost(double p, double d) const
{
  if (d <= range)
  {
    int trips = this->getTrips(p);
    double hours = d / speed;
    double fuelCost = d * (double)fuel / range * Plane::gallonPrice * trips;
    double fSal = ceil(passengers / 100.0) * 30 * ceil(2.0 + hours) * trips;
    double pSal = 2 * 100 * ceil((2 + hours)) * trips;
    double maintenance = 0.000025 * price * hours * trips;
    return ceil(fuelCost + fSal + pSal + maintenance);
  } //satisfy range
  
  return -1;
} //getCost

int Plane::getTrips(double totalP) const
{
  return ceil(totalP / passengers);
} //getTrips

int Plane::getRange() const
{
  return range; 
} //getMaxRange

const char* Plane::getName() const
{
  return name;
} //getName

bool Plane::operator<(const Plane& rhs) const
{
  return strcmp(name, rhs.name) < 0;
} //operator <

ostream& operator<<(ostream& os, const Plane& rhs)
{
  os << left << setw(12) << rhs.name << setw(6) << rhs.passengers << setw(6) 
     << rhs.range << setw(6) << rhs.speed << right << setw(6) << rhs.fuel 
     << setfill(' ') << setw(6) << fixed << setprecision(3) 
     << (double)rhs.range / rhs.fuel << setfill(' ') << setw(6) 
     << setprecision(2) << (double)rhs.fuel * Plane::gallonPrice / rhs.range 
     << setfill(' ') << setw(2) << "$" << setfill(' ') << setw(5) 
     << setprecision(1) << (double)rhs.price / 1e6;
  
  return os;
} //Insertion operator 
