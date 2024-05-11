package src;

// parking lot list reading
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JLabel;

import java.awt.Label;
import java.awt.Panel;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.Button;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.TextField;

public class ProdConProb {

    // Declaring the components of the GUI
    private Frame mainFrame;
    private Label headerLabel;

    private static Panel parkingLotGUI;

    private static Panel pufferNumberLot;

    private Label statusLabel;
    private Panel controlPanel;

    // declaring the parking lot
    private static ParkingLot parkingLot;
    private static int numberQuadrants;

    // images
    private static ImageIcon carImage;
    private static ImageIcon statusC;
    private static ImageIcon statusP;

    private static int numberOfConsumers;
    private static int numberOfProducers;

    private static int capacity;

    // boolean values

    private static boolean parkingLotIsOpen = false;

    public ProdConProb() {
        prepareGUI();
    }

    public static void main(String[] args) {

        // parking lot size (influences layout of the GUI)
        numberQuadrants = 10;
        capacity = numberQuadrants/2;

        // loading images
        System.out.println("Loading images...");
        carImage = new ImageIcon("Aufgabe2-Producer-Consumer-java\\src\\carImage.png");
        carImage.setImage(carImage.getImage().getScaledInstance(25, 25, Image.SCALE_DEFAULT));
        statusC = new ImageIcon("Aufgabe2-Producer-Consumer-java\\src\\statusC.png");
        statusC.setImage(statusC.getImage().getScaledInstance(25, 25, Image.SCALE_DEFAULT));
        statusP = new ImageIcon("Aufgabe2-Producer-Consumer-java\\src\\statusP.png");
        statusP.setImage(statusP.getImage().getScaledInstance(25, 25, Image.SCALE_DEFAULT));

        // system out if the images are null
        if (carImage == null || statusC == null || statusP == null) {
            System.out.println("Images are null.");
        } else {
            System.out.println("Images are not null. Images loaded.");
        }

        ProdConProb main = new ProdConProb();
        
        main.showParkingLot();

        System.out.println("Hitting of GUI with Initialisation...");

        // for the number of quadrants in the parking lot, draw a quadrant with its number 

        for (int i = 0; i < numberQuadrants; i++) {

            // create a normal Panel with a Label of a number for pufferNumberLot
            Label number = new Label(Integer.toString(i+1));
            pufferNumberLot.add(number);

            // creating quadrant panel for parkinglotGUI

            QuadrantPanel quadrant = new QuadrantPanel(new JLabel(carImage), 
                                                        new JLabel(statusC), 
                                                        new JLabel(statusP));

            quadrant.setLayout(new BoxLayout(quadrant, BoxLayout.Y_AXIS));

            quadrant.carImageLabel.setVisible(false);
            quadrant.statusCLabel.setVisible(false);
            quadrant.statusPLabel.setVisible(false);

            parkingLotGUI.add(quadrant);
        }
        
        // update this GUI every 250ms

        System.out.println("Starting GUI main-thread update loop...");

        while(true){

            // if parkinglot has started
            if(parkingLotIsOpen) {
                updateParkingLotGUI();
            }

            try {
                Thread.sleep(50);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

    private void prepareGUI() {
        // Creating main frame with size and layout
        mainFrame = new Frame("Parking Lot Simulation");
        mainFrame.setSize(1000, 400);
        mainFrame.setLayout(new GridLayout(5, 1));

        // Adding a window listener to the main frame to close the application when the close button is clicked
        mainFrame.addWindowListener(
            new WindowAdapter() {

        // Add missing import for WidePanel if necessary

                public void windowClosing(WindowEvent windowEvent) {
                    System.exit(0);
                }
            }
        );
        
        // Creating the header label and setting its alignment
        headerLabel = new Label();
        headerLabel.setAlignment(Label.CENTER);

        // Creating the status label and setting its alignment and size
        statusLabel = new Label();
        statusLabel.setAlignment(Label.CENTER);
        statusLabel.setSize(1000, 50);

        // Creating the control panel and setting its layout
        controlPanel = new Panel();
        controlPanel.setLayout(new FlowLayout());
        controlPanel.setSize(1000, 50);

        // control panel has two input boxes for int values and a START button
        // the START button will create the parking lot with the given values

        // input box for number of producers
        Label producersLabel = new Label("INT: Producers: ");
        controlPanel.add(producersLabel);
        final TextField producersText = new TextField(5);
        // if text is not a number, set the text to 0, else parse the text to an int and give it to the numberOfProducers if change has happened
        producersText.addTextListener(
            e -> {
                if (!producersText.getText().matches("[0-9]+")) {
                    producersText.setText("0");
                } else {
                    numberOfProducers = Integer.parseInt(producersText.getText());
                }
            }
        );
        controlPanel.add(producersText);

        // input box for number of consumers
        Label consumersLabel = new Label("INT: Consumers: ");
        controlPanel.add(consumersLabel);
        final TextField consumersText = new TextField(5);
        // if text is not a number, set the text to 0, else parse the text to an int and give it to the numberOfProducers if change has happened
        consumersText.addTextListener(
            e -> {
                if (!consumersText.getText().matches("[0-9]+")) {
                    consumersText.setText("0");
                } else {
                    numberOfConsumers = Integer.parseInt(consumersText.getText());
                }
            }
        );
        controlPanel.add(consumersText);
                
        // button for starting the parking lot 
        Button startButton = new Button("START");
        startButton.addActionListener(
            new ActionListener() {

                public void actionPerformed(ActionEvent e) {
                    // -------- create parkingLot when the START button of the GUI is pressed with the numberOf... that is in the fields...

                    // set false in case a paint or update thread was to (unlikely) update the GUI while not fully initalised
                    parkingLotIsOpen = false;

                    parkingLot = new ParkingLot(numberQuadrants, capacity, numberOfProducers, numberOfConsumers);

                    // start the parking lot. Starts the produce and consume threads of the parking lot.

                    parkingLot.start();

                    parkingLotIsOpen = true;
                }
            }
        );
        controlPanel.add(startButton);
        
        // creating parkingLOTGUI
        parkingLotGUI = new Panel();
        parkingLotGUI.setLayout(new GridLayout(1, numberQuadrants));
        parkingLotGUI.setSize(1000, 200);

        // creating pufferNumberLot
        pufferNumberLot = new Panel();
        pufferNumberLot.setLayout(new GridLayout(1, numberQuadrants));
        pufferNumberLot.setSize(1000, 100);

        headerLabel.setVisible(true);
        statusLabel.setVisible(true);
        controlPanel.setVisible(true);
        parkingLotGUI.setVisible(true);

        // Adding the header label, control panel, and status label to the main frame
        mainFrame.add(headerLabel);

        mainFrame.add(parkingLotGUI);
        mainFrame.add(pufferNumberLot);
        mainFrame.add(controlPanel);
        mainFrame.add(statusLabel);

        // Making the main frame visible
        mainFrame.setVisible(true);
    }

    private void showParkingLot() {
        // Set the text of the header label
        headerLabel.setText("Parking Lot Simulation Ongoing...");

        // Create the buttons and add action listeners to them
        Button exitButton = new Button("EXIT");

        exitButton.addActionListener(
            new ActionListener() {

                public void actionPerformed(ActionEvent e) {
                    // Close the application when the EXIT button is clicked
                    System.exit(0);
                }
            }
        );

        // Add button to the control panel
        controlPanel.add(exitButton);
        // CANCEL BUTTON NOT ADDED, KEPT AS EXAMPLE FOR STATUS LABEL

        // Set the visibility of the main frame to true
        mainFrame.setVisible(true);
    }

    private static void updateParkingLotGUI() {
        // clone the linked list of the parking lot

        List<Car> parkingLotList = parkingLot.getParkingLotList();

        // iterating over quadrants, setting all labels to invisible, and visible if true

        for (int i = 0; i < numberQuadrants; i++) {

            // get the quadrant panel
            QuadrantPanel quadrant = (QuadrantPanel) parkingLotGUI.getComponent(i);

            // set all labels to invisible
            quadrant.obscuro();

            // numberOfCars in Quadrant at once
            int numberOfCars = 0;

            // iterate over the parking lot list
            for (int j = 0; j < parkingLotList.size(); j++) {

                // get the car object
                Car car = parkingLotList.get(j);

                // check if the car is parked in the current quadrant
                if (car.getStreetQuadrant() == i) {

                    numberOfCars++;
                   
                    quadrant.carImageLabel.setVisible(true);

                    // if car moving, status should be there, then allowing a status be displayed
                    if (car.getIsMoving()) {
                        if (car.isUsedByProducer()) {
                            quadrant.revilioWcar(true);
                        } else {
                            quadrant.revilioWcar(false);
                        }
                    } else {
                        quadrant.revilioOstatus();
                    }
                }
            }

            // if numberofcars is greater than 1, set this number to the quadrant numberOfCars label and make it visible
            if (numberOfCars > 1) {
                quadrant.numberOfCarsLabel.setText(Integer.toString(numberOfCars));
                quadrant.numberOfCarsLabel.setVisible(true);
            }
        };

        parkingLotGUI.setVisible(true);

        parkingLotGUI.revalidate();
        parkingLotGUI.repaint();

    }
}
