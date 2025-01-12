/* This code includes following
   1. Constructor, Destructor, Copy/Move Constructors, Copy/Move Assignment
   2. Virtual and Override
   3. Abstract Class
   4. Inheritance
   5. Multiple Inheritance
   6. Static Member
   7. Delegating Constructor
   8. Access Modifiers
   9. Object Slicing
   10. Default Keyword
 */

#include <iostream>
#include <memory>
#include <string>

class Engine {
 public:
  Engine(int horsePower) : mHorsePower(horsePower) {
    std::cout << "Engine constructor called" << std::endl;
  };
  int getHorsePower() const { return mHorsePower; }

 private:
  int mHorsePower;
};

// Base class
class Car {
 public:
  // Constructor
  Car() = default;

  Car(const std::string& make, const std::string& model, int year,
      std::unique_ptr<Engine> engine)
      : mMake(make), mModel(model), mYear(year), mEngine(std::move(engine)) {
    ++carCount;
    std::cout << "Car constructor called " << std::endl;
  };

  // Copy constructor
  Car(const Car& car) : mMake(car.mMake), mModel(car.mModel), mYear(car.mYear) {
    if (car.mEngine) mEngine = std::make_unique<Engine>(*car.mEngine);
    std::cout << "Car copy constructor called" << std::endl;
  }

  // Move constructor
  Car(Car&& car) noexcept
      : mMake(std::move(car.mMake)),
        mModel(std::move(car.mModel)),
        mYear(car.mYear),
        mEngine(std::move(car.mEngine)) {
    std::cout << "Car move constructor called" << std::endl;
    car.mMake.clear();
    car.mModel.clear();
    car.mEngine = nullptr;
  }

  // Copy assignment operator
  Car& operator=(const Car& car) {
    std::cout << "Car copy assignment called" << std::endl;
    if (this != &car) {
      mMake = car.mMake;
      mModel = car.mModel;
      mYear = car.mYear;
      if (car.mEngine) mEngine = std::make_unique<Engine>(*car.mEngine);
    }

    return *this;
  }

  // Move assignment operator
  Car& operator=(Car&& car) noexcept {
    std::cout << "Car move assignment called" << std::endl;
    if (this != &car) {
      mMake = std::move(car.mMake);
      mModel = std::move(car.mModel);
      mYear = car.mYear;
      mEngine = std::move(car.mEngine);

      car.mMake.clear();
      car.mModel.clear();
      car.mEngine = nullptr;
    }

    return *this;
  }

  // Deligating constuctor
  Car(const std::string& make, const std::string& model)
      : Car(make, model, 2023, std::make_unique<Engine>(200)) {}

  // Destructor
  virtual ~Car() {
    std::cout << "Car destructor called" << std::endl;
    --carCount;
  }

  virtual void printInfo() const {
    std::cout << "Make: " << mMake << std::endl;
    std::cout << "Model: " << mModel << std::endl;
    std::cout << "Year: " << mYear << std::endl;
    std::cout << "Engine HorsPower: " << mEngine->getHorsePower() << std::endl;
  }

  static void printCarNumber() {
    std::cout << "Car number: " << carCount << std::endl;
  }

  int getYear() const { return mYear; }

  bool isOlderThan(int mYear) { return this->mYear < mYear ? true : false; }

 private:
  std::string mMake;
  std::string mModel;
  int mYear;
  std::unique_ptr<Engine> mEngine;
  static int carCount;
};

// Static memeber initilization
int Car::carCount{0};

class FuelCar : virtual public Car {
 public:
  enum class FuelType { Gasoline, Diesel };

  // Constructor
  FuelCar(FuelType fuelType) : mFuelType(fuelType) {
    std::cout << "FuelCar constructor called." << std::endl;
  };

  // Copy constructor
  FuelCar(const FuelCar& fuelCar) : mFuelType(fuelCar.mFuelType) {
    std::cout << "FuelCar copy constructor called." << std::endl;
  }

  // Move constructor
  FuelCar(FuelCar&& fuelCar) noexcept : mFuelType(fuelCar.mFuelType) {
    std::cout << "FuelCar move constructor called." << std::endl;
  }

  // Copy assignment
  FuelCar& operator=(const FuelCar& fuelCar) {
    if (this == &fuelCar) return *this;
    mFuelType = fuelCar.mFuelType;
    std::cout << "FuelCar copy assignment called." << std::endl;

    return *this;
  }

  // Move assignment
  FuelCar& operator=(FuelCar&& fuelCar) noexcept {
    if (this == &fuelCar) return *this;
    mFuelType = fuelCar.mFuelType;
    std::cout << "FuelCar move assignment called." << std::endl;

    return *this;
  }

