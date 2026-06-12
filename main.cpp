#include <zephyr/kernel.h>
#include "hardware_driver.hpp"
    AlarmManager alarm;
    led l;
    buzzer buz;
    PumpStateMachine pump(alarm);
    commandparser parser(&pump);
    Volumetracker vt;
    K_THREAD_STACK_DEFINE(thread1,1024);

    struct k_thread my_thread;
    void th_fn(void *arg1, void *arg2, void *arg3 ){
        while(1){
            if(pump.motor.motor_running){
                gpio_pin_set_dt(&step,1);
                k_sleep(K_USEC(pump.motor.delay));
                gpio_pin_set_dt(&step,0);
                k_sleep(K_USEC(pump.motor.delay));
                pump.motor.steps++;
                vt.update(pump.motor.steps);
            }
            k_yield();
        }
    }
int main(void){
    alarm.add(&l);
    alarm.add(&buz);
    pump.setrate(1.0f);
    hardware_init();
    k_thread_create(&my_thread,thread1,K_THREAD_STACK_SIZEOF(thread1),th_fn,NULL,NULL,NULL,5,0,K_NO_WAIT);
    while(1){
        k_sleep(K_MSEC(100));
    }
    return 0;
}
