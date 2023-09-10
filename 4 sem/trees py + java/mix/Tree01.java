/*
import java.io.*;
import javafx.application.Application;
import javafx.stage.Stage;

public class Tree01 implements Runnable{
    Integer info;
    Tree01 left;
    Tree01 right;

    public Tree01() {
        this.info = null;
        this.left = null;
        this.right = null;
    }

    public Tree01(int n) {
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
                    this.left = new Tree01(n);
                else {
                    assert false;
                    this.left.add(n);
                }
            } else if (n > this.info) {
                if (this.right == null)
                    this.right = new Tree01(n);
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

    public static void main(String[]args) {
        new Thread(null, new Tree01(), "", 64 * 1024 * 1024).start();
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

        Tree01 tree = null;
        try {
            tree = new Tree01(Integer.parseInt(in.readLine()));
        } catch (IOException e) {
            e.printStackTrace();
        }
        String line = null;
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
        try {
            tree.leftTraversal(out);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}*/
