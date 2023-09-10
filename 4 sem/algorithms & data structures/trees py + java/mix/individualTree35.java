import java.io.*;
import java.util.ArrayList;
import java.util.Collections;

public class individualTree35 implements Runnable {
    Integer info;
    individualTree35 root;
    individualTree35 left;
    individualTree35 right;
    Integer level;
    ArrayList<Integer> distancesLeafL = new ArrayList<>();
    ArrayList<Integer> distancesLeafR = new ArrayList<>();
    ArrayList<Integer> distancesLeafU = new ArrayList<>();
    ArrayList<Integer> distancesNodes = new ArrayList<>();

    public individualTree35() {
        this.info = null;
        this.left = null;
        this.right = null;
    }

    public individualTree35(int n, individualTree35 r, int l) {
        this.info = n;
        this.left = null;
        this.right = null;
        this.root = r;
        this.level = l + 1;
    }

    public individualTree35(int n) {
        this.info = n;
        this.left = null;
        this.right = null;
        this.level = 0;
        this.root = this;
    }

    public void add(int n, ArrayList<individualTree35> treesArray) {
        if (this.info == null)
            this.info = n;
        else {
            if (n < this.info) {
                if (this.left == null) {
                    this.left = new individualTree35(n, this.root, this.level);
                    treesArray.add(this.left);
                }
                else {
                    assert false;
                    this.left.add(n, treesArray);
                }
            } else if (n > this.info) {
                if (this.right == null) {
                    this.right = new individualTree35(n, this.root, this.level);
                    treesArray.add(this.right);
                }
                else {
                    assert false;
                    this.right.add(n, treesArray);
                }
            }
        }
    }

    public int distances(individualTree35 it) {
        return Math.abs(this.level + it.level - 2 * this.root.findLCA(this, it).level);
    }

    public void reversTraversalDistances(ArrayList<individualTree35> treesArray) {
        if (this.info == null) {
            return;
        } else {
            assert false;
            if (this.left != null)
                this.left.reversTraversalDistances(treesArray);
            if (this.right != null)
                this.right.reversTraversalDistances(treesArray);
            this.defineArrays(treesArray);
        }
    }

    private individualTree35 findLCA(individualTree35 t1, individualTree35 t2) {
        if (this.info > t1.info && this.info > t2.info)
            return this.left.findLCA(t1, t2);
        if (this.info < t1.info && this.info < t2.info)
            return this.right.findLCA(t1, t2);
        return this;
    }

    public void defineArrays(ArrayList<individualTree35> treesArray) {
        for (individualTree35 it : treesArray) {
            if (it.left == null && it.right == null){
                individualTree35 common = this.root.findLCA(this, it);
                if (common == this && this.info > it.info) {
                    this.distancesLeafL.add(this.distances(it));
                }
                else
                if (common == this && this.info < it.info) {
                    this.distancesLeafR.add(this.distances(it));
                }
                else
                if (this != it)
                    this.distancesLeafU.add(this.distances(it));
            }
            if (!this.info.equals(it.info))
                this.distancesNodes.add(this.distances(it));
        }
    }

    static ArrayList<Integer> suspiciousNodes = new ArrayList<>();
    public void treesCheck(int k, ArrayList<individualTree35> treesArray){
        if (this.info == null) {
            return;
        }
        else {
            if (this.left != null)
                this.left.treesCheck(k, treesArray);
            if (this.right != null)
                this.right.treesCheck(k, treesArray);

            boolean suspiciousNode = true;

            this.distancesNodes.sort(Collections.reverseOrder());
            this.distancesLeafL.sort(Collections.reverseOrder());
            this.distancesLeafR.sort(Collections.reverseOrder());
            this.distancesLeafU.sort(Collections.reverseOrder());

            if (this.distancesNodes.size() != 0) {
                if (this.distancesNodes.get(0) < k) {
                    if (this.distancesLeafL.size() == 0 && this.distancesLeafR.size() == 0 && this.distancesLeafU.size() != 0)
                        for (int u : this.distancesLeafU)
                            if (u == k) {
                                suspiciousNode = false;
                                break;
                            }
                    if (this.distancesLeafL.size() != 0 && this.distancesLeafR.size() != 0)
                        for (int l : this.distancesLeafL) {
                            for (int r : this.distancesLeafR)
                                if (l + r == k) {
                                    suspiciousNode = false;
                                    break;
                                }
                            if (!suspiciousNode)
                                break;
                        }
                    if (this.distancesLeafL.size() != 0 && this.distancesLeafU.size() != 0)
                        for (int l : this.distancesLeafL) {
                            for (int u : this.distancesLeafU)
                                if (l + u == k) {
                                    suspiciousNode = false;
                                    break;
                                }
                            if (!suspiciousNode)
                                break;
                        }
                    if (this.distancesLeafR.size() != 0 && this.distancesLeafU.size() != 0)
                        for (int r : this.distancesLeafR) {
                            for (int u : this.distancesLeafU)
                                if (r + u == k) {
                                    suspiciousNode = false;
                                    break;
                                }
                            if (!suspiciousNode)
                                break;
                        }
                    //distances
                    for (int d : this.distancesNodes)
                        if (d >= k) {
                            suspiciousNode = false;
                            break;
                        }
                }
                else
                    suspiciousNode = false;
            }
            //check
            if (suspiciousNode)
                suspiciousNodes.add(this.info);
        }
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

    public static void main(String[]args) {
        new Thread(null, new individualTree35(), "", 64 * 1024 * 1024).start();
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(new FileReader("tst.in"));
            BufferedWriter out = new BufferedWriter(new FileWriter("tst.out"));
            ArrayList<individualTree35> treesArray = new ArrayList<>();
            int k;
            String line = in.readLine();
            k = Integer.parseInt(line);
            line = in.readLine();
            individualTree35 tree;
            if (line != null) {
                int r = Integer.parseInt(line);
                tree = new individualTree35(r);
                treesArray.add(tree);
                while ((line = in.readLine()) != null)
                    tree.add(Integer.parseInt(line), treesArray);
                if (k > 0) {
                    tree.reversTraversalDistances(treesArray);
                    tree.treesCheck(k, treesArray);
                    if (suspiciousNodes.size() != 0) {
                        suspiciousNodes.sort(Collections.reverseOrder());
                        tree = tree.delete(suspiciousNodes.get(0));
                        if (tree == null) {
                            out.write("Empty");
                            out.flush();
                        }
                    }
                    if (tree != null)
                        tree.leftTraversal(out);
                }
                else {
                    tree.leftTraversal(out);
                }
            }
            else {
                out.write("Empty");
                out.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}