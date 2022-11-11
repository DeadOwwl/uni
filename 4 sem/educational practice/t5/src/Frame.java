import javax.swing.*;
import javax.swing.tree.TreePath;
import java.awt.*;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Scanner;

public class Frame extends JFrame {

    private static final long serialVersionUID = 1L;
    JTable infoPanel;
    JTree notebooksTree = new JTree();
    static TModel tableModel = null;
    static TrModel treeModel = null;

    public Frame() throws HeadlessException {

        JButton addButton = new JButton("Add");
        addButton.addActionListener(e -> openAddDialog());

        JButton removeButton = new JButton("Delete");
        removeButton.addActionListener(e -> removeItem());

        JButton loadButton = new JButton("Load");

        JButton saveButton = new JButton("Save");

        saveButton.addActionListener(e ->{
            try {
                JFileChooser jFileChooser = new JFileChooser();
                jFileChooser.showSaveDialog(this);
                if (jFileChooser.getSelectedFile() != null){
                    FileWriter out = new FileWriter(jFileChooser.getSelectedFile());
                    ArrayList<Node> nodes = treeModel.getRoot().getAllLeaves();
                    for (Node estate : nodes){
                        out.write(estate.getNaming()+"\n"
                                + estate.getYear() + "\n"
                                + estate.getSculptors() + "\n"
                                + estate.getAddress() + "\n");
                    }
                    out.close();
                }
            }catch (Exception ignore){ }
        });

        loadButton.addActionListener(e ->{
            try {
                JFileChooser jFileChooser = new JFileChooser();
                jFileChooser.showOpenDialog(this);
                if (jFileChooser.getSelectedFile() != null) {
                    notebooksTree.removeAll();
                    //tableModel = null;
                    //treeModel = new TrModel(new TrNode("Historical Monuments"));
                    Scanner scanner = new Scanner(jFileChooser.getSelectedFile());
                    while (scanner.hasNextLine()){
                        Node estate = new Node(
                                scanner.nextLine(),
                                scanner.nextLine(),
                                scanner.nextLine(),
                                scanner.nextLine()
                        );
                        addNewItem(estate);
                    }
                }
            }catch (Exception ignore){}
        });

        tableModel = new TModel();
        infoPanel = new JTable(tableModel);
        treeModel = new TrModel(new TrNode("Historical Monuments"));
        notebooksTree = new JTree(treeModel);
        notebooksTree.addTreeSelectionListener(e -> {
            TrNode node = (TrNode) notebooksTree.getLastSelectedPathComponent();
            if (node == null) {
                return;
            }
            ArrayList<Node> array = node.getAllLeaves();
            tableModel = new TModel(array);
            infoPanel.setModel(tableModel);
        });
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, true, new JScrollPane(notebooksTree), new JScrollPane(infoPanel));
        splitPane.setDividerLocation(300);

        getContentPane().add(splitPane);
        getContentPane().add("North", addButton);
        getContentPane().add("South", removeButton);
        getContentPane().add("East", loadButton);
        getContentPane().add("West", saveButton);
        setBounds(100, 100, 600, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
    }

    private void openAddDialog() {
        Add addForm = new Add(this);
        addForm.setVisible(true);
    }

    void addNewItem(Node addResult) {
        TrNode where, insert, root = treeModel.getRoot();
        if (addResult != null) {
            try {
                insert = new TrNode(addResult.getNaming(), addResult);
                if ((where = findNode(root, String.valueOf(addResult.getYear()))) != null) {
                    treeModel.insertNodeInto(insert, where, where.getChildCount(), false);
                }
                else {
                    treeModel.insertNodeInto(new TrNode(String.valueOf(addResult.getYear())),
                            root,
                            root.getChildCount(),
                            false);
                    where = findNode(root, String.valueOf(addResult.getYear()));

                    if (where != null) {
                        treeModel.insertNodeInto(insert, where, where.getChildCount(), false);
                    }
                }
            } catch (Exception ignore) { }
        }
    }


    public void removeItem() {
        TreePath currentSelection = notebooksTree.getSelectionPath();
        if (currentSelection != null) {
            TrNode currentNode = (TrNode) (currentSelection.getLastPathComponent());
            TrNode parent = (TrNode) (currentNode.getParent());
            if (parent != null) {
                treeModel.removeNodeFromParent(currentNode);
                parent.deleteNode(currentNode);
                ArrayList<Node> array = parent.getAllLeaves();
                tableModel = new TModel(array);
                infoPanel.setModel(tableModel);
            }
        }
    }

    private static TrNode findNode(TrNode root, String s) {
        Enumeration e = root.depthFirstEnumeration();
        while (e.hasMoreElements()) {
            TrNode node = (TrNode) e.nextElement();
            if (node.toString().equalsIgnoreCase(s)) {
                return node;
            }
        }
        return null;
    }

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException | UnsupportedLookAndFeelException | IllegalAccessException e) {
            System.err.println(e.getMessage());
        }
        Frame mainClass = new Frame();
        mainClass.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        mainClass.setVisible(true);
    }
}