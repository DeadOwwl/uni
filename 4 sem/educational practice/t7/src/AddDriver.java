import javax.swing.*;
import java.io.IOException;
import java.sql.*;

public class AddDriver extends JDialog {
    static String driver = "org.apache.derby.jdbc.EmbeddedDriver";
    static String connect = "jdbc:derby:CatalogDB";
    static String buyerIns = "INSERT INTO Buyer(FIO, Sex, BirthDate) VALUES(?,?,?)";
    CatalogFrame frame;
    private JLabel fioLabel;
    private JTextField fioTextField;
    private JButton closeButton;
    private JLabel sexLabel;
    private JTextField sexTextField;
    private JSeparator jSeparator1;
    private JSeparator jSeparator2;
    private JLabel birthdayLabel;
    private JTextField birthdayTextField;
    private JButton okButton;

    public AddDriver(CatalogFrame temp) {
        frame = temp;
        initComponents();
        this.setTitle("Add Driver");
        this.setSize(400, 300);
        this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setModal(true);

    }

    private void initComponents() {

        fioLabel = new JLabel();
        sexLabel = new JLabel();
        birthdayLabel = new JLabel();

        fioTextField = new JTextField();
        sexTextField = new JTextField();
        birthdayTextField = new JTextField();

        jSeparator1 = new JSeparator();
        jSeparator2 = new JSeparator();
        okButton = new JButton();
        closeButton = new JButton();

        fioLabel.setText("FIO:");
        sexLabel.setText("Sex:");
        birthdayLabel.setText("Birthday:");

        fioTextField.addCaretListener(this::colorTextFieldCaretUpdate);
        sexTextField.addCaretListener(this::speciesTextFieldCaretUpdate);
        birthdayTextField.addCaretListener(this::typeTextFieldCaretUpdate);

        okButton.setText("Add");
        okButton.addMouseListener(new java.awt.event.MouseAdapter() {
            @Override
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                try {
                    okButtonMouseClicked(evt);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        closeButton.setText("Close");
        closeButton.addMouseListener(new java.awt.event.MouseAdapter() {
            @Override
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                closeButtonMouseClicked(evt);
            }
        });
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                        .addComponent(jSeparator1)
                                        .addGroup(layout.createSequentialGroup()
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                        .addComponent(fioLabel)
                                                        .addComponent(sexLabel)
                                                        .addComponent(birthdayLabel)


                                                )
                                                .addGap(28, 28, 28)
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                        .addComponent(fioTextField, GroupLayout.Alignment.TRAILING)
                                                        .addComponent(sexTextField, GroupLayout.Alignment.TRAILING)
                                                        .addComponent(birthdayTextField)
                                                ))
                                        .addComponent(jSeparator2)
                                        .addGroup(layout.createSequentialGroup()
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                                        .addGroup(layout.createSequentialGroup()
                                                                .addComponent(okButton)
                                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                                .addComponent(closeButton))
                                                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                                .addGroup(layout.createSequentialGroup()
                                                                        .addGap(18, 18, 18)
                                                                        .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED))
                                                        ))
                                                .addGap(0, 4, Short.MAX_VALUE)))
                                .addContainerGap())
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addGap(16, 16, 16)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jSeparator1, GroupLayout.PREFERRED_SIZE, 10, GroupLayout.PREFERRED_SIZE)
                                .addGap(8, 8, 8)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(fioLabel)
                                        .addComponent(fioTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(sexLabel)
                                        .addComponent(sexTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(birthdayLabel)
                                        .addComponent(birthdayTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                )
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                )
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jSeparator2, GroupLayout.PREFERRED_SIZE, 10, GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                )
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 16, Short.MAX_VALUE)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(okButton)
                                        .addComponent(closeButton))
                                .addContainerGap())
        );
        pack();
    }

    private void colorTextFieldCaretUpdate(javax.swing.event.CaretEvent evt) {//GEN-FIRST:event_typeTextFieldCaretUpdate
        checkOkClose();
    }

    private void speciesTextFieldCaretUpdate(javax.swing.event.CaretEvent evt) {//GEN-FIRST:event_speciesTextFieldCaretUpdate
        checkOkClose();
    }

    private void typeTextFieldCaretUpdate(javax.swing.event.CaretEvent evt) {//GEN-FIRST:event_colorTextFieldCaretUpdate
        checkOkClose();
    }

    private void closeButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_closeButtonMouseClicked
        this.dispose();
    }

    private void okButtonMouseClicked(java.awt.event.MouseEvent evt) throws IOException {//GEN-FIRST:event_okButtonMouseClicked
        if (this.fioTextField.getText().isEmpty() || this.sexTextField.getText().isEmpty()
                || this.birthdayTextField.getText().isEmpty()) {
            JOptionPane.showMessageDialog(this, "fill all fields!", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (this.okButton.isEnabled()) {

            driverItem driverItem = new driverItem(
                    this.fioTextField.getText(),Integer.parseInt(this.sexTextField.getText()),
                    Date.valueOf(this.birthdayTextField.getText()));

            try {
                // Регистрируем драйвер JDBC
                Class.forName( driver );
                // Подключаемся к БД
                Connection conn = DriverManager.getConnection(connect);
                // Выполняем запросы

                PreparedStatement st = conn.prepareStatement(buyerIns);

                try {
                    st.setString( 1, driverItem.fio );
                    st.setInt(2, driverItem.sex);
                    st.setDate(3, driverItem.birthDate);
                    st.executeUpdate();
                } catch (SQLException e) {
                    JOptionPane.showMessageDialog(this, "Insert error: " + e , "Error", JOptionPane.ERROR_MESSAGE);
                    System.err.println("Insert error: " + e );
                }

                st.close();
                conn.close();

            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "Run-time error: " + e  , "Error", JOptionPane.ERROR_MESSAGE);
                System.err.println("Run-time error: " + e );
            }
            CatalogFrame.tableDriverModel = new CatalogTableDriverModel(CatalogDB.ReadBuyerDB());
            CatalogFrame.infoDriverPanel.setModel( CatalogFrame.tableDriverModel);
            this.dispose();
        }
    }

    public void checkOkClose() {

        if (!this.fioTextField.getText().isEmpty()
                && !this.sexTextField.getText().isEmpty()
                && !this.birthdayTextField.getText().isEmpty()) {
            this.okButton.setEnabled(true);
        }
    }
}


