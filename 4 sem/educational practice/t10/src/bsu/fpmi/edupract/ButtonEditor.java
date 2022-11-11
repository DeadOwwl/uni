/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bsu.fpmi.edupract;

import java.beans.*;
import javax.swing.JButton;

public class ButtonEditor extends PropertyEditorSupport {
    
     @Override
    public String[] getTags() {
        return new String[] {"Button 1", "Button 2", "Button 3"};
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
        if (o.equals("Button 1")) return "\"Button 1\"";
	else if (o.equals("Button 2")) return "\"Button 2\"";
	else if (o.equals("Button 3")) return "\"Button 3\"";
	return null;
    }
    
}
