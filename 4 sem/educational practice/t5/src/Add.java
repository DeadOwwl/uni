import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class Add extends JDialog {
    private final Frame frame;
    private final JTextField editName = new JTextField();
    private final JTextField editPrice = new JTextField();
    private final JTextField editSculptors = new JTextField();
    private final JButton okButton = new JButton();
    private final JTextField editYear = new JTextField();

    public Add(Frame frame) {
        this.frame = frame;
        initComponents();
        setTitle("Add a new historical monument");
        setBounds(400, 200, 400, 150);
        setSize(400, 400);
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
    }

    private void initComponents() {
        final JLabel lblName = new JLabel();
        final JLabel lblYear = new JLabel();
        final JLabel lblSculptors = new JLabel();
        final JLabel lblAddress = new JLabel();
        JButton closeButton = new JButton();
        lblName.setText("Name");
        lblYear.setText("Year");
        lblSculptors.setText("Sculptors");
        lblAddress.setText("Address");
        editName.addCaretListener(e-> closeCheck());
        editYear.addCaretListener(e-> closeCheck());
        editSculptors.addCaretListener(e-> closeCheck());

        okButton.setText("Add");
        okButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent evt) {
                if (editName.getText().isEmpty() ||
                        editYear.getText().isEmpty() ||
                        editSculptors.getText().isEmpty() ||
                        editPrice.getText().isEmpty()) {
                    JOptionPane.showMessageDialog(Add.this,
                            "All fields should be filled!",
                            "Error",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }
                if (okButton.isEnabled()) {
                    Node nb = new Node(editName.getText(),
                            editYear.getText(),
                            editSculptors.getText(),
                            editPrice.getText());
                    frame.addNewItem(nb);
                    dispose();
                }
            }
        });
        closeButton.setText("Cancel");
        closeButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent evt) {
                dispose();
            }
        });
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup().addContainerGap()
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                .addComponent(lblYear).addComponent(lblSculptors).addComponent(lblName).addComponent(lblAddress)
                                        ).addGap(28, 28, 28)
                                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                .addComponent(editYear, GroupLayout.Alignment.TRAILING)
                                                .addComponent(editSculptors, GroupLayout.Alignment.TRAILING)
                                                .addComponent(editPrice, GroupLayout.Alignment.TRAILING)
                                                .addComponent(editName)))
                                .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                                .addGroup(layout.createSequentialGroup().addComponent(okButton)
                                                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                        .addComponent(closeButton))
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                        .addGroup(layout.createSequentialGroup().addGap(18, 18, 18)
                                                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED))))
                                        .addGap(0, 4, Short.MAX_VALUE)))
                        .addContainerGap()));
        layout.setVerticalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addGap(16, 16, 16)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGap(8, 8, 8)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(lblName)
                                        .addComponent(editName, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(lblYear)
                                        .addComponent(editYear, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(lblSculptors)
                                        .addComponent(editSculptors, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(editPrice, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                                        .addComponent(lblAddress))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 16, Short.MAX_VALUE)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(okButton)
                                        .addComponent(closeButton))
                                .addContainerGap()));
        pack();
    }



    public void closeCheck() {
        if (!editName.getText().isEmpty() &&
                !editYear.getText().isEmpty() &&
                !editSculptors.getText().isEmpty()) {
            okButton.setEnabled(true);
        }
    }

}