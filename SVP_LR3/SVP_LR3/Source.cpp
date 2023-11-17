#include <iostream>

using namespace std;

class IVehicle
{
public:
    virtual void drive(int kilometrs) = 0;
    virtual void refuel() = 0;
    virtual void printStatus() = 0;
};

class AbstractCar : public IVehicle
{
protected:
    double totalDistance;
    double fuelLevel;
    double fuelConsumption;
    double maxFuel;

public:
    AbstractCar(double fuelConsumption, double maxFuel)
        : totalDistance(0), fuelLevel(0), fuelConsumption(fuelConsumption), maxFuel(maxFuel) {}

    void drive(int kilometers) override {
        int requiredFuel = (kilometers * fuelConsumption) / 100;
        if (fuelLevel < requiredFuel) {
            std::cout << "Недостаточно топлива для прохождения дистанции." << std::endl;
        }
        else {
            totalDistance += kilometers;
            fuelLevel -= requiredFuel;
        }
    }

    void refuel() override {
        fuelLevel = maxFuel;
        std::cout << "Бак заполнен" << std::endl;
    }

    void printStatus() override {
        std::cout << "Общий пробег: " << totalDistance << " км" << std::endl;
        std::cout << "Остаток топлива в баке: " << fuelLevel << " литров" << std::endl;
    }
};

class Sedan : public AbstractCar
{
public:
    Sedan()
        : AbstractCar(8, 60)
    {}
};

class SUV : public AbstractCar
{
public:
    SUV()
        : AbstractCar(10, 70)
    {}
};

class Bus : public AbstractCar
{
public:
    Bus()
        : AbstractCar(15, 150)
    {}
};

class Bicycle : public IVehicle
{
private:
    int totalDistance = 0;
public:
    int get_totalDistance()
    {
        return totalDistance;
    }

    void drive(int kilometrs) override
    {
        totalDistance += kilometrs;
    }

    void refuel() override {};

    void printStatus()
    {
        cout << "Общий пробег: " << get_totalDistance() << "km" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    IVehicle* vehicles[4] = { new Sedan, new SUV, new Bus, new Bicycle };
    for (int i = 0; i < 4; ++i)
    {
        IVehicle* vehicle = vehicles[i];
        vehicle->refuel();
        vehicle->printStatus();
        vehicle->drive(120);
        vehicle->printStatus();
        vehicle->drive(420);
        vehicle->printStatus();
        vehicle->drive(300);
        vehicle->printStatus();
        vehicle->refuel();
        vehicle->drive(300);
        vehicle->printStatus();
        delete vehicle;
        std::cout << std::endl;
    }
}