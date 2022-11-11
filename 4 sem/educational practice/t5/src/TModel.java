import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class TModel implements TableModel {

    private final Set<TableModelListener> listeners = new HashSet<TableModelListener>();
    private ArrayList<Node> infoNodes = new ArrayList<>();
    static final String[] columnNames = new String[]{"Name", "Year", "Sculptors", "Address"};
    static final Class<?>[] columnTypes = new Class[]{String.class, String.class, String.class, String.class};

    public TModel() {
    }

    public TModel(ArrayList<Node> al) {
        setInfoNodes(al);
    }

    public void setInfoNodes(ArrayList<Node> al) {
        infoNodes = al;
    }

    @Override
    public void addTableModelListener(TableModelListener l) {
        listeners.add(l);
    }

    @Override
    public Class<?> getColumnClass(int columnIndex) {
        return columnTypes[columnIndex];
    }

    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    @Override
    public String getColumnName(int columnIndex) {
        return columnNames[columnIndex];
    }

    @Override
    public int getRowCount() {
        return infoNodes.size();
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Node an = infoNodes.get(rowIndex);
        switch (columnIndex) {
            case 0:
                return an.getNaming();
            case 1:
                return an.getYear();
            case 2:
                return an.getSculptors();
            case 3:
                return an.getAddress();
        }
        return "";
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return false;
    }

    @Override
    public void removeTableModelListener(TableModelListener l) {
        listeners.remove(l);
    }

    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
    }
}