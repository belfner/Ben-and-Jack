#include <vector>
#include <numeric>
#include "Elavator.cpp"
using namespace std;

class ElevatorController{
    private:
        int numElevators = 0;
        int numFloors = 0;
        Elavator a = Elavator(10,numFloors);
    public:
        ElevatorController(int numElevators, int numFloors)
        {
            this->numElevators = numElevators;
            this->numFloors = numFloors;
            a = Elavator(10,numFloors);
        }
        ElevatorController()
        {
            this->numElevators = 0;
            this->numFloors = 0;
        }
        
        int getNumFloors()
        {
            return numFloors;
        }
        
        int getNumElevators()
        {
            return numElevators;
        }
        
        void updateControls(vector<vector<int>> peopleOnFloor)
        {
            int floor = a.getFloor();
            bool up = a.getDirection();
            
        }
        
        vector<vector<int>> timeStepController(vector<vector<int>> peopleOnFloor)
        {
            int floor = a.getFloor();
            vector<bool> stopOnFloors = getNewStops(peopleOnFloor,a.getFloor());
            
            cout << "Current Floor" << floor << endl;
            a.updateStops(stopOnFloors);
            if(a.getStops().at(a.getFloor()))
            {
                peopleOnFloor.at(floor) = a.peopleGetOnandOff(peopleOnFloor.at(floor));
            }
            
            stopOnFloors = a.getStops();
            bool peopleAboveOrBelow;
            if(a.getDirection())
            {
                peopleAboveOrBelow = accumulate(stopOnFloors.begin()+a.getFloor(), stopOnFloors.end(), 0);
            }
            else
            {
                peopleAboveOrBelow = accumulate(stopOnFloors.begin(), stopOnFloors.end()-(numFloors-a.getFloor()), 0);
            }
            
            if(!peopleAboveOrBelow)
            {
                if(a.getFloor() != 0 && a.getFloor() != numFloors-1)
                {
                a.changeDirection();
                }
            }
            else
            {
                a.moveElavator();
            }
            
            cout << "Are people in dir "<< peopleAboveOrBelow << endl;
            cout << "What floors to stop on:";
            for(int i =0;i< stopOnFloors.size(); i++)
            {
                cout << stopOnFloors.at(i) << ", ";
            }
            cout << endl;
            cout << endl;
            
            cout << "Number of people currently in elevator " << a.getnumPeople() << endl;
            return peopleOnFloor;
        }
        
        vector<bool> getNewStops(vector<vector<int>> peopleOnFloor, int floor)
        {
            vector<bool> ret;
            if(a.getDirection())
            {
                ret = arePeopleAboveGoingUp(peopleOnFloor, floor);
            }
            else
            {
                ret = arePeopleBelowGoingDown(peopleOnFloor, floor);
            }
            return ret;
        }
        
        vector<bool> arePeopleAboveGoingUp(vector<vector<int>> peopleOnFloor,int floor)
        {
            vector<bool> floors(numFloors,false);
            for(int i = floor; i < numFloors-1; i++)
            {
                if(getSumOfVectorU(peopleOnFloor.at(i),i)>0)
                {
                    floors.at(i) = true;
                }
            }
            return floors;
        }
        
        vector<bool> arePeopleBelowGoingDown(vector<vector<int>> peopleOnFloor, int floor)
        {
            vector<bool> floors(numFloors,false);
            for(int i = floor; i > 0; i--)
            {
                if(getSumOfVectorD(peopleOnFloor.at(i),i)>0)
                {
                    floors.at(i) = true;
                }
            }
            return floors;
        }
        
        int getSumOfVectorU(vector<int> floor, int i)
        {
            return accumulate(floor.begin()+i+1, floor.end(), 0);
        }
        int getSumOfVectorD(vector<int> floor, int i)
        {
            return accumulate(floor.begin(), floor.end()-(numFloors-i-1), 0);
        }
};