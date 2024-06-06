import java.util.List;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import java.awt.Panel;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.awt.Button;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.TextField;
import java.awt.Label;
import java.io.File;
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Container;

public class AwtGUI extends Main {

    // Declaring the components of the GUI
    private Frame mainFrame;
    private Label headerLabel;

    private static Panel parkingLotGUI;

    private static Panel pufferNumberLot;

    private Panel statusPanel;
    private static Label numberCarsLabel;
    private static Label numberPCarsLabel;
    private static Label numberCCarsLabel;
    private static Label numberParkedCarsLabel;

    private static Panel graphs;

    private static LineGraph graphNumCar;
    // data for numCar
    private static int[] dataNumCar = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    private static int currentIndexNumCar = 0;

    private static LineGraph graphProduc;
    // data for produc
    private static int[] dataProduc = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    private static int currentIndexProduc = 0;


    private static LineGraph graphConsum;
    // data for consum
    private static int[] dataConsum = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    private static int currentIndexConsum = 0;
    

    private Panel controlPanel;

    // images
    private static ImageIcon carImage;
    private static ImageIcon statusC;
    private static ImageIcon statusP;

    // boolean values

    private static boolean parkingLotIsOpen = false;

    public AwtGUI() {
        prepareGUI();
    }

    public static void load(int numberQuadrants){

        // loading images
        System.out.println("Loading images...");
        carImage = new ImageIcon("src" + File.separator + "fxFrontend" + File.separator + "car.png");
        carImage.setImage(carImage.getImage().getScaledInstance(25, 25, Image.SCALE_DEFAULT));
        statusC = new ImageIcon("src" + File.separator + "awtFrontend" + File.separator + "statusC.png");
        statusC.setImage(statusC.getImage().getScaledInstance(25, 25, Image.SCALE_DEFAULT));
        statusP = new ImageIcon("src" + File.separator + "awtFrontend" + File.separator + "statusP.png");
        statusP.setImage(statusP.getImage().getScaledInstance(25, 25, Image.SCALE_DEFAULT));    
    

        // system out if the images are null
        if (carImage == null || statusC == null || statusP == null) {
            System.out.println("Images are null.");
        } else {
            System.out.println("Images are not null. Images loaded.");
        }

        AwtGUI main = new AwtGUI();
            
        main.showParkingLot();

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
        mainFrame = new Frame("Multi-Threaded Valet-Parking");
        mainFrame.setSize(1000, 800);
        mainFrame.setLayout(new GridLayout(7, 1));

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

        // Creating the status Panel and setting its alignment and size
        statusPanel = new Panel();
        statusPanel.setLayout(new FlowLayout());
        statusPanel.setSize(1000, 20);

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
        super.setNumberOfProducers(3);
        producersText.setText("3");
        // if text is not a number, set the text to 0, else parse the text to an int and give it to the numberOfProducers if change has happened
        producersText.addTextListener(
            e -> {
                if (!producersText.getText().matches("[0-9]+")) {
                    producersText.setText("0");
                    graphProduc.setInterval(0);
                } else {
                    // super numberOfProducers
                    super.setNumberOfProducers(Integer.parseInt(producersText.getText()));
                    // set interval of producer graph to the number of producers
                    graphProduc.setInterval(Integer.parseInt(producersText.getText()));
                }
            }
        );
        controlPanel.add(producersText);

        // input box for number of consumers
        Label consumersLabel = new Label("INT: Consumers: ");
        controlPanel.add(consumersLabel);
        final TextField consumersText = new TextField(5); 
        super.setNumberOfConsumers(2);
        consumersText.setText("2");
        // if text is not a number, set the text to 0, else parse the text to an int and give it to the numberOfProducers if change has happened
        consumersText.addTextListener(
            e -> {
                if (!consumersText.getText().matches("[0-9]+")) {
                    consumersText.setText("0");
                    // set interval of consumer graph to 0
                    graphConsum.setInterval(0);
                } else {
                    // super numberOfConsumers
                    super.setNumberOfConsumers(Integer.parseInt(consumersText.getText()));
                    // set interval of consumer graph to the number of consumers
                    graphConsum.setInterval(Integer.parseInt(consumersText.getText()));
                }
            }
        );
        controlPanel.add(consumersText);
        
        // input box for capacity
        Label capacityLabel = new Label("INT < 10: Capacity");
        controlPanel.add(capacityLabel);
        final TextField capacityText = new TextField(5);
        capacity = 7;
        capacityText.setText("7");
        capacityText.addTextListener(
            e -> {
                if (!capacityText.getText().matches("[0-9]+")) {
                    capacityText.setText("0");
                    capacity = 0;
                    graphNumCar.setInterval(0);
                } else {
                    capacity = Integer.parseInt(capacityText.getText());
                    graphNumCar.setInterval(capacity+1);
                }
            }
        );
        controlPanel.add(capacityText);
                
        // button for starting the parking lot 
        Button startButton = new Button("START");
        startButton.addActionListener(
            new ActionListener() {

                public void actionPerformed(ActionEvent e) {

                    // set text of the header label
                    headerLabel.setText("Parking Lot Simulation is running...");

                    // turn puffer visible
                    pufferNumberLot.setVisible(true);

                    // -------- create parkingLot when the START button of the GUI is pressed with the numberOf... that is in the fields...

                    // set false in case a paint or update thread was to (unlikely) update the GUI while not fully initalised
                    parkingLotIsOpen = false;

                    // create the parking lot through super createParkingLot() method
                    createParkingLot();

                    // start the parking lot. Starts the produce and consume threads of the parking lot.

                    // using supered method startParkingLot() 
                    startParkingLot();

                    parkingLotIsOpen = true;
                }
            }
        );
        controlPanel.add(startButton);
        
        // creating parkingLOTGUI
        parkingLotGUI = new Panel();
        parkingLotGUI.setLayout(new GridLayout(1, super.getNumberQuadrants()));
        parkingLotGUI.setSize(1000, 200);

        // creating pufferNumberLot
        pufferNumberLot = new Panel();
        pufferNumberLot.setLayout(new GridLayout(1, super.getNumberQuadrants()));
        pufferNumberLot.setSize(1000, 200);
        pufferNumberLot.setVisible(false);

        // status Panel contains all the information about the parking lot: number of cars, cars with producers, cars with consumers, cars parked
        numberCCarsLabel = new Label("Cars: ");
        numberPCarsLabel = new Label("Cars with Producers: ");
        numberParkedCarsLabel = new Label("Cars Parked: ");
        numberCarsLabel = new Label("Cars with Consumers: ");
        statusPanel.add(numberCCarsLabel);
        statusPanel.add(numberPCarsLabel);
        statusPanel.add(numberCarsLabel);
        statusPanel.add(numberParkedCarsLabel);

        // Panel with 3 LineGraphs (which extend Frame and are added to the Panel)
        // 1. number of cars in the parking lot
        // 2. number of cars with producers
        // 3. number of cars with consumers

        // creating the graphs panel
        graphs = new Panel();
        graphs.setLayout(new GridLayout(1, 3, 30, 30));

        // three lineGraphs
        graphNumCar = new LineGraph();
        graphProduc = new LineGraph();
        graphConsum = new LineGraph();

        // adding the images to the Panel
        graphs.add(graphNumCar);
        graphs.add(graphProduc);
        graphs.add(graphConsum);

        // setting visibility to true
        headerLabel.setVisible(true);
        statusPanel.setVisible(true);
        controlPanel.setVisible(true);
        parkingLotGUI.setVisible(true);
        graphs.setVisible(true);

        // Adding the header label, control panel, and status label to the main frame
        mainFrame.add(headerLabel);
        mainFrame.add(parkingLotGUI);
        mainFrame.add(pufferNumberLot);
        mainFrame.add(controlPanel);
        mainFrame.add(statusPanel);
        mainFrame.add(graphs);

        // Making the main frame visible
        mainFrame.setVisible(true);
    }

