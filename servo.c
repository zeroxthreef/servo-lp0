#include "parapin.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void servo(int pin, float deg)
{
	struct timespec t;
	double pulse = (deg/360.0) + 1.0;
	set_pin(LP_PIN[pin]);
	t.tv_sec = 0;
	t.tv_nsec = (long)(pulse * 1000000.0);
	nanosleep(&t, NULL);
	clear_pin(LP_PIN[pin]);

	/* now sleep for the rest of the pulse */

	t.tv_nsec = (long)((20.0 - pulse) * 1000000.0);
	nanosleep(&t, NULL);
}

/* this really isn't the best way to get the servo to hold it's position */
/* a better way would be to set the servo's state and only change it when
 * a new position is given */
void serv_setto(int pin, float deg)
{
	int i;
	for(i = 0; i < 28; i++)
	{
		servo(pin, deg);
	}
}
