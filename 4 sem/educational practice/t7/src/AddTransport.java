import javax.swing.*;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class AddTransport extends JDialog {
    static String driver = "org.apache.derby.jdbc.EmbeddedDriver";
    static String connect = "jdbc:derby:CatalogDB";
    static String mIns = "INSERT INTO Camera(Company, Type, Name, Cost) VALUES(?,?,?,?)";
    CatalogFrame frame;
    private JLabel CompanyLabel;
    private JTextField CompanyTextField;
    private JButton closeButton;
    private JLabel CostLabel;
    private JTextField CostTextField;
    private JSeparator jSeparator1;
    private JSeparator jSeparator2;
    private JLabel NameLabel;
    private JTextField NameTextField;
    private JButton okButton;
    private JLabel TypeLabel;
    private JTextField TypeTextField;

    public AddTransport(CatalogFrame temp) {
        frame = temp;
        initComponents();
        this.setTitle("Add Transport");
        this.setSize(400, 300);
        this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setModal(true);
    }

    private void initComponents() {
        CompanyLabel = new JLabel();
        TypeLabel = new JLabel();
        NameLabel = new JLabel();
        CostLabel = new JLabel();

        CompanyTextField = new JTextField();
        TypeTextField = new JTextField();
        NameTextField = new JTextField();
        CostTextField = new JTextField();

        jSeparator1 = new JSeparator();
        jSeparator2 = new JSeparator();
        okButton = new JButton();
        closeButton = new JButton();

        CompanyLabel.setText("Number:");
        NameLabel.setText("Route:");
        TypeLabel.setText("Type:");
        CostLabel.setText("Price:");
        CompanyTextField.addCaretListener(this::colorTextFieldCaretUpdate);
        TypeTextField.addCaretListener(this::speciesTextFieldCaretUpdate);
        NameTextField.addCaretListener(this::typeTextFieldCaretUpdate);

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
                                                        .addComponent(CostLabel)
                                                        .addComponent(CompanyLabel)
                                                        .addComponent(NameLabel)
                                                        .addComponent(TypeLabel)

                                                )
                                                .addGap(28, 28, 28)
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                        .addComponent(CostTextField, GroupLayout.Alignment.TRAILING)
                                                        .addComponent(CompanyTextField, GroupLayout.Alignment.TRAILING)
                                                        .addComponent(NameTextField, GroupLayout.Alignment.TRAILING)
                                                        .addComponent(TypeTextField)
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
                                        .addComponent(CostLabel)
                                        .addComponent(CostTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(CompanyLabel)
                                        .addComponent(CompanyTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(NameLabel)
                                        .addComponent(NameTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                        .addComponent(TypeLabel, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                                        .addComponent(TypeTextField))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                )
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
        if (this.CompanyTextField.getText().isEmpty() || this.TypeTextField.getText().isEmpty()
                || this.NameTextField.getText().isEmpty() || this.CostTextField.getText().isEmpty()) {
            JOptionPane.showMessageDialog(this, "fill all fields!", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (this.okButton.isEnabled()) {

            transportItem transportItemb = new transportItem(
                    this.CompanyTextField.getText(),this.TypeTextField.getText(), this.NameTextField.getText(),
                    Float.valueOf(this.CostTextField.getText()));

            try {
                // Регистрируем драйвер JDBC
                Class.forName( driver );
                // Подключаемся к БД
                Connection conn = DriverManager.getConnection(connect);
                // Выполняем запросы

                PreparedStatement st = conn.prepareStatement(mIns);

                    try {
                        st.setString( 3, transportItemb.transportNumber);
                        st.setString(1, transportItemb.transportType);
                        st.setString(2, transportItemb.transportWay);
                        st.setFloat( 4, transportItemb.cost);
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
            CatalogFrame.tableTransportModel = new CatalogTableTransportModel(CatalogDB.ReadMonumentDB());
            CatalogFrame.infoTransportPanel.setModel( CatalogFrame.tableTransportModel);
            this.dispose();
        }
    }

    public void checkOkClose() {

        if (!this.CostTextField.getText().isEmpty()
                && !this.CompanyTextField.getText().isEmpty()
                && !this.NameTextField.getText().isEmpty()
                && !this.TypeTextField.getText().isEmpty()) {
            this.okButton.setEnabled(true);
        }
    }
}


