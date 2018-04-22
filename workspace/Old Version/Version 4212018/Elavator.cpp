#include <vector>
#include <iostream>
using namespace std;


class Elavator
{
    private:
        //The floor the elevator is currently on
        int current_floor = 0;
        //The number of people that are currently in the elevator
        int numberPeople = 0;
        //A boolean vector of floors that need to be stopped at
        vector<bool> FloorsToDropOffPeople;
        //A vector of how many people are getting off at each floor
        vector<int> peopleGoingtoEachFloor;
        //Is the elevator going up
        bool goingUp = true;
        //Is the elevator going down
        bool goingDown = false;
        //How fast does the elevator travel
        double speed;
        
        int numFloors = 5;
    public:
    //Constructor for the elevator when passing in speed and intial floor
    Elavator(double speed,int numFloor)
    {
        numFloors = numFloor;
        FloorsToDropOffPeople.assign(numFloors,false);
        peopleGoingtoEachFloor.assign(numFloors,0);
        this->speed = speed;
        current_floor = 0;
    }
    //Default constructor for the elevator
    Elavator()
    {
        FloorsToDropOffPeople.assign(6,false);
        peopleGoingtoEachFloor.assign(6,0);
        this->speed = 10;
        current_floor = 0;
    }
    
       //Gets Direction of Elavator
    bool getDirection()
    {
        //If true then the elevator is going up
        return goingUp;
    }
    
    //Returns the current floor of the elevator
    int getFloor() const
    {
        return current_floor;
    }
    
    vector<bool> getStops()
    {
        return FloorsToDropOffPeople;
    }
    
    int getNumFloors()
    {
        return numFloors;
    }
    //Gets the number of people
     int getnumPeople() const
    {
        return numberPeople;
    }
    //Sets the floor value for an elevator
    int setFloor(int userFloorInput)
    {
        current_floor = userFloorInput;
    }
    void setDirection(bool dir)
    {
        if(dir)
        {
            goingDown = false;
            goingUp = true;
        }
        else
        {
            goingDown = true;
            goingUp = false;
        }
    }
    
    void changeDirection()
    {
        if(goingUp)
        {
            goingDown = true;
            goingUp = false;
        }
        else
        {
            goingDown = false;
            goingUp = true;
        }
    }
    
    //This function will continue to run infinitely, 
    //it deals with transporting the people around
    void moveElavator()
    {
        //If the elevator is going up
        if (goingUp)
        {
            //It moves up one floor
            goUp1();
            //If the elevator is at the top floor then it starts going down
            if (getFloor() == (numFloors-1))
            {
                goingDown = true;
                goingUp = false;
            }
        }
        //If the elevator is going down
        else if (goingDown)
        {
            //It moves down one floor
            goDown1();
            //If the elevator is at the bottom floor then it starts going up 
            if (getFloor() == 0)
            {
                goingDown = false;
                goingUp = true;
            }
        }
    }

    vector<int> pickPeopleUp(vector<int> peopleOnFloor, bool up)
    {   
        if(up)
        {
                
                for(int i = getFloor(); i< getNumFloors();i++)
                {
                    peopleGetOn(peopleOnFloor, i);
                    peopleOnFloor.at(i) = 0;
                }
        cout <<endl;
        }
        else
        {
                for(int i = getFloor(); i> 0;i--)
                {
                    peopleGetOn(peopleOnFloor, i);
                    peopleOnFloor.at(i) = 0;
                }
        cout <<endl;
        }
        
        return peopleOnFloor;
    }
    
    //Call this function to make the elevator move up
    void goUp1()
    {
        //sleep(1000);
        cout << "Previous Floor " << getFloor() << endl;
        cout << "Going UP" << endl;
        setFloor(getFloor()+1);
        cout << "Current Floor after moving up : " << getFloor() << " " << endl;
        
    }
    
    //Call this function to make the elevator move down
    void goDown1()
    {
        //sleep(1000);
        cout << "Previous Floor " << getFloor() << endl;
        cout << "Going DOWN" << endl;
        setFloor(getFloor()-1);
        cout << "Current Floor after moving down : " << getFloor() << " " << endl;
    }
    
    //Call this function when people get off of the elevator
    void PeopleExit()
    {
        int peopleExiting = peopleGoingtoEachFloor.at(getFloor());
        //sleep(500*numPeople);
        numberPeople -= peopleExiting;
        FloorsToDropOffPeople.at(getFloor()) = false;
        peopleGoingtoEachFloor.at(getFloor()) = 0;
    }
    
    void peopleGetOn(vector<int> peopleOnFloor, int i)
    {
                peopleGoingtoEachFloor.at(i) += peopleOnFloor.at(i);
                numberPeople += peopleOnFloor.at(i);
                peopleOnFloor.at(i)= 0;
                
                //This tells the elevator to go to the destinations of the different people who just entered
                if(peopleGoingtoEachFloor.at(i)>0)
                {
                    FloorsToDropOffPeople.at(i) = true;
                }
    }
    
    
    void updateStops(vector<bool> floorsToPickUpOn)
    {
        for (int i = 0; i < floorsToPickUpOn.size(); i++)
        {
            FloorsToDropOffPeople.at(i) = (FloorsToDropOffPeople.at(i) || floorsToPickUpOn.at(i)); 
        } 
    }
    
    vector<int> peopleGetOnandOff(vector<int> peopleOnFloor)
    {
        cout << endl << "Stopping on floor " << getFloor() << endl;
        //If people need to get on or off it stops at the floor
        if (FloorsToDropOffPeople.at(getFloor()))
        {
            //People get off the elevator
            peopleOnFloor = pickPeopleUp(peopleOnFloor,true);
            PeopleExit();
        }
        return peopleOnFloor;
    }
};