package bsu.fpmi.edupract;

import javax.swing.JLabel;
import java.beans.PropertyEditorSupport;

public class MyLabelEditor extends PropertyEditorSupport {
	
	@Override
	public String[] getTags() {
		return new String[] {"Label"};
	}
	
	@Override
	public void setAsText(String s) {
		setValue(new JLabel(s));
	}

	@Override 
	public String getAsText() {
		return ((JLabel)getValue()).getText();
	}

	@Override
	public String getJavaInitializationString() {
		return "";
	}	
}
