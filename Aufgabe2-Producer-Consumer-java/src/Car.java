package src;

public class Car {
    private int carId;

    private int streetQuadrant;
    private int goalQuadrant;

    private boolean usedByProducer;

    private boolean isMoving = false;

    public Car(int numberOfQudrants) {
        this.carId = createRandomId();
        this.streetQuadrant = 0;
        this.usedByProducer = true;
        this.goalQuadrant = createRandomGoalQuadrant(numberOfQudrants);

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

    public int createRandomGoalQuadrant(int numberQuadrants) {
        // above 1 and below numberQuadrants
        return (int) (Math.random() * (numberQuadrants - 1) + 1);
    }

    public void setStreetQuadrant(int streetQuadrant) {
        this.streetQuadrant = streetQuadrant;
    }

    private int createRandomId() {
        return (int) (Math.random() * 100);
    }

}