  // Destructor
  virtual ~FuelCar() { std::cout << "FuelCar destructor called" << std::endl; }

  // Pure virtual function
  virtual void refuel() const = 0;

 private:
  FuelType mFuelType;
};

class GasolineCar : public FuelCar {
 public:
  // Constructor
  GasolineCar(const std::string& make, const std::string& model, int year,
              std::unique_ptr<Engine> engine,
              const FuelCar::FuelType fuelType = FuelCar::FuelType::Gasoline)
      : Car(make, model, year, std::move(engine)), FuelCar(fuelType) {
    std::cout << "GasolineCar constructor called" << std::endl;
  }

  // Copy constructor
  GasolineCar(const GasolineCar& gasolineCar)
      : Car(gasolineCar), FuelCar(gasolineCar) {
    std::cout << "GasolineCar copy constructor called." << std::endl;
  }

  // Move constructor
  GasolineCar(GasolineCar&& gasolineCar) noexcept
      : Car(std::move(gasolineCar)), FuelCar(std::move(gasolineCar)) {
    std::cout << "GasolineCar move constructor called." << std::endl;
  }

  // Copy assignment operator
  GasolineCar& operator=(const GasolineCar& gasolineCar) {
    if (this == &gasolineCar) return *this;
    Car::operator=(gasolineCar);
    FuelCar::operator=(gasolineCar);
    std::cout << "GasolineCar copy assignment called." << std::endl;

    return *this;
  }

  // Move assignment operator
  GasolineCar& operator=(GasolineCar&& gasolineCar) noexcept {
    if (this == &gasolineCar) return *this;
    Car::operator=(std::move(gasolineCar));
    FuelCar::operator=(std::move(gasolineCar));
    std::cout << "GasolineCar move assignment called." << std::endl;

    return *this;
  }

  // Destructor
  ~GasolineCar() override {
    std::cout << "GasolineCar destructor called." << std::endl;
  }

  void refuel() const override {
    std::cout << "Refueling gasoline car ..." << std::endl;
  }

  void printInfo() const override {
    Car::printInfo();
    std::cout << "Fuel type: Gasoline" << std::endl;
  }
};

class DieselCar : public FuelCar {
 public:
  // Constructor
  DieselCar(const std::string& make, const std::string& model, int year,
            std::unique_ptr<Engine> engine,
            const FuelCar::FuelType fuelType = FuelCar::FuelType::Diesel)
      : Car(make, model, year, std::move(engine)), FuelCar(fuelType) {
    std::cout << "DieselCar constructor called." << std::endl;
  }

  // Copy constructor
  DieselCar(const DieselCar& dieselCar) : Car(dieselCar), FuelCar(dieselCar) {
    std::cout << "DieselCar copy constructor called." << std::endl;
  }

  // Move constructor
  DieselCar(DieselCar&& dieselCar)
      : Car(std::move(dieselCar)), FuelCar(std::move(dieselCar)) {
    std::cout << "DieselCar move constructor called." << std::endl;
  }

  // Copy assignment operator
  DieselCar& operator=(const DieselCar& dieselCar) {
    if (this == &dieselCar) return *this;
    Car::operator=(dieselCar), FuelCar::operator=(dieselCar);
    std::cout << "DieselCar copy assignment called." << std::endl;
    return *this;
  }

  // Move assignment operator
  DieselCar& operator=(DieselCar&& dieselCar) {
    if (this == &dieselCar) return *this;
    Car::operator=(std::move(dieselCar)),
    FuelCar::operator=(std::move(dieselCar));
    std::cout << "DieselCar move assignment called." << std::endl;
    return *this;
  }

  // Destructor
  ~DieselCar() { std::cout << "DieselCar constructor called." << std::endl; }

  void refuel() const override {
    std::cout << "Refueling diesel car..." << std::endl;
  }

  void printInfo() const override {
    Car::printInfo();
    std::cout << "Fuel type: Disel" << std::endl;
  }
};

class ElectricCar : virtual public Car {
 public:
  // Constructor
  ElectricCar(const std::string& make, const std::string& model, int year,
              std::unique_ptr<Engine> engine, int batteryCapacity,
              bool isMostDerivedClass = true)
      : Car(make, model, year, std::move(engine)),
        mBatteryCapacity(batteryCapacity),
        mIsMostDerivedClass(isMostDerivedClass) {
    std::cout << "ElectricCar constructor called" << std::endl;
  }

  // Copy constructor
  ElectricCar(const ElectricCar& electricCar)
      : Car(electricCar),
        mBatteryCapacity(electricCar.mBatteryCapacity),
        mIsMostDerivedClass(electricCar.mIsMostDerivedClass) {
    std::cout << "ElectricCar copy constructor called." << std::endl;
  }

