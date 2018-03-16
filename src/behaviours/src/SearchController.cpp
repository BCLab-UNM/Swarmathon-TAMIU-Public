//code version 3162018
#include "SearchController.h"
#include <angles/angles.h>


double wumbo=0, smittywerbenjagermanjensen=6.3, mermaidman=0.1, barnacleboy=0.1,pinheadlarry=0, a=9,b=9,c=0,d=0, f=0,z=0,q=10;
SearchController::SearchController() {
  rng = new random_numbers::RandomNumberGenerator();
  currentLocation.x = 0;
  currentLocation.y = 0;
  currentLocation.theta = 0;

  centerLocation.x = 0;
  centerLocation.y = 0;
  centerLocation.theta = 0;
  result.PIDMode = FAST_PID;

  result.fingerAngle = M_PI/2;
  result.wristAngle = M_PI/4;
}

void SearchController::Reset() {
  result.reset = false;
}

/**
 * This code implements a basic random walk search.
 */
Result SearchController::DoWork() {

  if (!result.wpts.waypoints.empty()) {
    if (hypot(result.wpts.waypoints[0].x-currentLocation.x, result.wpts.waypoints[0].y-currentLocation.y) < 2.7) {
      attemptCount = 0;
    }
  }

  if (attemptCount > 0 && attemptCount < 5) {
    attemptCount++;
    if (succesfullPickup) {
      succesfullPickup = false;
      attemptCount = 1;
    }
    return result;
  }
  else if (attemptCount >= 5 || attemptCount == 0) 
  {
    attemptCount = 1;


    result.type = waypoint;
    Point  searchLocation;

    if (first_waypoint)
    {
      first_waypoint = false;//works march 16 //inital position for spiral
      searchLocation.theta = currentLocation.theta + M_PI;//works march 16
      searchLocation.x = currentLocation.x + (5.10 * cos(searchLocation.theta)); //works march 16
      searchLocation.y = currentLocation.y + (5.10 * sin(searchLocation.theta)); //works march 16
      wumbo = 5.6;
    }
    else if(wumbo>0)//works march 16 // Square spiral
    {
      
      searchLocation.theta = currentLocation.theta - M_PI/2; //90 degrees in radians//works march 16
      searchLocation.x = currentLocation.x + (wumbo * cos(searchLocation.theta)); //CR//works march 16
      searchLocation.y = currentLocation.y + (smittywerbenjagermanjensen * sin(searchLocation.theta)); //works march 16
	wumbo=wumbo-0.3; ///0.4 works //a//works march 16
	smittywerbenjagermanjensen = smittywerbenjagermanjensen-0.3; //b//works march 16

    }


///////experimental march 16



   else if (smittywerbenjagermanjensen<1.5)//works march 16 //this allows the rovers to move to next quadrant downwards
{

	//searchLocation.theta = currentLocation.theta - M_PI;// works march 16
        searchLocation.x = currentLocation.x +(6.35 * cos(searchLocation.theta)); //works march 16 //2.35 works
        searchLocation.y = currentLocation.y +(0.0 * sin(searchLocation.theta)); //works march 16
	smittywerbenjagermanjensen=3;
	
	q=0.4;
}
  else if (q<0.5) // reverse square spiral
   {
     
      searchLocation.theta = currentLocation.theta - M_PI/2; //90 degrees in radians_change 4:42
      searchLocation.x = currentLocation.x + (mermaidman * cos(searchLocation.theta)); 
      searchLocation.y = currentLocation.y + (barnacleboy * sin(searchLocation.theta)); 
	mermaidman=mermaidman+0.3; 
	barnacleboy=barnacleboy+0.3;
   }




  /*  else if (q<0.5) //EH big field
    { 
	
      //select new heading from Gaussian distribution around current heading
      searchLocation.theta = currentLocation.theta - M_PI/2; //90 degrees in radians
      searchLocation.x = currentLocation.x + (a * cos(searchLocation.theta)); //CR
      searchLocation.y = currentLocation.y + (b * sin(searchLocation.theta)); //CR
	a=a-0.3; ///0.4 works //CR//a
	b=b-0.3; //b
   }
   */






    result.wpts.waypoints.clear();
    result.wpts.waypoints.insert(result.wpts.waypoints.begin(), searchLocation);
    
    return result;
  }

}

void SearchController::SetCenterLocation(Point centerLocation) {
  
  float diffX = this->centerLocation.x - centerLocation.x;
  float diffY = this->centerLocation.y - centerLocation.y;
  this->centerLocation = centerLocation;
  
  if (!result.wpts.waypoints.empty())
  {
  result.wpts.waypoints.back().x -= diffX;
  result.wpts.waypoints.back().y -= diffY;
  }
  
}

void SearchController::SetCurrentLocation(Point currentLocation) {
  this->currentLocation = currentLocation;
}

void SearchController::ProcessData() {
}

bool SearchController::ShouldInterrupt(){
  ProcessData();

  return false;
}

bool SearchController::HasWork() {
  return true;
}

void SearchController::SetSuccesfullPickup() {
  succesfullPickup = true;
}


