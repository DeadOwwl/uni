import javax.swing.*;
import java.io.IOException;
import java.sql.*;

public class AddRoute extends JDialog {
    static String driver = "org.apache.derby.jdbc.EmbeddedDriver";
    static String connect = "jdbc:derby:CatalogDB";
    static String shoppingBasketIns = "INSERT INTO ShoppingBasket(FIO, Name, isPaied) VALUES(?,?,?)";
    CatalogFrame frame;
    private JLabel fioLabel;
    private JTextField fioTextField;
    private JButton closeButton;
    private JLabel nameLabel;
    private JTextField nameTextField;
    private JSeparator jSeparator1;
    private JSeparator jSeparator2;
    private JLabel isPaidLabel;
    private JTextField isPaidTextField;
    private JButton okButton;

    public AddRoute(CatalogFrame temp) {
        frame = temp;
        initComponents();
        this.setTitle("Add Route");
        this.setSize(400, 300);
        this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setModal(true);

    }
    private void initComponents() {

        fioLabel = new JLabel();
        nameLabel = new JLabel();
        isPaidLabel = new JLabel();

        fioTextField = new JTextField();
        nameTextField = new JTextField();
        isPaidTextField = new JTextField();

        jSeparator1 = new JSeparator();
        jSeparator2 = new JSeparator();
        okButton = new JButton();
        closeButton = new JButton();

        fioLabel.setText("Driver's FIO:");
        nameLabel.setText("Transport's number:");
        isPaidLabel.setText("If active:");

        fioTextField.addCaretListener(this::colorTextFieldCaretUpdate);
        nameTextField.addCaretListener(this::speciesTextFieldCaretUpdate);
        isPaidTextField.addCaretListener(this::typeTextFieldCaretUpdate);

        okButton.setText("add");
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
                                                        .addComponent(nameLabel)
                                                        .addComponent(isPaidLabel)


                                                )
                                                .addGap(28, 28, 28)
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                        .addComponent(fioTextField, GroupLayout.Alignment.TRAILING)
                                                        .addComponent(nameTextField, GroupLayout.Alignment.TRAILING)
                                                        .addComponent(isPaidTextField)
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
                                        .addComponent(nameLabel)
                                        .addComponent(nameTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(isPaidLabel)
                                        .addComponent(isPaidTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
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
        if (this.fioTextField.getText().isEmpty() || this.nameTextField.getText().isEmpty()
                || this.isPaidTextField.getText().isEmpty()) {
            JOptionPane.showMessageDialog(this, "fill all fields!", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (this.okButton.isEnabled()) {

            roadItem roadItem = new roadItem(
                    this.fioTextField.getText(),this.nameTextField.getText(),
                    Boolean.parseBoolean(this.isPaidTextField.getText()));

            try {
                // Регистрируем драйвер JDBC
                Class.forName( driver );
                // Подключаемся к БД
                Connection conn = DriverManager.getConnection(connect);
                // Выполняем запросы

                PreparedStatement st = conn.prepareStatement(shoppingBasketIns);

                try {
                    st.setString( 1, roadItem.fio );
                    st.setString(2, roadItem.name);
                    st.setBoolean(3, roadItem.isPaied);
                    st.executeUpdate();
                } catch (SQLException e) {
                    JOptionPane.showMessageDialog(this, "Insert error: " + e   , "Error", JOptionPane.ERROR_MESSAGE);
                    System.err.println("Insert error: " + e );
                }

                st.close();
                conn.close();

            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "Run-time error: " + e  , "Error", JOptionPane.ERROR_MESSAGE);
                System.err.println("Run-time error: " + e );
            }
            CatalogFrame.tableRoadsModel =
                    new CatalogTableRoutesModel(CatalogDB.ReadShoppingBasketDB());
            CatalogFrame.infoRoadsPanel.setModel( CatalogFrame.tableRoadsModel);
            this.dispose();
        }
    }

    public void checkOkClose() {

        if (!this.fioTextField.getText().isEmpty()
                && !this.nameTextField.getText().isEmpty()
                && !this.isPaidTextField.getText().isEmpty()) {
            this.okButton.setEnabled(true);
        }
    }
}


