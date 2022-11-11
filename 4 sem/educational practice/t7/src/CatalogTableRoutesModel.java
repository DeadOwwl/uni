
import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class CatalogTableRoutesModel implements TableModel {

    static final String[] columnNames = new String[]{"Driver's name", "Transport number", "If active"};
    static final Class[] columnTypes = new Class[]{String.class, String.class, Boolean.class};
    private Set<TableModelListener> listeners = new HashSet<TableModelListener>();
    private ArrayList<roadItem> infoNodes = new ArrayList<roadItem>();

    public CatalogTableRoutesModel() {infoNodes = new ArrayList<>();}

    public CatalogTableRoutesModel(ArrayList<roadItem> al) {
        setInfoNodes(al);
    }

    public void setInfoNodes(ArrayList<roadItem> al) {
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
        roadItem an = infoNodes.get(rowIndex);
        switch (columnIndex) {
            case 0:
                return an.fio;
            case 1:
                return an.name;
            case 2:
                return an.isPaied;
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