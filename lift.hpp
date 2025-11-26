#ifndef LIFT_HPP
#define LIFT_HPP

#include <iostream>
#include <iomanip>

enum GeneralState {
    STATE_IDLE,
    STATE_CALLED,
    STATE_MOVING
};

enum EngineState {
    ENGINE_OFF,
    ENGINE_UP,
    ENGINE_DOWN
};

enum DoorState {
    DOORS_OPEN,
    DOORS_CLOSED
};

template <typename T>
class Lift {
private:
    GeneralState gState;
    EngineState eState;
    DoorState dState;

    T currentFloor;
    T targetFloor;
    double currentLoad;

    T minFloor;
    T maxFloor;
    const double maxLoadLimit = 250.0;

    void updateEngineState() {
        if (targetFloor > currentFloor)
            eState = ENGINE_UP;
        else if (targetFloor < currentFloor)
            eState = ENGINE_DOWN;
        else
            eState = ENGINE_OFF;
    }

    bool isLoadValid() {
        return (currentLoad >= 0 && currentLoad <= maxLoadLimit);
    }

public:
    Lift() : minFloor(1), maxFloor(24) {
        Reset();
    }

    Lift(T initialFloor, double initialLoad = 0.0, T minF = 1, T maxF = 24)
        : minFloor(minF), maxFloor(maxF)
    {
        gState = STATE_IDLE;
        eState = ENGINE_OFF;
        dState = DOORS_OPEN;

        if (initialFloor < minFloor || initialFloor > maxFloor)
            currentFloor = minFloor;
        else
            currentFloor = initialFloor;

        targetFloor = currentFloor;

        if (initialLoad < 0.0)
            currentLoad = 0.0;
        else if (initialLoad > maxLoadLimit)
            currentLoad = maxLoadLimit;
        else
            currentLoad = initialLoad;
    }

    Lift(const Lift<T>& other) {
        gState       = other.gState;
        eState       = other.eState;
        dState       = other.dState;
        currentFloor = other.currentFloor;
        targetFloor  = other.targetFloor;
        currentLoad  = other.currentLoad;
        minFloor     = other.minFloor;
        maxFloor     = other.maxFloor;
    }

    void Reset() {
        gState = STATE_IDLE;
        eState = ENGINE_OFF;
        dState = DOORS_OPEN;
        currentFloor = minFloor;
        targetFloor = minFloor;
        currentLoad = 0.0;
    }

    void StartCall(T destinationFloor) {
        if (destinationFloor < minFloor || destinationFloor > maxFloor) {
            std::cout << "Помилка: Невірний поверх!\n";
            return;
        }

        dState = DOORS_CLOSED;
        targetFloor = destinationFloor;
        updateEngineState();
        gState = STATE_CALLED;
    }

    void EndCall() {
        eState = ENGINE_OFF;
        currentFloor = targetFloor;
        dState = DOORS_OPEN;
        gState = STATE_IDLE;
    }

    void LoadCabin(double load) {
        if (load < 0)
            currentLoad = 0.0;
        else if (load > maxLoadLimit)
            currentLoad = maxLoadLimit;
        else
            currentLoad = load;
    }

    void Start(T destinationFloor) {
        if (!isLoadValid()) {
            std::cout << "Помилка: Перевантаження!\n";
            return;
        }

        if (destinationFloor < minFloor || destinationFloor > maxFloor) {
            std::cout << "Помилка: Невірний поверх!\n";
            return;
        }

        dState = DOORS_CLOSED;
        targetFloor = destinationFloor;
        updateEngineState();
        gState = STATE_MOVING;
    }

    void Stop() {
        eState = ENGINE_OFF;
        currentFloor = targetFloor;
        dState = DOORS_OPEN;
        gState = STATE_IDLE;
    }

    GeneralState GetGeneralState() const { return gState; }
    EngineState  GetEngineState()  const { return eState; }
    DoorState    GetDoorState()    const { return dState; }
    T            GetCurrentFloor() const { return currentFloor; }
    T            GetTargetFloor()  const { return targetFloor; }
    double       GetCurrentLoad()  const { return currentLoad; }

    const char* GetGeneralStateName() const {
        switch (gState) {
            case STATE_IDLE:   return "Простій";
            case STATE_CALLED: return "Виклик";
            case STATE_MOVING: return "Перевезення";
            default:           return "N/A";
        }
    }

    const char* GetEngineStateName() const {
        switch (eState) {
            case ENGINE_OFF:   return "Вимкнено";
            case ENGINE_UP:    return "Підйом";
            case ENGINE_DOWN:  return "Спуск";
            default:           return "N/A";
        }
    }

    const char* GetDoorStateName() const {
        switch (dState) {
            case DOORS_OPEN:   return "Відчинені";
            case DOORS_CLOSED: return "Зачинені";
            default:           return "N/A";
        }
    }
};

#endif
