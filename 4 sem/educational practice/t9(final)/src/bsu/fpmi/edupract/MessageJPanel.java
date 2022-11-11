package bsu.fpmi.edupract;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.Box;
import javax.swing.JOptionPane;

public class MessageJPanel extends javax.swing.JPanel {
    private javax.swing.JButton jButton1;
    private javax.swing.JRadioButton jRadioButton1;
    private javax.swing.JRadioButton jRadioButton2;
    private javax.swing.JLabel jLabel1;
    
	String STR = "Button is pressed. ";
        String radio = "Both radio buttons are not selected. ";
	ActionListener listener = new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent ae) {
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
        }
    };

    private char c;
    public char key = 'q';

    public MessageJPanel() {
        initComponents();
        initEnterKey();
    }
    
    private void jTextField1KeyTyped(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_jTextField1KeyTyped
        if (evt.getKeyChar() == key) {
             evt.consume();
            jButton1.doClick();
        }
        }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents()
    {

        jLabel1 = new javax.swing.JLabel();
        jButton1 = new javax.swing.JButton();
        jRadioButton1 = new javax.swing.JRadioButton(); 
        
                Box verticalBox = Box.createVerticalBox();
        verticalBox.add(jRadioButton1);
        verticalBox.add(jRadioButton2);
        verticalBox.add(jButton1);
        
        jRadioButton1.addActionListener(listener);
        jRadioButton1.setSelected(false);

        jRadioButton2 = new javax.swing.JRadioButton();
        
        jRadioButton2.addActionListener(listener);
        jRadioButton2.setSelected(false);
        
        //ButtonGroup group = new ButtonGroup();
        //group.add(jRadioButton1);
        //group.add(jRadioButton2);
        
        setToolTipText("");

        jLabel1.setText("label");
        jLabel1.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                jTextField1KeyTyped(evt);
            }
        });
        
        jRadioButton1.setText("RadioButton1");
        jRadioButton1.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                jTextField1KeyTyped(evt);
            }
        });
        
        jRadioButton2.setText("RadioButton2");
        jRadioButton2.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                jTextField1KeyTyped(evt);
            }
        });

        jButton1.setText("button");
        jButton1.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                jTextField1KeyTyped(evt);
            }
        });
        
        jButton1.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                jButton1ActionPerformed(evt);
            }
        });

        this.setLayout(new BorderLayout());
        
        this.add(jLabel1, BorderLayout.NORTH);
        this.add(verticalBox);
        
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addComponent(jRadioButton1)
                .addComponent(jRadioButton2)
                .addGap(18, 18, 18)
                .addComponent(jButton1)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(jButton1)
                    .addComponent(jRadioButton1)
                    .addComponent(jRadioButton2)
                    )
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt)    {
        JOptionPane.showMessageDialog(this, STR + radio);
    }

    private void initEnterKey() {
        jButton1.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e) {
                if (e.getKeyChar() == c) {
                    jButton1.doClick();
                }
            }

            @Override
            public void keyPressed(KeyEvent e) {
            }

            @Override
            public void keyReleased(KeyEvent e) {
            }
        });
    }
    
    public String getLabel() {
        return jLabel1.getText();
    }
    
    public void setLabel(String s) {
        jLabel1.setText(s);
    }
    
    public String getRadioButton2() {
        return jRadioButton2.getText();
    }
    
    public void setRadioButton2(String s) {
        jRadioButton2.setText(s);
    }
    
    public String getRadioButton1() {
        return jRadioButton1.getText();
    }

    public void setRadioButton1(String s) {
        jRadioButton1.setText(s);
    }
    
    public String getButton() {
        return jButton1.getText();
    }

    public void setButton(String s) {
        jButton1.setText(s);
    }
}