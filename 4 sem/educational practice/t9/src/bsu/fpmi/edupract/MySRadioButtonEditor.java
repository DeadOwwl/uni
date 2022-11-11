package bsu.fpmi.edupract;

import javax.swing.JRadioButton;
import java.beans.PropertyEditorSupport;

public class MySRadioButtonEditor extends PropertyEditorSupport {
	
	@Override
	public String[] getTags() {
		return new String[] {"RadioButton"};
	}
	
	@Override
	public void setAsText(String s) {
		setValue(new JRadioButton(s));
	}

	@Override 
	public String getAsText() {
		return ((JRadioButton)getValue()).getText();
	}

	@Override
	public String getJavaInitializationString() {
		return "";
	}	
}
