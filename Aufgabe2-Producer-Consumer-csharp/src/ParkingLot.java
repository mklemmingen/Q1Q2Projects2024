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

        // QUEUE
        parkingLot = new LinkedList<Car>();

        // LIST
        parkingLotList = new LinkedList<Car>();

        this.numberQuadrants = numberQuadrants;

        this.capacity = capacity;
    }

    // producer and consumer inner classes ------------------- BUFFER callable METHODS + ACCESS CONTROLL METHOD 

    class Producer extends Thread {

        // variable to store the current car thats being moved till its goal
        private Car currentCar;
        private boolean isCarMoving = false;

        public void run() {
            while (true) {
                if(isCarMoving) {

                    // if car is moving, move it till its goal
                    currentCar.move();
                    System.out.println("Car is moving to quadrant " + currentCar.getStreetQuadrant());

                    // if car is at goal, remove it from parking lot
                    if (currentCar.getStreetQuadrant() == currentCar.getGoalQuadrant()) {
                        isCarMoving = false;
                        // stop car, so its boolean isMoving is false
                        currentCar.stop();
                        // set the car to not used by producer
                        currentCar.setUsedByProducer(false);
                    }

                } else {
                    // if car is not moving (parked or not created yet), create a new car, if possible, and start driving
                    // if the capacity is not full, create a new car and drive it till its at its goal
                    if (parkingLot.size() < capacity) {

                        // create a new car
                        Car car = new Car(numberQuadrants);
                        park(car);
                        currentCar = car;
                        System.out.println("Car is parked in quadrant " + car.getStreetQuadrant());

                        // if no car is moving, get the first car from the parking lot
                        if (!isCarMoving) {
                            currentCar = parkingLot.peek();
                            isCarMoving = true;
                        }
                    } else {
                        System.out.println("Parking lot is full. Producer is waiting.");
                    }
                }

                // sleep for 1 second
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void produce() throws InterruptedException {
        int value = 0;
        while (true) {
            synchronized (this) {
                while (parkingLot.size() >= capacity) {
                    // wait for the consumer
                    wait();
                }

                parkingLot.add(new Car(numberQuadrants));
                System.out.println("Produced " + value);

                // notify the consumer
                notify();
                Thread.sleep(1000);
            }
        }
    }

    class Consumer extends Thread {

        // variable to store the current car thats being moved till its beyond the parking lot
        private Car currentCar;
        private boolean isCarMoving = false;

        public void run() {
            while (true) {
                if (parkingLot.size() > 0) {

                    // if no car is moving, get the first car from the parking lot
                    if (!isCarMoving) {

                        // call consume method to check buffer
                        try {
                            currentCar = consume();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }

                    } else {
                        // if car is moving, move it till its beyond the parking lot (last quadrant)
                        currentCar.move();
                        System.out.println("Car is moving to quadrant " + currentCar.getStreetQuadrant());

                        // if car is at last quadrant, remove it from parking lot
                        if (currentCar.getStreetQuadrant() == numberQuadrants) {
                            // call removeCar method to remove car from parking lot
                            removeCar(currentCar);
                            isCarMoving = false;
                        }
                    }

                    // sleep for 1 second
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    public Car consume() throws InterruptedException {
        while (true) {
            synchronized (this) {
                while (parkingLot.size() == 0){
                    // wait for the producer
                    wait();
                }

                Car car = parkingLot.poll();

                // notify the producer
                notify();

                return car;
            }
        }
    }

    // ------------------ Parking Lot ------------------

    public void start() {

        Producer producer = new Producer();
        Consumer consumer = new Consumer();

        producer.start();
        consumer.start();
    }

    private void park(Car car) {

        // TODO ADD EXCEPTION HANDLING FOR IF ABOVE THE CAPACITY

        parkingLot.add(car);
        parkingLotList.add(car);
        
        currentNumberOfCars++;
    }

    private void removeCar(Car car) {
        parkingLot.remove(car);
        parkingLotList.remove(car);
        currentNumberOfCars--;
    }

    // --------------------------------------------------

    public void addCar(Car car) {
        parkingLot.add(car);
        parkingLotList.add(car);
        currentNumberOfCars++;
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
}