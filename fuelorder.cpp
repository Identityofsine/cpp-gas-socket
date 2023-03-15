#include "fuelorder.h"

namespace Fuel{
    
    FuelOrder::FuelOrder(){

    }

    FuelOrder::~FuelOrder(){
        
    }

    FuelOrder::FuelOrder(FuelType ft, double price, int pump) {
        this->fueltype = ft;
        this->price = price;
        this->pump = pump;
    }

    int FuelOrder::getPump(){
        return this->pump;
    }

    double FuelOrder::getPrice(){
        return this->price;
    }
    
    FuelType FuelOrder::getFuelType(){
        return this->fueltype;
    }
}