/*
import java.io.*;
import javafx.application.Application;
import javafx.stage.Stage;

public class Tree02 implements Runnable{
    Integer info;
    Tree02 left;
    Tree02 right;

    public Tree02() {
        this.info = null;
        this.left = null;
        this.right = null;
    }

    public Tree02(int n) {
        this.info = n;
        this.left = null;
        this.right = null;
    }

    public void add(int n) {
        if (this.info == null)
            this.info = n;
        else {
            if (n < this.info) {
                if (this.left == null)
                    this.left = new Tree02(n);
                else {
                    assert false;
                    this.left.add(n);
                }
            } else if (n > this.info) {
                if (this.right == null)
                    this.right = new Tree02(n);
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
        }
        else{
            assert false;
            w.write(this.info.toString() + '\n');
            w.flush();
            if (this.left != null)
                this.left.leftTraversal(w);
            if (this.right != null)
                this.right.leftTraversal(w);
        }
    }

    private int findMin(){
        if (this.left != null)
            return this.left.findMin();
        else
            return this.info;
    }

    private boolean find(int n){
        if (this.info == null)
            return false;
        if (this.info == n)
            return true;
        else {
            if (n > this.info) {
                if (this.right == null)
                    return false;
                return this.right.find(n);
            }
            else {
                if (this.left == null)
                    return false;
                return this.left.find(n);
            }
        }
    }

    public Tree02 delete(int n){
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
        }
        else
            return this;
    }

    public static void main(String[]args) {
        new Thread(null, new Tree02(), "", 64 * 1024 * 1024).start();
    }

    public void run() {
        BufferedReader in = null;
        try {
            in = new BufferedReader(new FileReader("input.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("output.txt"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        int del = 0;
        try {
            assert in != null;
            del = Integer.parseInt(in.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }

        String line = null;
        try {
            in.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        Tree02 tree = null;
        try {
            tree = new Tree02(Integer.parseInt(in.readLine()));
        } catch (IOException e) {
            e.printStackTrace();
        }
        while(true) {
            try {
                if ((line = in.readLine()) == null) break;
            } catch (IOException e) {
                e.printStackTrace();
            }
            assert tree != null;
            assert line != null;
            tree.add( Integer.parseInt(line));
        }
        assert tree != null;
        Tree02 treeAfter = tree.delete(del);
        if (treeAfter == null) {
            try {
                tree.leftTraversal(out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        else {
            try {
                treeAfter.leftTraversal(out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}*/