    private void showParkingLot() {
        // Set the text of the header label
        headerLabel.setText("Waiting for the start of the Parking Lot Simulation...");

        // Create the buttons and add action listeners to them
        Button exitButton = new Button("EXIT");

        exitButton.addActionListener(
            new ActionListener() {

                public void actionPerformed(ActionEvent e) {

                    // set header to "closing the simulation..."
                    headerLabel.setText("Closing the Parking Lot Simulation...");

                    // wait for 1 seconds
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException ex) {
                        ex.printStackTrace();
                    }

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

        List<Car> parkingLotList = getParkingLot().getParkingLotList();

        // count and set the number of: cars, cars with producers, cars with consumers, parked cars
        int numberOfCarsForGUI = parkingLotList.size();
        int numberOfCarsWithProducers = 0;
        int numberOfCarsWithConsumers = 0;
        int numberOfParkedCars = 0;

        for (int i = 0; i < parkingLotList.size(); i++) {
            Car car = parkingLotList.get(i);
            if (car.isUsedByProducer()) {
                numberOfCarsWithProducers++;
            }
            if (!car.isUsedByProducer()&& car.getIsMoving()) {
                numberOfCarsWithConsumers++;
            }
            if (car.hasReachedGoal()&& !car.getIsMoving()) {
                numberOfParkedCars++;
            }
        }

        // set the labels of the status panel to the values of the variables
        numberCCarsLabel.setText("Cars: " + numberOfCarsForGUI);
        numberPCarsLabel.setText("Cars with Producers: " + numberOfCarsWithProducers);
        numberCarsLabel.setText("Cars with Consumers: " + numberOfCarsWithConsumers);
        numberParkedCarsLabel.setText("Cars Parked: " + numberOfParkedCars);
        
        // iterating over quadrants, setting all labels to invisible, and visible if true

        for (int i = 0; i < getNumberQuadrants(); i++) {

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

        // graphs

        // if currentIndex at the end of the data size, setting it to 0
        if (currentIndexNumCar == dataNumCar.length - 1) {
            currentIndexNumCar = 0;
        } else {
            currentIndexNumCar++;
        }
        graphNumCar.setLiveViewIndex(currentIndexNumCar);

        if (currentIndexProduc == dataProduc.length - 1) {
            currentIndexProduc = 0;
        } else {
            currentIndexProduc++;
        }
        graphProduc.setLiveViewIndex(currentIndexProduc);

        if (currentIndexConsum == dataConsum.length - 1) {
            currentIndexConsum = 0;
        } else {
            currentIndexConsum++;
        }
        graphConsum.setLiveViewIndex(currentIndexConsum);

        // updating the data by using the currentIndex and the found variables
        dataNumCar[currentIndexNumCar] = numberOfCarsForGUI;
        dataProduc[currentIndexProduc] = numberOfCarsWithProducers;
        dataConsum[currentIndexConsum] = numberOfCarsWithConsumers;

        // setting that data to be the current data of the graphs
        graphNumCar.setData(dataNumCar);
        graphProduc.setData(dataProduc);
        graphConsum.setData(dataConsum);

        graphs.setVisible(parkingLotIsOpen);

        parkingLotGUI.setVisible(true);
        parkingLotGUI.revalidate();
        parkingLotGUI.repaint();

    }

    public class LineGraph extends Canvas {

        private int[] data = {};
        private int interval = 10; // Default interval is 10

        private int liveViewIndex = 0;
    
        public LineGraph() {
        }
    
        public void setData(int[] data) {
            this.data = data;
            revalidate();
            repaint();
        }
    
        // Method to set the interval
        public void setInterval(int interval) {
            this.interval = interval;
        }

        public void setLiveViewIndex(int index) {
            this.liveViewIndex = index;
        }
    
        @Override
        public Dimension getPreferredSize() {
            // Return a size based on the parent container's size
            Container parent = getParent();
            if (parent != null) {
                return parent.getSize();
            } else {
                return super.getPreferredSize();
            }
        }
    
        public void paint(Graphics g) {
            int h = getHeight();
            int w = getWidth();
            for (int i = 0; i < data.length - 1; i++) {
                int x1 = i * w / (data.length - 1);
                int x2 = (i + 1) * w / (data.length - 1);
                int y1 = h - data[i] * h / interval; 
                int y2 = h - data[i + 1] * h / interval; 

                if(i == liveViewIndex) {
                    g.setColor(java.awt.Color.RED);
                } else {
                    g.setColor(java.awt.Color.BLACK);
                }
                g.drawLine(x1, y1, x2, y2);
            }
        }
    }
    
}