
import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashSet;
import java.util.Set;

public class CatalogTableDriverModel implements TableModel {

    static final String[] columnNames = new String[]{"FIO", "Sex", "Birthday"};
    static final Class[] columnTypes = new Class[]{String.class, Integer.class, Date.class};
    private Set<TableModelListener> listeners = new HashSet<TableModelListener>();
    private ArrayList<driverItem> infoNodes = new ArrayList<driverItem>();


    public CatalogTableDriverModel() {infoNodes = new ArrayList<>();}

    public CatalogTableDriverModel(ArrayList<driverItem> al) {
        setInfoNodes(al);
    }

    public void setInfoNodes(ArrayList<driverItem> al) {
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
        driverItem an = infoNodes.get(rowIndex);
        switch (columnIndex) {
            case 0:
                return an.fio;
            case 1:
                return an.sex;
            case 2:
                return an.birthDate;
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