import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class Car {
    private int carId;

    private int streetQuadrant;
    private int goalQuadrant;

    private boolean usedByProducer;

    private boolean isMoving = false;

    public Car(int numberOfQudrants, Queue<Car> carsInParkingLot) {
        this.carId = createRandomId();
        this.streetQuadrant = 0;
        this.usedByProducer = true;
        try {
            this.goalQuadrant = createGoalQuadrant(numberOfQudrants, carsInParkingLot);
        } catch (IllegalStateException e) {
            System.out.println("No available quadrants to create a goal. Setting to 0.");
            this.goalQuadrant = 0;
        }

        System.out.println("Car " + carId + " created with goal quadrant " + goalQuadrant + " and street quadrant " + streetQuadrant);
    }

    public int getCarId() {
        return carId;
    }

    public void setCarId(int carId) {
        this.carId = carId;
    }

    public void move() {
        streetQuadrant++;
    }

    public int getStreetQuadrant() {
        return streetQuadrant;
    }

    public boolean isUsedByProducer() {
        return usedByProducer;
    }

    public void setUsedByProducer(boolean usedByProducer) {
        this.usedByProducer = usedByProducer;
    }

    public void start() {
        isMoving = true;
    }

    public void stop() {
        isMoving = false;
    }

    public boolean hasReachedGoal() {
        return streetQuadrant >= goalQuadrant;
    }
    
    public boolean getIsMoving() {
        return isMoving;
    }

    public int getGoalQuadrant() {
        return goalQuadrant;
    }

    public int createGoalQuadrant(int numberQuadrants, Queue<Car> cars) {
        // create a list of numbers from 1 to numberQuadrants
        List<Integer> list = new ArrayList<>();
        for (int i = 1; i < numberQuadrants; i++) {
            list.add(i);
        }
    
        // loop through Queue. The goal of each car (number) gets taken out of the set.
        for (Car car : cars) {
            list.remove(Integer.valueOf(car.getGoalQuadrant()));
        }
    
        // check if the list is empty
        if (list.isEmpty()) {
            throw new IllegalStateException("No available quadrants.");
        }
    
        // choose one of the remaining numbers randomly
        return list.get((int) (Math.random() * list.size()));
    }

    public void setStreetQuadrant(int streetQuadrant) {
        this.streetQuadrant = streetQuadrant;
    }

    private int createRandomId() {
        return (int) (Math.random() * 100);
    }

}