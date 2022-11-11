import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class JBeginPanel extends JPanel {

    private final SearchThread parent;

    public JBeginPanel(SearchThread parent) {
        this.parent = parent;
        JButton button = new JButton("Выбрать директорию.");
        setLayout(new GridBagLayout());
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    parent.setStartDir(Main.initStartDirectoryPath());
                    kill();
                } catch (Exception ex) {

                }
            }
        });
        add(button, new GridBagConstraints());
        setBackground(Color.RED);
        setVisible(true);
    }

    public void kill() {
        setVisible(false);
    }
}
