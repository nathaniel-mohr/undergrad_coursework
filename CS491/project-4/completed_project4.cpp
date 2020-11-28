void Bounce( float dt ) {
	while( dt > EPSILON ) {
		float tmin = dt;	// minimum time to do something
		int which = NOTHING_HIT; // which reason was it for doing the something

		// these four collision times are computed using your projectile motion equations:

		float tleft = (XLEFT + RADIUS - Xnow) / Vxnow;	// time to hit the left wall
		if( tleft > 0.  &&  tleft < tmin ) {
			tmin = tleft;
			which = HIT_LEFT;
		}
		float tright = (XRIGHT - RADIUS - Xnow) / Vxnow;	// time to hit the right wall
		if( tright > 0.  &&  tright < tmin ) {
			tmin = tright;
			which = HIT_RIGHT;
		}
		float tfloor1 = (-Vynow + sqrt((Vynow*Vynow) - 2*Gravity*(Ynow-YBOTTOM-RADIUS))) / Gravity;	// time to hit the floor
		if( tfloor1 > 0.  &&  tfloor1 < tmin ) {
			tmin = tfloor1;
			which = HIT_FLOOR1;
		}
		float tfloor2 = (-Vynow - sqrt((Vynow * Vynow) - 2 * Gravity * (Ynow - YBOTTOM - RADIUS))) / Gravity;	// time to hit the floor (note there are 2 answers)
		if( tfloor2 > 0.  &&  tfloor2 < tmin ) {
			tmin = tfloor2;
			which = HIT_FLOOR2;
		}

		// tmin is now set to the smallest of:
		//	dt, tleft, tright, tfloor1, tfloor2
		// which are positive

		// which is set to:
		//	NOTHING_HIT, HIT_LEFT, HIT_RIGHT, HIT_FLOOR1, or HIT_FLOOR2
		// to show what was the first thing hit

		// take a time step of time length tmin, using the projectile motion equations:
		// if a bounce is going to occur, tmin takes the ball right up to the surface:

		Xnow = Xnow + Vxnow*tmin;
		Vxnow = Vxnow;
		Ynow = Ynow + Vynow*tmin + 0.5*Gravity*tmin*tmin;
		Vynow = Vynow + Gravity*tmin;


		// a "bounce trick":

		if( Ynow < YBOTTOM+RADIUS )
			Ynow = YBOTTOM+RADIUS;		// floating point roundoff sometimes messes up

		if( Xnow < XLEFT+RADIUS )
			Xnow = XLEFT+RADIUS;

		if( Xnow > XRIGHT-RADIUS )
			Xnow = XRIGHT-RADIUS;


		// depending on what caused the bounce, change the proper velocity component:
		// if nothing was hit in this time step, just return:

		switch( which ) {
			case NOTHING_HIT:
				return;

			case HIT_LEFT:
				Vxnow = -CoefRest * Vxnow;
				Vynow = Vynow;
				break;

			case HIT_RIGHT:
				Vxnow = -CoefRest * Vxnow;
				Vynow = Vynow;
				break;

			case HIT_FLOOR1:
				Vynow = -CoefRest * Vynow;
				Vxnow = Vxnow;
				break;

			case HIT_FLOOR2:
				Vynow = -CoefRest * Vynow;
				Vxnow = Vxnow;
				break;
		}

		dt -= tmin;	// after the bounce, we might still have some time step left
	}
}

void WhoAmI( std::string &yourName, std::string &yourEmailAddress ){
        yourName = "Nathaniel Mohr";
        yourEmailAddress = "mohrna@oregonstate.edu" ;
}
