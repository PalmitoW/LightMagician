/*** MEMORIE ***/
/* BUTTON */
int old_select
int old_start
    
/* TEMPRATURE */
sensors_event_t old_temperature
/*** END MEMORIE ***/

/*** INPUTS *** / 
/* BUTTON */
int select
int start

/* GYRO */
sensors_event_t left_x
sensors_event_t left_y
sensors_event_t left_z
sensors_event_t right_x
sensors_event_t right_y
sensors_event_t right_z
sensors_event_t temperature

/* GESTURE */
int left_gesture
uint16_t left_ambient_light
uint16_t left_red_light
uint16_t left_green_light
uint16_t left_blue_light
int right_gesture
uint16_t right_ambient_light
uint16_t right_red_light
uint16_t right_green_light
uint16_t right_blue_light

