package Model;

import javax.swing.*;
import java.awt.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Date;
import java.util.List;

public class FindFrame extends JDialog {
    private JRadioButton RadioButtonByKey;
    private JPanel panel1;
    private JRadioButton RadioButtonMoreKey;
    private JRadioButton RadioButtonLessKey;
    private JRadioButton userSFullNameRadioButton;
    private JRadioButton trainerSFullNameRadioButton;
    private JRadioButton dataAndTimeRadioButton;
    private JButton findButton;
    private JTextField textField1;

    FindFrame() {
        setContentPane(panel1);
        panel1.setPreferredSize(new Dimension(600, 140));
        setModal(true);

        findButton.addActionListener(e -> {
            String str = textField1.getText();
            if (str.equals(""))
                JOptionPane.showMessageDialog(null, "Field is empty");
                if (RadioButtonByKey.isSelected()) {
                    if (userSFullNameRadioButton.isSelected()) {
                        boolean f = false;
                        for (sportComplexUserClass u : GFrame.cont) {
                            if (str.equals(u.userFullName)) {
                                JOptionPane.showMessageDialog(null, u);
                                f = true;
                            }
                        }
                        if (!f)
                            JOptionPane.showMessageDialog(null, "Nu such record in library");
                    } else if (trainerSFullNameRadioButton.isSelected()) {
                        boolean f = false;
                        for (sportComplexUserClass u : GFrame.cont) {
                            if (str.equals(u.trainerFullName)) {
                                JOptionPane.showMessageDialog(null, u);
                                f = true;
                            }
                        }
                        if (!f)
                            JOptionPane.showMessageDialog(null, "Nu such record in library");
                    } else if (dataAndTimeRadioButton.isSelected()) {
                        boolean f = false;
                        for (sportComplexUserClass u : GFrame.cont) {
                            if (str.equals(u.dateAngTimeOfBeginning)) {
                                JOptionPane.showMessageDialog(null, u);
                                f = true;
                            }
                        }
                        if (!f)
                            JOptionPane.showMessageDialog(null, "Nu such record in library");
                    } else JOptionPane.showMessageDialog(null, "No 'find-by-key' parameters have been chosen");
                } else if (RadioButtonMoreKey.isSelected()) {
                    if (userSFullNameRadioButton.isSelected()) {
                        List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                        tempList.sort((o1, o2) -> o2.userFullName.compareTo(o1.userFullName));
                        StringBuffer temp = new StringBuffer();
                        for (sportComplexUserClass u : tempList) {
                            if (u.userFullName.compareTo(str) > 0)
                                temp.append(u).append("\n");
                        }
                        JOptionPane.showMessageDialog(null, temp);
                    } else if (trainerSFullNameRadioButton.isSelected()) {
                        List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                        tempList.sort((o1, o2) -> o2.trainerFullName.compareTo(o1.trainerFullName));
                        StringBuffer temp = new StringBuffer();
                        for (sportComplexUserClass u : tempList) {
                            if (u.trainerFullName.compareTo(str) > 0)
                                temp.append(u).append("\n");
                        }
                        JOptionPane.showMessageDialog(null, temp);
                    } else if (dataAndTimeRadioButton.isSelected()) {
                        List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
                        tempList.sort((o1, o2) -> {
                            Date d1;
                            Date d2;
                            try {
                                d1 = sdf.parse(o1.dateAngTimeOfBeginning);
                                d2 = sdf.parse(o2.dateAngTimeOfBeginning);
                                assert d1 != null;
                                return d2.compareTo(d1);
                            } catch (ParseException ignored) {
                            }
                            return 0;
                        });
                        StringBuilder temp = new StringBuilder();
                        for (sportComplexUserClass u : tempList) {
                            try {
                                if (sdf.parse(u.dateAngTimeOfBeginning).compareTo(sdf.parse(str)) > 0)
                                    temp.append(u).append("\n");
                            } catch (ParseException parseException) {
                                parseException.printStackTrace();
                            }
                        }
                    } else JOptionPane.showMessageDialog(null,
                            "No 'sorted-by' parameters have been chosen");
                } else if (RadioButtonLessKey.isSelected()) {

                    if (userSFullNameRadioButton.isSelected()) {
                        List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                        tempList.sort(Comparator.comparing(o -> o.userFullName));
                        StringBuffer temp = new StringBuffer();
                        for (sportComplexUserClass u : tempList) {
                            if (u.userFullName.compareTo(str) < 0)
                                temp.append(u).append("\n");
                        }
                        JOptionPane.showMessageDialog(null, temp);
                    } else if (trainerSFullNameRadioButton.isSelected()) {
                        List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                        tempList.sort(Comparator.comparing(o -> o.trainerFullName));
                        StringBuffer temp = new StringBuffer();
                        for (sportComplexUserClass u : tempList) {
                            if (u.trainerFullName.compareTo(str) < 0)
                                temp.append(u).append("\n");
                        }
                        JOptionPane.showMessageDialog(null, temp);
                    } else if (dataAndTimeRadioButton.isSelected()) {
                        List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
                        tempList.sort((o1, o2) -> {
                            Date d1;
                            Date d2;
                            try {
                                d1 = sdf.parse(o1.dateAngTimeOfBeginning);
                                d2 = sdf.parse(o2.dateAngTimeOfBeginning);
                                assert d1 != null;
                                return d1.compareTo(d2);
                            } catch (ParseException ignored) {
                            }
                            return 0;
                        });
                        StringBuilder temp = new StringBuilder();
                        for (sportComplexUserClass u : tempList) {
                            try {
                                if (sdf.parse(u.dateAngTimeOfBeginning).compareTo(sdf.parse(str)) < 0)
                                    temp.append(u).append("\n");
                            } catch (ParseException parseException) {
                                parseException.printStackTrace();
                            }
                        }
                    } else JOptionPane.showMessageDialog(null,
                            "No 'sorted-by' parameters have been chosen");
                } else JOptionPane.showMessageDialog(null,
                        "No 'sorted-by' parameters have been chosen");

        });
    }
}
