package Model;

import javax.swing.*;
import java.awt.*;

public class DeleteFrame extends JDialog {
    private JPanel panel1;
    private JRadioButton userSFullNameRadioButton;
    private JRadioButton trainerSFullNameRadioButton;
    private JRadioButton dataAndTimeRadioButton;
    private JButton deleteButton;
    private JTextField textField1;

    DeleteFrame() {
        setContentPane(panel1);
        panel1.setPreferredSize(new Dimension(600, 150));
        setModal(true);

        deleteButton.addActionListener(e -> {
            String str = textField1.getText();
            if (str.equals(""))
                JOptionPane.showMessageDialog(null, "Field is empty");
            if (userSFullNameRadioButton.isSelected()) {
                StringBuilder temp=new StringBuilder();
                for (sportComplexUserClass u : GFrame.cont) {
                    if (str.equals(u.userFullName)) {
                        temp.append(u).append("\n");
                        GFrame.cont.remove(u);
                    }
                }
                JOptionPane.showMessageDialog(null, "Item has been deleted");
            } else if (trainerSFullNameRadioButton.isSelected()) {
                StringBuilder temp=new StringBuilder();
                for (sportComplexUserClass u : GFrame.cont) {
                    if (!str.equals(u.trainerFullName)) {
                        temp.append(u).append("\n");
                        GFrame.cont.remove(u);
                    }
                }
                JOptionPane.showMessageDialog(null, "Item has been deleted");
            } else if (dataAndTimeRadioButton.isSelected()) {
                StringBuilder temp=new StringBuilder();
                for (sportComplexUserClass u : GFrame.cont) {
                    if (!str.equals(u.dateAngTimeOfBeginning)) {
                        temp.append(u).append("\n");
                        GFrame.cont.remove(u);
                    }
                }
                JOptionPane.showMessageDialog(null, "Item has been deleted");}
            else
                JOptionPane.showMessageDialog(null, "No 'delete-by-key' parameters have been chosen");
        });
    }
}