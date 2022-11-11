package Model;

import javax.swing.*;
import java.awt.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Comparator;

public class SortFrame extends JDialog{
    private JPanel panel1;
    private JRadioButton forwardSortRadioButton;
    private JRadioButton reverseSortRadioButton;
    private JRadioButton userSFullNameRadioButton;
    private JRadioButton trainerSFullNameRadioButton;
    private JRadioButton dateAndTimeRadioButton;
    private JButton Sort;

    SortFrame(){
        setContentPane(panel1);
        panel1.setPreferredSize(new Dimension(400, 400));
        setModal(true);

        Sort.addActionListener(e -> {
            if(forwardSortRadioButton.isSelected()){
                if(userSFullNameRadioButton.isSelected()){
                    List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                    GFrame.cont.clear();
                    tempList.sort(Comparator.comparing(o -> o.userFullName));
                    GFrame.cont.addAll(tempList);
                }else
                if(trainerSFullNameRadioButton.isSelected()){
                    List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                    GFrame.cont.clear();
                    tempList.sort(Comparator.comparing(o -> o.trainerFullName));
                    GFrame.cont.addAll(tempList);
                }else
                if(dateAndTimeRadioButton.isSelected()){
                    List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                    GFrame.cont.clear();
                    tempList.sort((o1, o2) -> {
                        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
                        Date d1;
                        Date d2;
                        try {
                            d1 = sdf.parse(o1.dateAngTimeOfBeginning);
                            d2 = sdf.parse(o2.dateAngTimeOfBeginning);
                            assert d1 != null;
                            return d1.compareTo(d2);
                        } catch (ParseException ignored) {}
                        return 0;
                    });
                    GFrame.cont.addAll(tempList);
                }
                else JOptionPane.showMessageDialog(null,
                            "No 'sorted-by' parameters have been chosen");
            }
            else if (reverseSortRadioButton.isSelected()) {
                if (userSFullNameRadioButton.isSelected()) {
                    List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                    GFrame.cont.clear();
                    tempList.sort((o1, o2) -> o2.userFullName.compareTo(o1.userFullName));
                    GFrame.cont.addAll(tempList);
                }else if (trainerSFullNameRadioButton.isSelected()) {
                    List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                    GFrame.cont.clear();
                    tempList.sort((o1, o2) -> o2.trainerFullName.compareTo(o1.trainerFullName));
                    GFrame.cont.addAll(tempList);
                }else  if (dateAndTimeRadioButton.isSelected()) {
                    List<sportComplexUserClass> tempList = new ArrayList<>(GFrame.cont);
                    GFrame.cont.clear();
                    tempList.sort((o1, o2) -> {
                        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
                        Date d1;
                        Date d2;
                        try {
                            d1 = sdf.parse(o1.dateAngTimeOfBeginning);
                            d2 = sdf.parse(o2.dateAngTimeOfBeginning);
                            assert d1 != null;
                            return d2.compareTo(d1);
                        } catch (ParseException ignored) {}
                        return 0;
                    });
                    GFrame.cont.addAll(tempList);
                } else JOptionPane.showMessageDialog(null,
                        "No 'sorted-by' parameters have been chosen");
            }
            else JOptionPane.showMessageDialog(null,
                        "No types of sorting have been chosen");
            dispose();
        });
    }
}
