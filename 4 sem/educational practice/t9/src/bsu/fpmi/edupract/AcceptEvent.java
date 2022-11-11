package bsu.fpmi.edupract;

public class AcceptEvent extends java.util.EventObject {
    public static final int MESSAGE = 0;
    protected int id;
    
    public AcceptEvent(Object source, int id) {
	super(source);
	this.id = id;
    }
    
    public int getID() {
        return id;
    }
}
