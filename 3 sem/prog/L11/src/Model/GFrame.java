package Model;

import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.List;

public class GFrame extends JDialog {

    private JPanel panel1;
    public JTextArea textArea1;
    public static List<sportComplexUserClass> cont;

    private final JMenu fileMenu;
    private final JMenuItem quitItem;
    private final JMenuItem addItem;
    private final JMenuItem saveItem;
    private final JMenuItem sortItem;
    private final JMenuItem findItem;
    private final JMenuItem deleteItem;
    private final JMenu viewMenu;
    private final JMenuItem fontItem;
    private final JMenu helpMenu;
    private final JMenuItem aboutItem;
    private final JMenu recordsMenu;

    public GFrame() {
        cont = new ArrayList<>();
        setContentPane(panel1);
        panel1.setPreferredSize(new Dimension(800, 500));
        setModal(true);

        JMenuBar menu = new JMenuBar();

        fileMenu = new JMenu("File");
        recordsMenu = new JMenu("Records");
        quitItem = new JMenuItem("Quit");
        addItem = new JMenuItem("Add");
        saveItem = new JMenuItem("Save");
        sortItem = new JMenuItem("Sort");
        findItem = new JMenuItem("Find");
        JMenuItem openItem = new JMenuItem("Open");
        deleteItem = new JMenuItem("Delete");
        recordsMenu.add(addItem);
        fileMenu.add(openItem);
        fileMenu.add(saveItem);
        fileMenu.add(quitItem);
        recordsMenu.add(sortItem);
        recordsMenu.add(findItem);
        recordsMenu.add(deleteItem);
        viewMenu = new JMenu("View");
        fontItem = new JMenuItem("Font");
        viewMenu.add(fontItem);

        helpMenu = new JMenu("Help");
        aboutItem = new JMenuItem("About");
        helpMenu.add(aboutItem);
        menu.add(fileMenu);
        menu.add(recordsMenu);
        menu.add(viewMenu);
        menu.add(helpMenu);
        setJMenuBar(menu);
        FontFrame fontPanel = new FontFrame(this);
        JMenu temp=createPlafMenu(this);
        viewMenu.add(temp);

        JFileChooser fileChooser=new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
        fileChooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);

        quitItem.addActionListener(e -> dispose());

        aboutItem.addActionListener(e -> JOptionPane.showMessageDialog(null,
                "������� �11 ����������� ���������� Java\n" +
                        "\n" +
                        "������� ����������� ���������� Java, ����������� GUI ��� ������� �8.\n" +
                        "\n" +
                        "���������� � GUI:\n" +
                        "\n" +
                        "- ��� ���������� ���������� �������� ������������� ��������� CUI (Common User Interface). ������� ���� ���������� ����������� ������ ��������� ��������� ������� (� ������� �������/�������):\n" +
                        "File/Quit � ���������� ���������� ����� ������������� ������������\n" +
                        "View/Font � ����� ������ ��� ����������� ����������\n" +
                        "View/ Look and Feel � ����� ����� ���������� (��� � ��������)\n" +
                        "Help/About � ����� ����������� ���� ������� �������� ������� ������ � ���������� � ������������ (��� ��������, ������, ����, ���������, ���)\n" +
                        "(�������) � ������� ����������� ��� ������� ������ �������� ������, ��������, File/Open ��� ������ ����� � �.�.\n" +
                        "-\t���������� ������ ��������� ������������ ������� ���������� ���� (��������� �������� ����, ������� ���������, ���������� � �. �.)\n" +
                        "-\t������������� ����� ����� ����� ��� �������� ������ ���������\n" +
                        "\n" +
                        "��� �����/�������������� ������ ������ �11 ������� ���� ��� ��������� ���� � ���������� ������� �������� ����.\n" +
                        "\n������� 7-8-11 ���:\n12.\t������������ �������������� ����� ��������:���,��� ������,��� �������,��� �������, ���� � ����� ������, ���������� �����, ����� �� ������. ������������� �� ��� �������, ��� �������, ���� � ����� ������." +
                        "\n\n��������� ����� �������, 10 ������, 2 ����, ����, ���.\n2020 ���."
        ));

        addItem.addActionListener(e -> {
            //panel1.setVisible(false);
            AddFrame addPanel = new AddFrame();
            addPanel.pack();
            addPanel.setVisible(true);
            update();
        });

        sortItem.addActionListener(e -> {
            SortFrame sortPanel = new SortFrame();
            sortPanel.pack();
            sortPanel.setVisible(true);
            update();
        });

