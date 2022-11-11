package bsu.fpmi.edupract;

import javax.swing.JOptionPane;

public class MyComponent extends javax.swing.JPanel {
    
    private javax.swing.JButton jButton1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JRadioButton jRadioButton1;
    private javax.swing.JRadioButton jRadioButton2;

    public MyComponent() {
        initComponents();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jRadioButton1 = new javax.swing.JRadioButton();
        jRadioButton2 = new javax.swing.JRadioButton();
        jButton1 = new javax.swing.JButton();

        jLabel1.setText("Label");
        jRadioButton1.setText("First Radio Button");
        
        jRadioButton2.setText("Second Radio Button");
        jButton1.setText("Button");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });
        
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(38, 38, 38)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(67, 67, 67)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jLabel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jRadioButton1, javax.swing.GroupLayout.DEFAULT_SIZE, 170, Short.MAX_VALUE)
                         .addComponent(jRadioButton2, javax.swing.GroupLayout.DEFAULT_SIZE,170,Short.MAX_VALUE )
                        )
                        .addComponent(jButton1)))
                .addContainerGap(47, Short.MAX_VALUE)
            )
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 21, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(8, 8, 8)
                 .addComponent(jRadioButton1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jRadioButton2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(8, 8, 8)
                .addComponent(jButton1)
                .addContainerGap(184, Short.MAX_VALUE))
        );        
    }
        String STR = "Button is pressed. ";
        String radio = "Both radio buttons are not selected. ";
        
    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        STR =  "'" + jButton1.getText()+"' is pressed. ";
                        if (jRadioButton1.isSelected() && !jRadioButton2.isSelected()){
                radio = "'" + jRadioButton1.getText()+"' is selected. ";
            }
            else if (jRadioButton2.isSelected() && !jRadioButton1.isSelected()){
                radio = "'" + jRadioButton2.getText()+"' is selected. ";
            }
            else if (jRadioButton1.isSelected() && jRadioButton2.isSelected())
                radio = "Both '" + jRadioButton1.getText()+ "' & '" + jRadioButton2.getText() + "' are selected. ";
            else
                radio = "Both '" + jRadioButton1.getText()+ "' & '" + jRadioButton2.getText() + "' are not selected. ";
        JOptionPane.showMessageDialog(this, STR + radio);
    }//GEN-LAST:event_jButton1ActionPerformed
   
    public String getButton() {
        return jButton1.getText();
    }

    public void setButton(String s) {
        jButton1.setText(s);
    }
    
    public String getLabel() {
        return jLabel1.getText();
    }
    
    public void setLabel(String s) {
        jLabel1.setText(s);
    }
    
    public String getFirstRadioButton() {
        return jRadioButton1.getText();
    }
      
    public void setFirstRadioButton(String text) {
        jRadioButton1.setText(text);
    }
    
    public String getSecondRadioButton() {
        return jRadioButton2.getText();
    }
    
    public void setSecondRadioButton(String text) {
        jRadioButton2.setText(text);
    }

}
