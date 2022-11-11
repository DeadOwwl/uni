import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.regex.Pattern;

public class JUIPanel extends JPanel {

    private final JTextArea textArea = new JTextArea(25, 50);

    private final JTextField jTextFieldFormat = new JTextField(15);
    private final JTextField jTextFieldDepth = new JTextField(15);

    JCheckBox jCheckBoxUseSubDirs = new JCheckBox("Искать в поддиректориях");
    JCheckBox jCheckBoxFindFile = new JCheckBox("Искать файлы");
    JCheckBox jCheckBoxFindDirs = new JCheckBox("Искать поддиректории");

    private void init() {

        jTextFieldFormat.setText(".*");
        jTextFieldDepth.setText("1");

        GridLayout gridLayout = new GridLayout(1, 2);

        setLayout(gridLayout);

        textArea.setEditable(false);
        textArea.setLineWrap(false);
        JScrollPane scrollPane = new JScrollPane(textArea, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

        Panel panel = new Panel(new FlowLayout(FlowLayout.LEADING));

        panel.add(new Label("Формат:"));
        panel.add(jTextFieldFormat);
        panel.add(jCheckBoxUseSubDirs);
        panel.add(jCheckBoxFindFile);
        panel.add(jCheckBoxFindDirs);
        panel.add(new Label("Глубина:"));
        panel.add(jTextFieldDepth);

        add(scrollPane);
        add(panel);

        setVisible(true);
    }

    public JUIPanel(SearchThread searchThread) {
        init();
    }

    public void updateText(List<String> lines) {
        textArea.setText("");
        for (String string: lines) {
            textArea.append(string + "\n");
        }
    }

    public String getFormat() {
        try {
            Pattern.compile(jTextFieldFormat.getText());
            jTextFieldFormat.setBackground(Color.white);
        } catch (Exception ex) {
            jTextFieldFormat.setBackground(Color.RED);
        }
        return jTextFieldFormat.getText();
    }

    public boolean useSubDirs() {
        jTextFieldDepth.setEditable(jCheckBoxUseSubDirs.isSelected());
        return jCheckBoxUseSubDirs.isSelected();
    }

    public boolean findFiles() {
        return jCheckBoxFindFile.isSelected();
    }

    public boolean findDirs() {
        return jCheckBoxFindDirs.isSelected();
    }

    public int getMaxDepth() {
        try {
            int depth = Integer.parseInt(jTextFieldDepth.getText());
            jTextFieldDepth.setBackground(Color.WHITE);
            return depth;
        } catch (NumberFormatException ex) {
            jTextFieldDepth.setBackground(Color.RED);
            return 0;
        }
    }
}
