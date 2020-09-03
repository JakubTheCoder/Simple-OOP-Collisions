#include "Collision.h"

#include <math.h>

 bool Collision::colliding(int xa, int ya, int xb, int yb) 
{

	 int distance = sqrt(pow(xb - xa, 2) + (pow(yb - ya, 2))); //check the distance between 2 points
	 if (distance <= 2) //if distance <= 1
	 {
		 return true;	//return true (objects are colliding)

	 }
	 return false;	//else return false (not colliding)
}