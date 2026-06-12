#include <cstdio>
#include <cstdint>
#include <cstring>
#define printk printf
class MotorDriver{
    public:
    uint32_t step;
    float delay;
void start() {
    printf("motor started");
    step++;
    // while(1) removed for host testing
}
    void Setrate(float ml){
        float sec_for_ml = ((ml/0.002)*51200) / 3600;
        delay = 1000000/sec_for_ml;
    }
    void stop(){
        printk("motor_stopped");
    }
    void reset(){
        step = 0;
    }
    uint32_t getsteps(){
        return step;
    }
};
class Volumetracker{
    public:
    uint32_t step_count;
    public:
    void update(uint32_t steps){
        step_count = steps;
    }           
    float getvol(){
        return step_count*(2.0f /51200);
    }
    void reset(){
        step_count = 0;
    }
};
class Alarmobserver{
    public:
    virtual void update() = 0;
};
class led:public Alarmobserver{
    public:
    void update() override {
        printk("led");
    }
};
class buzzer : public Alarmobserver{
    public:
    void update() override{
        printk("on buzzer");
    }
};
class AlarmManager{
    public:
    Alarmobserver* indication[2];
    uint16_t player_count = 0;
    uint16_t noti_count = 0;
        public:
    void add(Alarmobserver* a){
        indication[player_count] = a;
        player_count++;
    }
    void notify(){
        for(int i = 0 ; i < player_count ; i++){
            indication[i]->update();
        }
        noti_count++;
    }
};
class PumpStateMachine;  // forward declare

class pumpState {
public:
    PumpStateMachine* context;
    void setcontext(PumpStateMachine* obj) {
        context = obj;
    }
    virtual void onenter() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual void occlusion() = 0;
    virtual void complete() = 0;
};
class idleState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};
class primingState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};
class infusingState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};
class pausingState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};
class occlusionState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};
class completeState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};
class PumpStateMachine{
    public:
    pumpState* currentState;
    MotorDriver motor;
    AlarmManager& alarmmanager;
    idleState idlestate;
    primingState primingstate;
    pausingState pausingstate;
    completeState completestate;
    occlusionState occlusionstate;
    infusingState infusingstate;


    public:
    PumpStateMachine(AlarmManager& alarm) :alarmmanager(alarm) { 
        currentState = &idlestate;
        currentState->setcontext(this);
    }
    void setstate(pumpState* newState){
        currentState =  newState;
        currentState->setcontext(this);
        currentState->onenter();
    }
    void stop(){
        currentState->stop();
    }
    void pause(){
        currentState->pause();
    }
    void occlusion(){
        currentState->occlusion();
    }
    void start(){
        currentState->start();
    }
    void complete(){
        currentState->complete();
    }
    void setrate(float ml){
        motor.Setrate(ml);
    }
};

void idleState::onenter()    { printf("idle state"); }
void idleState::start()      { context->setstate(&context->primingstate); printf("starting prime"); }
void idleState::stop()       { printf("already idle"); }
void idleState::pause()      { printf("not started"); }
void idleState::occlusion()  { printf("occlusion ignored"); }
void idleState::complete()   { printf("not started"); }

void primingState::onenter()   { context->motor.start(); }
void primingState::start()     { context->setstate(&context->infusingstate); }
void primingState::stop()      { context->setstate(&context->idlestate); printf("stopped"); }
void primingState::pause()     { printf("cannot pause priming"); }
void primingState::occlusion() { context->setstate(&context->occlusionstate); }
void primingState::complete()  { context->motor.stop(); }

void infusingState::onenter()   { context->motor.start(); printf("infusing"); }
void infusingState::start()     { printf("already infusing"); }
void infusingState::stop()      { context->setstate(&context->idlestate); }
void infusingState::pause()     { context->setstate(&context->pausingstate); }
void infusingState::occlusion() { context->setstate(&context->occlusionstate); }
void infusingState::complete()  { context->setstate(&context->completestate); }

void pausingState::onenter()   { context->motor.stop(); printf("paused"); }
void pausingState::start()     { context->setstate(&context->infusingstate); }
void pausingState::stop()      { context->setstate(&context->idlestate); }
void pausingState::pause()     { printf("already paused"); }
void pausingState::occlusion() { printf("occlusion while paused"); }
void pausingState::complete()  { context->setstate(&context->idlestate); }

void occlusionState::onenter()   { context->motor.stop(); context->alarmmanager.notify(); printf("occlusion!"); }
void occlusionState::start()     { printf("resolve occlusion first"); }
void occlusionState::stop()      { context->setstate(&context->idlestate); }
void occlusionState::pause()     { printf("in fault state"); }
void occlusionState::occlusion() { printf("already in occlusion"); }
void occlusionState::complete()  { printf("already in occlusion"); }

void completeState::onenter()   { context->motor.stop(); printf("complete!"); }
void completeState::start()     { context->setstate(&context->primingstate); }
void completeState::stop()      { printf("already complete"); }
void completeState::pause()     { printf("already complete"); }
void completeState::occlusion() { printf("already complete"); }
void completeState::complete()  { printf("already complete"); }
class commandparser{
    PumpStateMachine* Motor;
    public:
    commandparser(PumpStateMachine* p) : Motor(p){}
    void parse(const char* word){
        if(strcmp(word ,"start") == 0){
            Motor->start();
        }
        else if(strcmp(word ,"stop") == 0){
            Motor->stop();
        }
        else if(strcmp(word , "pause") == 0){
            Motor->pause();
        }
        else if(strcmp(word , "setrate") == 0){
            Motor->setrate(1);
        }
    }
};