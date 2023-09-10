/*
import java.io.*;
import java.util.ArrayList;
import java.util.Collections;

class individualTree35 {
    Integer info;
    individualTree35 left;
    individualTree35 right;
    Integer distRootNode;
    Integer height;
    ArrayList<Integer> distancesL;
    ArrayList<Integer> distancesR;
    ArrayList<Integer> distancesU;

    public individualTree35() {
        this.info = null;
        this.left = null;
        this.right = null;
    }

    public individualTree35(int n) {
        this.info = n;
        this.left = null;
        this.right = null;
        this.distRootNode = 0;
        this.height = 0;
    }

    public individualTree35(int n, int d) {
        this.info = n;
        this.left = null;
        this.right = null;
        this.distRootNode = d;
    }
    public void add(int n) {
        if (this.info == null)
            this.info = n;
        else {
            if (n < this.info) {
                if (this.left == null)
                    this.left = new individualTree35(n, this.distRootNode + 1);
                else {
                    assert false;
                    this.left.add(n);
                }
            } else if (n > this.info) {
                if (this.right == null)
                    this.right = new individualTree35(n, this.distRootNode + 1);
                else {
                    assert false;
                    this.right.add(n);
                }
            }
        }
    }

    public void leftTraversal(BufferedWriter w) throws IOException {
        if (this.info == null) {
            return;
        } else {
            assert false;
            w.write(this.info.toString() + '\n');
            w.flush();
            if (this.left != null)
                this.left.leftTraversal(w);
            if (this.right != null)
                this.right.leftTraversal(w);
        }
    }

    public void reversTraversalWithNodesHeight() {
        if (this.info == null) {
            return;
        } else {
            assert false;
            if (this.left != null)
                this.left.reversTraversalWithNodesHeight();
            if (this.right != null)
                this.right.reversTraversalWithNodesHeight();
            if (this.left == null && this.right == null)
                this.height = 0;
            else if (this.left != null && this.right == null)
                this.height = this.left.height + 1;
            else if (this.left == null && this.right != null)
                this.height = this.right.height + 1;
            else
                this.height = (this.left.height > this.right.height) ?
                        this.left.height + 1 : this.right.height + 1;
            treesArray.add(this);
        }
    }

    public int MSL() {
        if (this.left == null && this.right == null)
            return 0;
        else if (this.left != null && this.right == null)
            return this.left.height + 1;
        else if (this.left == null && this.right != null)
            return this.right.height + 1;
        else
            return this.left.height + this.right.height + 2; //а для корня, по идее, сумма msl вершин наиб.?
    }

    private int findMin() {
        if (this.left != null)
            return this.left.findMin();
        else
            return this.info;
    }

    private boolean find(int n) {
        if (this.info == null)
            return false;
        if (this.info == n)
            return true;
        else {
            if (n > this.info) {
                if (this.right == null)
                    return false;
                return this.right.find(n);
            } else {
                if (this.left == null)
                    return false;
                return this.left.find(n);
            }
        }
    }

    public individualTree35 delete(int n) {
        if (this.find(n)) {
            if (this.info == null)
                return null;

            if (n < this.info) {
                this.left = this.left.delete(n);
                return this;
            } else if (n > this.info) {
                this.right = this.right.delete(n);
                return this;
            }

            if (this.left == null)
                return this.right;
            else if (this.right == null)
                return this.left;
            else {
                int minNode = this.right.findMin();
                this.info = minNode;
                this.right = this.right.delete(minNode);
                return this;
            }
        } else
            return this;
    }

    private individualTree35 findLCA(individualTree35 t1, individualTree35 t2) {
        if (this.info > t1.info && this.info > t2.info)
            return this.left.findLCA(t1, t2);
        if (this.info < t1.info && this.info < t2.info)
            return this.right.findLCA(t1, t2);
        return this;
    }

    public void defineArrays(individualTree35 root) {
        if (this.info == null) {
            return;
        } else {
            assert false;
            if (this.left != null)
                this.left.reversTraversalWithNodesHeight();
            if (this.right != null)
                this.right.reversTraversalWithNodesHeight();
            if (this.left == null && this.right == null){
                if (this.findLCA(root, this) == root && this.info < root.info)
                    distancesL.add(root.height);
                else
                if (this.findLCA(root, this) == root && this.info > root.info)
                    distancesR.add(root.height);
                else
                    distancesU.add(root.height);
            }
        }
    }
}

public class Test implements Runnable{
    public static void main(String[]args) {
        new Thread(null, new Test(), "", 64 * 1024 * 1024).start();
    }
    ArrayList<individualTree35> treesArray = new ArrayList<>();
    static ArrayList<Integer> suspiciousNodes = new ArrayList<>();
    public void treesCheck(int k){
        this.reversTraversalWithNodesHeight();
        for (individualTree35 it : treesArray) {
            if (it.MSL() < k)
                suspiciousNodes.add(it.info);
            else{
                this.defineArrays(it);
                boolean flag = false;
                for (int l : it.distancesL) {
                    for (int r : it.distancesR) {
                        if (l + r == k) {
                            flag = true;
                            break;
                        }
                        for (int u : it.distancesU) {
                            if (l + u == k || r + u == k){
                                flag = true;
                                break;
                            }
                        }
                        if (flag)
                            break;
                    }
                    if (flag)
                        break;
                }
                if (flag)
                    suspiciousNodes.add(it.info);
            }
        }
    }
    public void run() {
        try {
            BufferedReader in = new BufferedReader(new FileReader("tst.in"));;
            BufferedWriter out = new BufferedWriter(new FileWriter("tst.out"));
            int k;
            k = Integer.parseInt(in.readLine());
            String line;
            individualTree35 tree;
            int r = Integer.parseInt(in.readLine());
            tree = new individualTree35(r);
            while ((line = in.readLine()) != null)
                tree.add(Integer.parseInt(line));
            tree.treesCheck(k);
            suspiciousNodes.sort(Collections.reverseOrder());
            tree.delete(suspiciousNodes.get(0));
            tree.leftTraversal(out);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
*/
