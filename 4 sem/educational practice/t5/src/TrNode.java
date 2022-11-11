import javax.swing.tree.DefaultMutableTreeNode;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;

class TrNode extends DefaultMutableTreeNode {
    private static final long serialVersionUID = 1L;

    private String nodeName;
    private Node nodeValue = null;
    private final ArrayList<TrNode> nodes = new ArrayList<>();
    private boolean isLeafNode = false;

    TrNode() {}

    TrNode(String name) {
        nodeName = name;
    }

    TrNode(String name, Node value) {
        nodeName = name;
        nodeValue = value;
        isLeafNode = true;
    }

    void addNode(TrNode node) {
        nodes.add(node);
    }

    void deleteNode(TrNode node) {
        nodes.removeIf(i -> i.toString().equalsIgnoreCase(node.toString()));
    }

    ArrayList<Node> getAllLeaves() {
        ArrayList<Node> leaves = new ArrayList<>();
        Deque<TrNode> deque = new ArrayDeque<>();

        deque.push(this);
        TrNode temp;
        while (!deque.isEmpty()) {
            temp = deque.removeFirst();
            if (temp.isLeafNode) {
                leaves.add(temp.getNodeValue());
            } else {
                deque.addAll(temp.nodes);
            }
        }

        return leaves;
    }

    private Node getNodeValue() {
        return nodeValue;
    }

    @Override
    public String toString() {
        return nodeName;
    }
}