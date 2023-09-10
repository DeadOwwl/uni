package Model;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.util.*;

public class ItemFrame extends JPanel {
    String name;
    String[] labels;
    Object[] values;
    int selection;
    int presentation;

    public static final int LIST = 1;
    public static final int COMBOBOX = 2;
    public static final int RADIOBUTTONS = 3;

    JList<String> list;
    JComboBox<String> combobox;
    JRadioButton[] radiobuttons;

    ArrayList<ItemFrame.Listener> listeners = new ArrayList<>();

    public ItemFrame(String name, String[] labels, Object[] values, int defaultSelection, int presentation)
    {
        this.name = name;
        this.labels = labels;
        this.values = values;
        this.selection = defaultSelection;
        this.presentation = presentation;

        if (values == null) this.values = labels;

        switch(presentation) {
            case LIST: initList(); break;
            case COMBOBOX: initComboBox(); break;
            case RADIOBUTTONS: initRadioButtons(); break;
        }
    }

    void initList() {
        list = new JList<>(labels);
        list.setSelectedIndex(selection);

        list.addListSelectionListener(e -> ItemFrame.this.select(list.getSelectedIndex()));

        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        this.add(new JLabel(name));
        this.add(new JScrollPane(list));
    }

    void initComboBox() {
        combobox = new JComboBox<>(labels);
        combobox.setSelectedIndex(selection);

        combobox.addItemListener(e -> ItemFrame.this.select(combobox.getSelectedIndex()));

        this.setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
        this.add(new JLabel(name));
        this.add(combobox);
    }

    void initRadioButtons() {
        radiobuttons = new JRadioButton[labels.length];
        ButtonGroup radioButtonGroup = new ButtonGroup();
        ChangeListener listener = e -> {
            JRadioButton b = (JRadioButton)e.getSource();
            if (b.isSelected()) {
                for(int i = 0; i < radiobuttons.length; i++) {
                    if (radiobuttons[i] == b) {
                        ItemFrame.this.select(i);
                        return;
                    }
                }
            }
        };

        this.setBorder(new TitledBorder(new EtchedBorder(), name));
        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

        for(int i = 0; i < labels.length; i++) {
            radiobuttons[i] = new JRadioButton(labels[i]);
            if (i == selection) radiobuttons[i].setSelected(true);
            radiobuttons[i].addChangeListener(listener);
            radioButtonGroup.add(radiobuttons[i]);
            this.add(radiobuttons[i]);
        }
    }

    public String getName() { return name; }

    public Object getSelectedValue() { return values[selection]; }

    protected void select(int selection) {
        this.selection = selection;
        if (!listeners.isEmpty()) {
            ItemFrame.Event e = new ItemFrame.Event(this, selection, values[selection]);
            for (Listener l : listeners)
                l.itemChosen(e);
        }
    }

    public void addItemChooserListener(ItemFrame.Listener l) {
        listeners.add(l);
    }

    public static class Event extends java.util.EventObject {
        int selectedIndex;
        Object selectedValue;
        public Event(ItemFrame source, int selectedIndex, Object selectedValue) {
            super(source);
            this.selectedIndex = selectedIndex;
            this.selectedValue = selectedValue;
        }

        public ItemFrame getItemChooser() { return (ItemFrame)getSource();}
        public int getSelectedIndex() { return selectedIndex; }
        public Object getSelectedValue() { return selectedValue; }
    }

    public interface Listener extends java.util.EventListener {
        void itemChosen(ItemFrame.Event e);
    }

    public static class Demo {
        public static void main(String[] args) {
            final JFrame frame = new JFrame("ItemChooser Demo");
            frame.addWindowListener(new WindowAdapter() {
                public void windowClosing(WindowEvent e) {System.exit(0);}
            });

            final JLabel msgline = new JLabel(" ");

            JPanel chooserPanel = new JPanel();
            final ItemFrame c1 = new ItemFrame("Choice #1", args, null, 0,
                    ItemFrame.LIST);
            final ItemFrame c2 = new ItemFrame("Choice #2", args, null, 0,
                    ItemFrame.COMBOBOX);
            final ItemFrame c3 = new ItemFrame("Choice #3", args, null, 0,
                    ItemFrame.RADIOBUTTONS);

            ItemFrame.Listener l = e -> msgline.setText(e.getItemChooser().getName() + ": " +
                    e.getSelectedIndex() + ": " +
                    e.getSelectedValue());
            c1.addItemChooserListener(l);
            c2.addItemChooserListener(l);
            c3.addItemChooserListener(l);

            JButton report = new JButton("Report");
            report.addActionListener(e -> {
                String msg = "<html><i>" +
                        c1.getName() + ": " + c1.getSelectedValue() + "<br>"+
                        c2.getName() + ": " + c2.getSelectedValue() + "<br>"+
                        c3.getName() + ": " + c3.getSelectedValue() + "</i>";
                JOptionPane.showMessageDialog(frame, msg);
            });

            chooserPanel.add(c1);
            chooserPanel.add(c2);
            chooserPanel.add(c3);
            chooserPanel.add(report);

            Container contentPane = frame.getContentPane();
            contentPane.add(chooserPanel, BorderLayout.CENTER);
            contentPane.add(msgline, BorderLayout.SOUTH);

            frame.pack();
            frame.setVisible(true);
        }
    }
}
