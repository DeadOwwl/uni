package Model;

import javax.swing.*;
import java.awt.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class AddFrame extends JDialog {

    JTextField userFullNameInput;
    JTextField sectionCodeInput;
    JTextField occupationTypeInput;
    JTextField trainerFullNameInput;
    JTextField dateAngTimeOfBeginningInput;
    JTextField numOfMinutesInput;
    JTextField ratePerMinuteInput;
    JButton submit;
    private JPanel panel1;

    public AddFrame(){
        setContentPane(panel1);
        panel1.setPreferredSize(new Dimension(600, 600));
        setModal(true);

        submit.addActionListener(e -> {
            try {
                boolean flag = false;
                String userFullName = userFullNameInput.getText();
                for(sportComplexUserClass scu : GFrame.cont) {
                    if (userFullName.equalsIgnoreCase(scu.userFullName)) {
                        flag = true;
                        break;
                    }
                }
                int sectionCode = Integer.parseInt(sectionCodeInput.getText());
                String occupationType = occupationTypeInput.getText();
                String trainerFullName = trainerFullNameInput.getText();
                String dateAngTimeOfBeginning = dateAngTimeOfBeginningInput.getText();
                SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
                Date docDate= sdf.parse(dateAngTimeOfBeginning);
                dateAngTimeOfBeginning = sdf.format(docDate);

                int numOfMinutes = Integer.parseInt(numOfMinutesInput.getText());
                double ratePerMinute = Double.parseDouble(ratePerMinuteInput.getText());
                if (!flag) {
                    GFrame.cont.add(new sportComplexUserClass(userFullName, sectionCode, occupationType,
                            trainerFullName, dateAngTimeOfBeginning, numOfMinutes, ratePerMinute));
                    JOptionPane.showMessageDialog(null,
                            "New record has been successfully added");
                }
                else {
                    JOptionPane.showMessageDialog(null,
                            "The field 'Full Name' isn't unique");
                }
            }
            catch(IllegalArgumentException | ParseException ignored){
                JOptionPane.showMessageDialog(null,
                        "Input Error.");
            }
        });
    }

}
