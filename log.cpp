/*
log.cpp
Log类
*/

#include "log.h"

Log::Log(ElevatorParameters* param){
    levels = param->level_num;
    elevs = param->elevator_num;
    fp = fopen(param->output_file,"w");
    if (fp == NULL){
        perror(file_err);
        exit(EXIT_FAILURE);
    }
}

Log::~Log(){
    fflush(fp);
    fclose(fp);
}

void Log::add(int level, int num){

}

void Log::load(int elev_id, int num){

}

void Log::drop(int elev_id, int num){

}

void Log::move(int elev_id, int diff){

}

