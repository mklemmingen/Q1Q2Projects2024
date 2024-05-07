/*
 Buffer as Queue
 */

package src;

import java.util.Queue;
import java.util.LinkedList;

import java.util.List;

public class ParkingLot{
    private Queue<Car> parkingLot;

    private List<Car> parkingLotList;

    private int numberQuadrants;

    private int capacity;

    private int currentNumberOfCars;

    public ParkingLot(int numberQuadrants, int capacity) {
        parkingLot = new LinkedList<>();

        this.numberQuadrants = numberQuadrants;
        this.capacity = capacity;
    }

    // ------------------ BUFFER callable METHODS form Producer and Consumer with! ACCESS CONTROLL ------------------

    

    // ------------------ Parking Lot ------------------

    public void addCar(Car car) {
        parkingLot.add(car);
        parkingLotList.add(car);
        currentNumberOfCars++;
    }

    public void removeCar(Car car) {
        parkingLot.remove(car);
        parkingLotList.remove(car);
        currentNumberOfCars--;
    }

    public void printParkingLot() {
        for (Car car : parkingLot) {
            System.out.println(car);
        }
    }

    public int getNumberQuadrants() {
        return numberQuadrants;
    }

    public int getCapacity() {
        return capacity;
    }

    public List<Car> getParkingLotList() {
        return parkingLotList;
    }

    public void park(Car car) {
        if (parkingLot.size() < capacity) {
            addCar(car);
        } else {
            System.out.println("Parking lot is full. Producer is waiting.");
        }
    }
}