  // Move constructor
  ElectricCar(ElectricCar&& electricCar) noexcept
      : Car(std::move(electricCar)),
        mBatteryCapacity(electricCar.mBatteryCapacity),
        mIsMostDerivedClass(electricCar.mIsMostDerivedClass) {
    std::cout << "ElectricCar move constructor called." << std::endl;
  }

  // Copy assignment
  ElectricCar& operator=(const ElectricCar& electricCar) {
    if (this == &electricCar) return *this;
    mIsMostDerivedClass = electricCar.mIsMostDerivedClass;
    mBatteryCapacity = electricCar.mBatteryCapacity;
    if (mIsMostDerivedClass) Car::operator=(electricCar);
    std::cout << "ElectricCar copy assignment called." << std::endl;

    return *this;
  }

  // Move assignment
  ElectricCar& operator=(ElectricCar&& electricCar) noexcept {
    if (this == &electricCar) return *this;
    mIsMostDerivedClass = electricCar.mIsMostDerivedClass;
    mBatteryCapacity = electricCar.mBatteryCapacity;
    if (mIsMostDerivedClass) Car::operator=(std::move(electricCar));
    std::cout << "ElectricCar move assignment called." << std::endl;

    return *this;
  }

  // Destructor
  ~ElectricCar() { std::cout << "ElectricCar destructor called." << std::endl; }

  void charge() const { std::cout << "Charging electric car..." << std::endl; }

  void printInfo() const override {
    Car::printInfo();
    std::cout << "Battery capacity: " << mBatteryCapacity << std::endl;
  }

 private:
  int mBatteryCapacity;
  bool mIsMostDerivedClass;
};

class HybridCar : public FuelCar, public ElectricCar {
 public:
  // Constructor
  HybridCar(const std::string& make, const std::string& model, int year,
            std::unique_ptr<Engine> engine, int batteryCapacity,
            FuelCar::FuelType fuelType)
      : Car(make, model, year, std::move(engine)),
        FuelCar(fuelType),
        ElectricCar(make, model, year, nullptr, batteryCapacity, false),
        mBatteryCapacity(batteryCapacity),
        mFuelType(fuelType) {
    std::cout << "HybridCar constructor called." << std::endl;
  }

  // Copy constructor
  HybridCar(const HybridCar& hybridCar)
      : Car(hybridCar),
        FuelCar(hybridCar),
        ElectricCar(hybridCar),
        mBatteryCapacity(hybridCar.mBatteryCapacity),
        mFuelType(hybridCar.mFuelType) {
    std::cout << "HybridCar copy constructor called." << std::endl;
  }

  // Move constructor
  HybridCar(HybridCar&& hybridCar) noexcept
      : Car(std::move(hybridCar)),
        FuelCar(std::move(hybridCar)),
        ElectricCar(std::move(hybridCar)),
        mBatteryCapacity(hybridCar.mBatteryCapacity),
        mFuelType(hybridCar.mFuelType) {
    std::cout << "HybridCar move constructor called." << std::endl;
  }

  // Copy assignment
  HybridCar& operator=(const HybridCar& hybridCar) {
    if (this == &hybridCar) return *this;
    // Car::operator=(hybridCar);
    FuelCar::operator=(hybridCar);
    ElectricCar::operator=(hybridCar);
    Car::operator=(hybridCar);
    mBatteryCapacity = hybridCar.mBatteryCapacity;
    mFuelType = hybridCar.mFuelType;
    std::cout << "HybridCar copy assignment called." << std::endl;

    return *this;
  }

  // Move assignment
  HybridCar& operator=(HybridCar&& hybridCar) noexcept {
    if (this == &hybridCar) return *this;
    Car::operator=(std::move(hybridCar));
    FuelCar::operator=(std::move(hybridCar));
    ElectricCar::operator=(std::move(hybridCar));
    mBatteryCapacity = hybridCar.mBatteryCapacity;
    mFuelType = hybridCar.mFuelType;
    std::cout << "HybridCar move assignment called." << std::endl;

    return *this;
  }

  // Destructor
  ~HybridCar() { std::cout << "HybridCar destructor called." << std::endl; }

  void charge() const { std::cout << "Charging hybrid Car..." << std::endl; }

  void refuel() const override {
    std::cout << "Refueling hybrid car..." << std::endl;
  }

  void printInfo() const override {
    Car::printInfo();
    std::cout << "Battery capacity: " << mBatteryCapacity << " khw "
              << std::endl;
    std::cout << "Fuel type: "
              << (mFuelType == FuelCar::FuelType::Gasoline ? " Gasoline"
                                                           : "Diesel")
              << std::endl;
  }

