#include <iostream>
#include "Building.cpp"
using namespace std;

int main(int argc, char* argv[]) 
{
    //cout << "Why are we still here? Just to suffer? Every night, I can feel my leg... And my arm... even my fingers... The body I've lost... the comrades I've lost... won't stop hurting... It's like they're all still there. You feel it, too, don't you? I'm gonna make them give back our past!" << endl;
    Building b = Building(5,3);
    while(1)
    {
    b.timeStep();
    getchar();
    }
    
}