#include <vector>
#include <Windows.h>
using namespace std;


class Elevator
{
    private:
        //The floor the elevator is currently on
        int current_floor;
        //The number of people that are currently in the elevator
        int numberPeople;
        //A boolean vector of floors that need to be stopped at
        vector<bool> stopOnFloor;
        //A vector of how many people area 
        vector<int> peopleGoingtoEachFloor;
        bool goingUp;
        bool goingDown;
        double speed;
        double waitTime;
    
    public:
    //Constructor for the elevator when passing in speed and intial floor
    Elevator(double speed, int defaultFloor,int numFloors)
    {
        queuedFloors.assign(numFloors,false);
        peopleGoingtoEachFloor.assign(numFloors,0);
        this.speed = speed;
        current_floor = defaultFloor;
    }
    //Default constructor for the elevator
    Elevator()
    {
        queuedFloors.assign(6,false);
        peopleGoingtoEachFloor.assign(6,0);
        this.speed = 10;
        current_floor = 0;
    }
    //Returns the current floor of the elevator
    int getFloor() const
    {
        return current_floor;
    }
    //Sets the floor value for an elevator
    int setFloor(int userFloorInput)
    {
        current_floor = userFloorInput;
    }
    
    int goToFloor(int floor)
    {
       //FIXME
    }
    //When a person enters the elevator then they input the floor they want to go to, the elevator waits for them to enter, and the number of people in the elevator increases by 1
    void personEnters(int floor)
    {
        floorsChosen.push_back(floor);
        sleep(500);
        numberPeople++;
    }
    //Call this function to make the elevator move up
    void movingUp(int floor)
    {
        sleep(1000);
        setFloor(floor+1)
    }
    
    //Call this function to make the elevator move down
    void movingDown(int floor)
    {
        sleep(1000);
        setFloor(floor-1)
    }
    
    //Call this function when people get off of the elevator
    void PeopleExit(int numPeople)
    {
        sleep(500*numPeople);
        numberPeople -= numPeople;
        stopOnFloor.at(getFloor) = false;
    }
}