 private:
  int mBatteryCapacity;
  FuelCar::FuelType mFuelType;
};

int main() {
  Car* carPtr;

  // Constructor
  GasolineCar gasCar("Toyota", "Camry", 2022, std::make_unique<Engine>(180));
  std::cout << std::endl;

  // Copy constructor
  GasolineCar copyConstructorGasCar{gasCar};
  std::cout << std::endl;

  // Move constructor
  GasolineCar moveConstructorGasCar{std::move(gasCar)};
  std::cout << std::endl;

  // Copy assignment
  GasolineCar copyAssignmentGasCar("Brand", "Model", 0,
                                   std::make_unique<Engine>(0));
  copyAssignmentGasCar = moveConstructorGasCar;
  std::cout << std::endl;

  // Move assignment
  GasolineCar moveAssignmentGasCar("Brand", "Model", 0,
                                   std::make_unique<Engine>(0));
  moveAssignmentGasCar = std::move(moveConstructorGasCar);
  std::cout << std::endl;

  carPtr = &moveAssignmentGasCar;
  moveAssignmentGasCar.refuel();
  carPtr->printInfo();
  std::cout << std::endl;

  // Constructor
  DieselCar dieselCar("Mercedes", "Benz", 2023, std::make_unique<Engine>(220));
  std::cout << std::endl;

  // Copy constructor
  DieselCar copyConstructorDieselCar{dieselCar};
  std::cout << std::endl;

  // Move constructor
  DieselCar moveConstructorDieselCar{std::move(dieselCar)};
  std::cout << std::endl;

  // Copy assignment
  DieselCar copyAssignmentDieselCar("Brand", "Model", 0,
                                    std::make_unique<Engine>(0));
  copyAssignmentDieselCar = moveConstructorDieselCar;
  std::cout << std::endl;

  // Move assignment
  DieselCar moveAssignmentDieselCar("Brand", "Model", 0,
                                    std::make_unique<Engine>(0));
  moveAssignmentDieselCar = std::move(moveConstructorDieselCar);
  std::cout << std::endl;

  carPtr = &moveAssignmentDieselCar;
  moveAssignmentDieselCar.refuel();
  carPtr->printInfo();
  std::cout << std::endl;

  // Constructor
  ElectricCar electricCar("Tesla", "Model 3", 2023,
                          std::make_unique<Engine>(180), 80);
  std::cout << std::endl;

  // Copy constructor
  ElectricCar copyConstructorElectricCar{electricCar};
  std::cout << std::endl;

  // Move constructor
  ElectricCar moveConstructorElectricCar{std::move(electricCar)};
  std::cout << std::endl;

  // Copy assignment
  ElectricCar copyAssignmentElectricCar("Brand", "Model", 0,
                                        std::make_unique<Engine>(0), 0);
  copyAssignmentElectricCar = moveConstructorElectricCar;
  std::cout << std::endl;

  // Move assignment
  ElectricCar moveAssignmentElectricCar("Brand", "Model", 0,
                                        std::make_unique<Engine>(0), 0);
  moveAssignmentElectricCar = std::move(moveConstructorElectricCar);
  std::cout << std::endl;

  carPtr = &moveAssignmentElectricCar;
  moveAssignmentElectricCar.charge();
  carPtr->printInfo();
  std::cout << std::endl;

  // Constructor
  HybridCar hybridCar("Toyota", "Prius", 2024, std::make_unique<Engine>(120),
                      10, FuelCar::FuelType::Gasoline);
  std::cout << std::endl;

  // Copy constructor
  HybridCar copyConstructorHybridCar{hybridCar};
  std::cout << std::endl;

  // Move constructor
  HybridCar moveConstructorHybridCar{std::move(hybridCar)};
  std::cout << std::endl;

  // Copy assignment
  HybridCar copyAssignmentHybridCar("Brand", "Model", 0,
                                    std::make_unique<Engine>(0), 0,
                                    FuelCar::FuelType::Gasoline);
  copyAssignmentHybridCar = moveConstructorHybridCar;
  std::cout << std::endl;

  // Move assignment
  HybridCar moveAssignmentHybridCar("Brand", "Model", 0,
                                    std::make_unique<Engine>(0), 0,
                                    FuelCar::FuelType::Gasoline);
  moveAssignmentHybridCar = std::move(moveConstructorHybridCar);
  std::cout << std::endl;

  carPtr = &moveAssignmentHybridCar;
  moveAssignmentHybridCar.refuel();
  moveAssignmentHybridCar.charge();
  carPtr->printInfo();
  std::cout << std::endl;

  Car::printCarNumber();
  std::cout << std::endl;
  return 0;
}