        findItem.addActionListener(e -> {
            FindFrame findPanel = new FindFrame();
            findPanel.pack();
            findPanel.setVisible(true);
            update();
        });

        deleteItem.addActionListener(e -> {
            DeleteFrame deletePanel = new DeleteFrame();
            deletePanel.pack();
            deletePanel.setVisible(true);
            update();
        });

        fontItem.addActionListener(e -> {
            fontPanel.pack();
            fontPanel.setVisible(true);

            fileMenu.setFont(fontPanel.getSelectedFont());
            openItem.setFont(fontPanel.getSelectedFont());
            viewMenu.setFont(fontPanel.getSelectedFont());
            helpMenu.setFont(fontPanel.getSelectedFont());
            recordsMenu.setFont(fontPanel.getSelectedFont());
            quitItem.setFont(fontPanel.getSelectedFont());
            addItem.setFont(fontPanel.getSelectedFont());
            saveItem.setFont(fontPanel.getSelectedFont());
            sortItem.setFont(fontPanel.getSelectedFont());
            findItem.setFont(fontPanel.getSelectedFont());
            deleteItem.setFont(fontPanel.getSelectedFont());
            fontItem.setFont(fontPanel.getSelectedFont());
            temp.setFont(fontPanel.getSelectedFont());
            aboutItem.setFont(fontPanel.getSelectedFont());
            textArea1.setFont(fontPanel.getSelectedFont());
        });

        saveItem.addActionListener(e -> {
            File file = new File("src//output.txt");
            try {
                FileWriter fw = new FileWriter(file, false);
                StringBuilder temp1 = new StringBuilder();
                for (sportComplexUserClass i : cont) {
                    temp1.append(i).append("\n");
                }
                fw.write(String.valueOf(temp1));
                fw.close();
                JOptionPane.showMessageDialog(null,
                        "The file has been successfully saved in the 'src'-folder");
            } catch (IOException fileNotFoundException) {
                fileNotFoundException.printStackTrace();
            }

        });

        openItem.addActionListener(e -> {
            int ret= fileChooser.showOpenDialog(null);
            File file=fileChooser.getSelectedFile();
            if(ret== JFileChooser.APPROVE_OPTION){
            try {
                Scanner in=new Scanner(file);
                cont.clear();
                while(in.hasNextLine()){
                    StringTokenizer sttok = new StringTokenizer(in.nextLine(), "|");
                    while(sttok.hasMoreElements()){
                        String userFullName=sttok.nextToken();
                        int sectionCode=Integer.parseInt(sttok.nextToken());
                        String occupationType=sttok.nextToken();
                        String trainerFullName=sttok.nextToken();
                        String dateAngTimeOfBeginning=sttok.nextToken();
                        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
                        Date docDate= sdf.parse(dateAngTimeOfBeginning);
                        dateAngTimeOfBeginning = sdf.format(docDate);
                        int numOfMinutes=Integer.parseInt(sttok.nextToken());
                        double ratePerMinute=Double.parseDouble(sttok.nextToken());
                        cont.add(new sportComplexUserClass(userFullName,sectionCode,occupationType,
                                trainerFullName,dateAngTimeOfBeginning,numOfMinutes,ratePerMinute));
                    }
                }
                in.close();
                update();
            } catch (FileNotFoundException | ParseException fileNotFoundException) {
                fileNotFoundException.printStackTrace();
            }}
        });
    }
    public static JMenu createPlafMenu (final GFrame frame){
        JMenu plafmenu = new JMenu("Look and Feel");
        ButtonGroup radiogroup = new ButtonGroup();
        UIManager.LookAndFeelInfo[] plafs =
                UIManager.getInstalledLookAndFeels();
        for (UIManager.LookAndFeelInfo plaf : plafs) {
            String plafName = plaf.getName();
            final String plafClassName = plaf.getClassName();
            JMenuItem item = plafmenu.add(new JRadioButtonMenuItem(plafName));
            item.addActionListener(e -> {
                try {
                    UIManager.setLookAndFeel(plafClassName);
                    SwingUtilities.updateComponentTreeUI(frame);
                    frame.pack();
                } catch (Exception ex) {
                    System.err.println(ex);
                }
            });
            radiogroup.add(item);
        }
        return plafmenu;
    }
    void update() {
        textArea1.setText("");
        for (sportComplexUserClass i : cont)
            textArea1.append(i.toString() + "\n");
    }

}
