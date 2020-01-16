/*******************************************************************************
* EECS 397
*
* Assignment Name: Lab_8_WaG
*
* Author: Lemnij, Luca
*
* Purpose: Full hardware driver module for the WaG game
*
* Last Modified: 4/5/2019
*
*******************************************************************************/

#include "mbed.h"
#include "display.h"
#include "stepper.h"
#include "io_pins.h"
#include "testing.h"
#include "carriage.h"
#include "WaG.h"

//#define gnoll_lifetime 20
//#define station_A 1
//#define station_B 0
//#define BAUD_RATE 230400
//#define CALIBRATED 1
//#define NOT_CALIBRATED 0
//#define MAX_VOLLEY_COUNT 15
//
//DigitalIn user_button_2(BUTTON1);
//
//DigitalIn start_button_2(UI_START_BUTTON);
//
//DigitalIn cal_button_2(UI_CAL_BUTTON, PullUp);
//
//Serial pc_2(USBTX, USBRX, BAUD_RATE);
//
//DigitalIn station(UI_STATION_SELECT);
//
//Timer gnoll_timer;
//Timer whacker_timer;
//
//int cal_status = NOT_CALIBRATED;
//int match_cnt; 
//int hit_count;
//int miss_count;
//int volley_no;
//int volley_count;
//
//int correct_whacker_pos;
//int pos_to_seek;
//int gnoll_pos;
//int bcd_array[4]; 
//
//bool button_is_pressed(DigitalIn* button) {
//    if(button == &user_button_2) {
//        if(*button) {
//            return true;
//        } else {
//            return false;
//        }
//    } else {
//        if(!(*button)) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//}
//
//void wait_for_button_to_be_released(DigitalIn* button) {
//    while(button_is_pressed(button)) {
//        ;
//    }
//}
//
//int pick_random_location() {
//    srand(time(NULL));
//    int pos = rand() % 8;
//    if(station == station_A) {
//        return pos;
//    } else {
//        return pos + 8;
//    }
//}
//
////Returns position of the sensor the other side illuminated
//int other_illuminated_sensor() {
//    static int start_pos = station == station_A ? 9 : 1;
//    static int end_pos = station == station_A ? 16 : 8;
//    for(int i = start_pos; i <= end_pos; i++) {
//        if(is_lit(i)) {
//            return i;
//        }
//    }
//    return -1;
//}
//
////Must be called after pos is set in play as gnoller function
//void set_correct_whacker_pos(int pos) {
//    correct_whacker_pos = station == station_A ? pos + 8 : pos - 8;
//}
//
////Sets the correct position for the whacker function to go to and illuminate
//void set_correct_pos_to_seek() {
//    pos_to_seek = station == station_A ? gnoll_pos - 8 : gnoll_pos + 8;
//} 
//
//void update_display() {
//    int score = hit_count * 100 + miss_count;
//    int_to_bcd_array(score, bcd_array);
//    dsp_bcd(bcd_array);
//}
//    
//void play_as_gnoller() {
//    int pos;
//    while(volley_count < MAX_VOLLEY_COUNT) {
//        pos = pick_random_location() + 1;
//        set_correct_whacker_pos(pos);
//        move_to_sensor(pos);
//        turn_on_laser();
//        wait_ms(50);
//        scan_phototransistors(false);
//        illuminate_light(pos);
//        gnoll_timer.reset();
//        gnoll_timer.start();
//        while(1) {
//            scan_phototransistors(false);
//            if(other_illuminated_sensor() == correct_whacker_pos) {
//                ++hit_count;
//                break;
//            } else if(other_illuminated_sensor() != correct_whacker_pos && other_illuminated_sensor() != -1) {
//                ++miss_count;
//                break;
//            } else if(gnoll_timer.read() > gnoll_lifetime) {
//                ++miss_count;
//                break;
//            }
//        }
//        update_display();
//        //Server side error for deluminating so I had to do it this way
//        write_int_to_digit(0x0500, 0);
//        turn_off_laser();
//        ++volley_count;
//        while(other_illuminated_sensor() != -1) {
//            scan_phototransistors(false);
//        }
//    }
//    return;
//}
//
//void play_as_whacker() {
//    while(volley_count < MAX_VOLLEY_COUNT) {
//        scan_phototransistors(false);
//        while((gnoll_pos = other_illuminated_sensor()) == -1) {
//            scan_phototransistors(false);
//        }
//        set_correct_pos_to_seek();
//        move_to_sensor(pos_to_seek);
//        turn_on_laser();
//        whacker_timer.reset();
//        whacker_timer.start();
//        //retry 3 times needs to change to scan my current sensor
//        for(int i = 0; i < 3; i++) {
//            if(!is_lit(pos_to_seek)) {
//                scan_phototransistors(false);
//            } else {
//                break;
//            }
//        }
//        illuminate_light(pos_to_seek);
//        while(is_lit(gnoll_pos) && whacker_timer.read() < 5) {
//            scan_phototransistors(false);
//        }
//        //SERVER SIDE ERROR ON DELUMINATE FUNCTION SO I USED WRITE INT TO DIGIT UNTIL MBED FIXES THIS
//        //deluminate_lights();
//        write_int_to_digit(0x0500, 0);
//        turn_off_laser();
//        ++volley_count;
//    }
//    return;
//}

int main() {
    play_WaG();
}
    

