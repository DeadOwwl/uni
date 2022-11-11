package bsu.fpmi.edupract;

import java.beans.*;
import java.lang.reflect.*;
import java.awt.*;

public class MessageJPanelInfo extends SimpleBeanInfo {

    static PropertyDescriptor prop(String name, String description) {
	try {
	    PropertyDescriptor p =
		new PropertyDescriptor(name, MessageJPanel.class);
	    p.setShortDescription(description);
	    return p;
	}
	catch(IntrospectionException e) { return null; } 
    }

    static PropertyDescriptor[] props = {
	prop("labelText", "The message text that appears in the bean body"),
	prop("firstRadioButtonText", "The label for the first radio button"),
	prop("secondRadioButtonText", "The label for the second radio button"),
	prop("buttonText", "The label for the simple button"),
    };
    
    static {
	props[0].setPropertyEditorClass(MyLabelEditor.class);
        props[1].setPropertyEditorClass(MyFRadioButtonEditor.class);
        props[2].setPropertyEditorClass(MySRadioButtonEditor.class);
        props[3].setPropertyEditorClass(MyButtonEditor.class);
    }
    
    public PropertyDescriptor[] getPropertyDescriptors() { return props; }
    
    public int getDefaultPropertyIndex() { return 0; }
}

    