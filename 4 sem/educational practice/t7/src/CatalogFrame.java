
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class CatalogFrame extends JFrame {

    private static final long serialVersionUID = 1L;
    public static JTable infoTransportPanel;
    public static JTable infoDriverPanel;
    public static JTable infoRoadsPanel;
    public static CatalogTableTransportModel tableTransportModel = null;
    public static CatalogTableDriverModel tableDriverModel = null;
    public static CatalogTableRoutesModel tableRoadsModel = null;

    public CatalogFrame() throws HeadlessException, IOException {
        setTitle("Catalog");
        System.setProperty("DERBY_HOME", "C:\\Users\\aowl2\\OneDrive\\Рабочий стол\\bsu\\4 s\\ep\\t7\\src" );

        tableTransportModel = new CatalogTableTransportModel();
        infoTransportPanel = new JTable(tableTransportModel);
        tableTransportModel = new CatalogTableTransportModel(CatalogDB.ReadMonumentDB());

        infoTransportPanel.setModel(tableTransportModel);
        infoTransportPanel.setAutoCreateRowSorter(true);
        infoTransportPanel.setShowGrid(true);
        tableDriverModel = new CatalogTableDriverModel(CatalogDB.ReadBuyerDB());
        infoDriverPanel = new JTable(tableDriverModel);
        infoDriverPanel.setModel(tableDriverModel);
        infoDriverPanel.setAutoCreateRowSorter(true);
        infoDriverPanel.setShowGrid(true);

        tableRoadsModel = new CatalogTableRoutesModel(CatalogDB.ReadShoppingBasketDB());
        infoRoadsPanel = new JTable(tableRoadsModel);
        infoRoadsPanel.setModel(tableRoadsModel);
        infoRoadsPanel.setAutoCreateRowSorter(true);
        infoRoadsPanel.setShowGrid(true);


        Container container = new Container();
        container.setLayout(new BoxLayout(container, BoxLayout.Y_AXIS));
        Container container3 = new Container() ;


        container3.setLayout(new BoxLayout(container3, BoxLayout.Y_AXIS));
        container3.add(new JLabel("\n"));
        container3.add(new JLabel("Roads Table"));

        container3.add(new JScrollPane(infoRoadsPanel));
        container.add(container3);



        Container container1 = new Container() ;
        container1.setLayout(new BoxLayout(container1, BoxLayout.Y_AXIS));
        container1.add(new JLabel("\n"));
        container1.add(new JLabel("Drivers Table"));
        container1.add(new JScrollPane(infoDriverPanel));
        container.add(container1);


        Container container2 = new Container() ;
        container2.setLayout(new BoxLayout(container2, BoxLayout.Y_AXIS));
        container2.add(new JLabel("\n"));
        container2.add(new JLabel("Transport Table"));
        container2.add(new JScrollPane(infoTransportPanel));
        container2.add(new JLabel("\n"));
        container.add(container2);

        Container container4 = new Container();
        container4.setLayout(new BoxLayout(container4, BoxLayout.X_AXIS));

        Button addPlant = new Button("Add Transport");
        addPlant.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openAddPlantDialog();
            }
        });
        Button addBuyer = new Button("Add Driver");
        addBuyer.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openAddBuyerDialog();
            }
        });
        Button addShoppingBasket = new Button("Add Road");
        addShoppingBasket.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openAddShoppingBasketDialog();
            }
        });

        Button createButton = new Button("Create DB");
        createButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    CatalogDBCreate.createDB();
                    getSuccessfullyMsg("DB created successfully!");
                }catch (Exception exception){
                    System.out.println(exception);
                    getError(exception.toString());
                    createButton.setEnabled(false);
                }

                createButton.setEnabled(false);

            }
        });
        Button fillButton = new Button("Fill DB");
        fillButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                try {
                    CatalogDBFill.FillDB();
                    tableTransportModel = new CatalogTableTransportModel(CatalogDB.ReadMonumentDB());
                    infoTransportPanel.setModel(tableTransportModel);
                    tableDriverModel = new CatalogTableDriverModel(CatalogDB.ReadBuyerDB());
                    infoDriverPanel.setModel(tableDriverModel);
                    tableRoadsModel = new CatalogTableRoutesModel(
                            CatalogDB.ReadShoppingBasketDB());
                    infoRoadsPanel.setModel(tableRoadsModel);
                    //getSuccessfullyMsg("DB filled successfully!");
                } catch (Exception exception) {
                    System.out.println(exception);
                    getError(exception.toString());
                }
            }
        });
        container4.add(createButton);
        container4.add(fillButton);
        container4.add(addPlant);
        container4.add(addBuyer);
        container4.add(addShoppingBasket);


        container.add(container4);
        add(container);
        setSize(680,650);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
        setLocationRelativeTo(null);
    }
    private void openAddPlantDialog() {
        AddTransport addTransport = new AddTransport(this);
        addTransport.setVisible(true);
    }

    private void openAddBuyerDialog() {
        AddDriver addDriver = new AddDriver(this);
        addDriver.setVisible(true);
    }

    private void openAddShoppingBasketDialog() {
        AddRoute addRoute = new AddRoute(this);
        addRoute.setVisible(true);
    }

    private void getError(String error){
        JOptionPane.showMessageDialog(this, error, "Error", JOptionPane.ERROR_MESSAGE);
    }

    private void getSuccessfullyMsg(String msg){
        JOptionPane.showMessageDialog(this, msg, "Message", JOptionPane.INFORMATION_MESSAGE);
    }
}