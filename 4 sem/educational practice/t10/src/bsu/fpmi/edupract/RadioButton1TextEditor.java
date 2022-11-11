/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bsu.fpmi.edupract;

import java.beans.*;
import javax.swing.JButton;

public class RadioButton1TextEditor extends PropertyEditorSupport {
    
     @Override
    public String[] getTags() {
        return new String[] {"FRB 1", "FRB 2", "FRB 3"};
    }

    @Override
    public void setAsText(String s) {
        setValue(s);
    }

    @Override
    public String getAsText() {
        return (String) getValue();
    }

    @Override
    public String getJavaInitializationString() {
	Object o = getValue();
        if (o.equals("FRB 1")) return "\"FRB 1\"";
	else if (o.equals("FRB 2")) return "\"FRB 2\"";
	else if (o.equals("FRB 3")) return "\"FRB 3\"";
	return null;
    }
    
}
