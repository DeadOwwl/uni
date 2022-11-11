
package bsu.fpmi.edupract;

import java.beans.PropertyEditorSupport;
import javax.swing.JButton;

public class MyButtonEditor extends PropertyEditorSupport {
	
	@Override
	public String[] getTags() {
		return new String[] {"button"};
	}
	
	@Override
	public void setAsText(String s) {
		setValue(new JButton(s));
	}

	@Override 
	public String getAsText() {
		return ((JButton)getValue()).getText();
	}

	@Override
	public String getJavaInitializationString() {
		return "";
	}	
}
