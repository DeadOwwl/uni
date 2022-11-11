import javax.swing.tree.DefaultTreeModel;

public class TrModel extends DefaultTreeModel {

    private static final long serialVersionUID = 1L;
    private final TrNode root;

    TrModel(TrNode root) {
        super(root);
        this.root = root;
    }

    public TrNode getRoot() {
        return root;
    }

    void insertNodeInto(TrNode child, TrNode parent, int i, boolean flag) {
        insertNodeInto(child, parent, i);
        parent.addNode(child);
    }

}