/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bsu.fpmi.edupract;

import java.beans.*;
import javax.swing.JButton;

public class RadioButton2TextEditor extends PropertyEditorSupport {
    
     @Override
    public String[] getTags() {
        return new String[] {"SRB 1", "SRB 2", "SRB 3"};
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
        if (o.equals("SRB 1")) return "\"SRB 1\"";
	else if (o.equals("SRB 2")) return "\"SRB 2\"";
	else if (o.equals("SRB 3")) return "\"SRB 3\"";
	return null;
    }
    
}
