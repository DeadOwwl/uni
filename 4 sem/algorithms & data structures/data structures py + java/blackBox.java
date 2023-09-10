import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

class UpgradedNote {
    UpgradedNote parent;
    int key;
    int countLefter;
    int add;
    UpgradedNote left;
    UpgradedNote right;

    public UpgradedNote() {
    }

    public UpgradedNote(UpgradedNote parent, int key, int countLefter, int add, UpgradedNote left, UpgradedNote right) {
        this.parent = parent;
        this.key = key;
        this.countLefter = countLefter;
        this.add = add;
        this.left = left;
        this.right = right;
    }

    public void push() {
        countLefter += add;
        if (left != null)
            left.add += add;
        if (right != null)
            right.add += add;
        add = 0;
    }
}

class UpgradedTree {
    private UpgradedNote root;
    private int size;

    public UpgradedTree() {
    }

    public int size() {
        return size;
    }

    public int get(int index) {
        return get(index, root);
    }

    public boolean add(int key) {
        if (root == null) {
            root = new UpgradedNote(null, key, 0, 0, null, null);
            size++;
            return true;
        }
        boolean res = add(key, root);
        if (res) size++;
        return res;
    }

    private int get(int index, UpgradedNote root) {
        root.push();
        if (index == root.countLefter)
            return root.key;
        if (index < root.countLefter)
            return get(index, root.left);
        return get(index, root.right);
    }

    private boolean add(int key, UpgradedNote root) {
        //if (key == root.key) return false;
        root.push();
        if (key < root.key)
            if (root.left != null) {
                boolean res = add(key, root.left);
                if (res) {
                    root.countLefter++;
                    if (root.right != null)
                        root.right.add++;
                }
                return res;
            } else {
                root.left = new UpgradedNote(root, key, root.countLefter, 0, null, null);
                root.countLefter++;
                if (root.right != null)
                    root.right.add++;
                return true;
            }
        if (root.right != null)
            return add(key, root.right);
        else {
            root.right = new UpgradedNote(root, key, root.countLefter + 1, 0, null, null);
            return true;
        }
    }

    private UpgradedNote getRight(UpgradedNote root) {
        root.push();
        if (root.right == null)
            return root;
        return getRight(root.right);
    }
}

public class blackBox implements Runnable{

    public static ArrayList<Integer> MainProcess(int m, int n, ArrayList<Integer> sequenceElements, ArrayList<Integer> sequenceInMoment) {
        ArrayList<Integer> ans = new ArrayList<>();
        int i = 0, sForMoment = 0, sForElement = 0;
        UpgradedTree dearTree = new UpgradedTree();
        while (i < n) {
            while (dearTree.size() != sequenceInMoment.get(sForMoment)) {
                boolean adding = dearTree.add(sequenceElements.get(sForElement));
                sForElement++;
            }
            sForMoment++;
            ans.add(dearTree.get(i));
            i++;
        }
        return ans;
    }

    public static void main(String[]args) {
        new Thread(null, new blackBox(), "", 64 * 1024 * 1024).start();
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(new FileReader("input.txt"));
            BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));

            int mCondition, nCondition;
            String line = in.readLine();
            StringTokenizer st = new StringTokenizer(line);
            mCondition = Integer.parseInt(st.nextToken());
            nCondition = Integer.parseInt(st.nextToken());

            ArrayList<Integer> sequenceElementsCondition = new ArrayList<>();
            line = in.readLine();
            st = new StringTokenizer(line);
            for (int i = 0; i < mCondition; i++)
                sequenceElementsCondition.add(Integer.parseInt(st.nextToken()));

            ArrayList<Integer> sequenceInMomentCondition = new ArrayList<>();
            line = in.readLine();
            st = new StringTokenizer(line);
            for (int i = 0; i < nCondition; i++)
                sequenceInMomentCondition.add(Integer.parseInt(st.nextToken()));

            ArrayList<Integer> answer = MainProcess(mCondition, nCondition, sequenceElementsCondition, sequenceInMomentCondition);

            for (int i = 0; i < nCondition; i++) {
                if (i == answer.size() - 1)
                    out.write(answer.get(i).toString());
                else
                    out.write(answer.get(i).toString() + ' ');
                out.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}