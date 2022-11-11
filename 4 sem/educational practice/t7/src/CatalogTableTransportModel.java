
import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class CatalogTableTransportModel implements TableModel {

    static final String[] columnNames = new String[]{"Number", "Type", "Route", "Price"};
    static final Class[] columnTypes = new Class[]{String.class, String.class, Integer.class,Float.class};
    private Set<TableModelListener> listeners = new HashSet<TableModelListener>();
    private ArrayList<transportItem> infoNodes = new ArrayList<transportItem>();


    public CatalogTableTransportModel() {infoNodes = new ArrayList<>();}

    public CatalogTableTransportModel(ArrayList<transportItem> al) {
        setInfoNodes(al);
    }

    public void setInfoNodes(ArrayList<transportItem> al) {
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
        transportItem an = infoNodes.get(rowIndex);
        switch (columnIndex) {
            case 0:
                return an.transportNumber;
            case 1:
                return an.transportType;
            case 2:
                return an.transportWay;
            case 3:
                return an.cost;
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