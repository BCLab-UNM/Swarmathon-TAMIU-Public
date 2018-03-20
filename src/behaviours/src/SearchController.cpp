//code version 3162018
#include "SearchController.h"
#include <angles/angles.h>
#include <iostream>
using namespace std;

double wumbo=5.0, smittywerbenjagermanjensen=5.0, mermaidman=0.0, barnacleboy=0.0,pinheadlarry=0,dirtydan=0, a=8,b=8,c=0,d=0, f=0,z=0,q=0;
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



    if (first_waypoint)//(first_waypoint)//works march 7
    {
      first_waypoint = false;//works march 7
      searchLocation.theta = currentLocation.theta + M_PI;//works march 7
	cout<<"1searchLocation.theta ";
	cout<<searchLocation.theta;
      searchLocation.x = currentLocation.x + (5.15 * cos(searchLocation.theta)); //works march 7
	cout<<"2searchLocation.x ";
	cout<<searchLocation.x;
      //searchLocation.y = currentLocation.y + (5.15 * sin(searchLocation.theta)); //works march 7
	cout<<"3searchLocation.y ";
	cout<<searchLocation.y;
      
    }
    if(wumbo>0)//works march 7
    {
      //select new heading from Gaussian distribution around current heading
      searchLocation.theta = currentLocation.theta - M_PI/2; //90 degrees in radians//works march 7
	cout<<"4 Square searchLocation.theta";
	cout<<searchLocation.theta;
      searchLocation.x = currentLocation.x + (wumbo * cos(searchLocation.theta)); //CR//works march 7
	cout<<"5 Square searchLocation.x";
	cout<<searchLocation.x;
      searchLocation.y = currentLocation.y + (smittywerbenjagermanjensen * sin(searchLocation.theta)); //works march 7
	cout<<"6 Square searchLocation.y";
	cout<<searchLocation.y;
	wumbo=wumbo-0.3; ///0.4 works //a//works march 7
	smittywerbenjagermanjensen=smittywerbenjagermanjensen-0.3; //b//works march 7

    }

    if(smittywerbenjagermanjensen < 0.5)
{
    searchLocation.x = currentLocation.x + (8.0 * cos(searchLocation.theta)); 
    z=z + 1;
//z = z + 0.2;
    wumbo=0;
    //mermaidman=1;
    //barnacleboy=1;
    
    
}


    if(z > 1.8) //works march 7
    {

      
//select new heading from Gaussian distribution around current heading
      searchLocation.theta = currentLocation.theta + M_PI/2; //90 degrees in radians//works march 7
	
      searchLocation.x = currentLocation.x + (mermaidman * cos(searchLocation.theta)); //CR//works march 7

      searchLocation.y = currentLocation.y + (barnacleboy * sin(searchLocation.theta)); //works march 7

	mermaidman=mermaidman+0.3; ///0.4 works //a //works march 7
	barnacleboy=barnacleboy+0.3; //b //works march 7
        smittywerbenjagermanjensen=1;
        //q=1;
}


     if(barnacleboy>4.5)//4.5 works
{
        z=0;
	searchLocation.theta= centerLocation.theta;
        searchLocation.theta= centerLocation.theta;
        pinheadlarry=1;
}



    if (pinheadlarry >0 )//(first_waypoint)//works march 7
    {
      barnacleboy=0;
      searchLocation.theta = currentLocation.theta + M_PI;//works march 7

      searchLocation.x = currentLocation.x + (8 * cos(searchLocation.theta)); //works march 7
      dirtydan=1;
}




    if(dirtydan >0)//works march 7
    {
      
      pinheadlarry=0;
//select new heading from Gaussian distribution around current heading
      searchLocation.theta = currentLocation.theta - M_PI/2; //90 degrees in radians//works march 7

      searchLocation.x = currentLocation.x + (a * cos(searchLocation.theta)); //CR//works march 7

      searchLocation.y = currentLocation.y + (b * sin(searchLocation.theta)); //works march 7

	a=a-0.3; ///0.4 works //a//works march 7
	b=b-0.3; //b//works march 7

    }


    else
{ 
dirtydan=0;
searchLocation.theta= centerLocation.theta;
first_waypoint=true;

}
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


