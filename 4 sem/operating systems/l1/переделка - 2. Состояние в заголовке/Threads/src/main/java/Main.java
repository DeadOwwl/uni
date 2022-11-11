/*
import javax.swing.*;
import java.awt.*;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final int THREADS_COUNT = 3;

    public static Path initStartDirectoryPath() throws Exception {
        JFileChooser jFileChooser = new JFileChooser();
        jFileChooser.setDialogTitle("Выберите главную директорию поиска.");
        jFileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        int result = jFileChooser.showOpenDialog(null);
        if (result == JFileChooser.APPROVE_OPTION) {
            //System.err.println(jFileChooser.getSelectedFile().toPath());
            return jFileChooser.getSelectedFile().toPath();
        } else {
            JOptionPane.showMessageDialog(null, "Что-то пошло не так.", "Ошибка", JOptionPane.ERROR_MESSAGE);
            throw new Exception();
        }
    }

    private static class Monitor extends Thread {
        List<SearchThread> threads = new ArrayList<>();

        public void addThread(SearchThread thread) {
            threads.add(thread);
        }

        private boolean isSmthAlive() {
            boolean alive = false;
            for (SearchThread thread : threads)
                alive |= thread.isAlive();
            return alive;
        }

        @Override
        public void run() {
            super.run();

            while (isSmthAlive()) {
                for (SearchThread thread : threads)
                try {
                    for (SearchThread searchThread : threads)
                        searchThread.update();
                    Thread.sleep(100);
                } catch (InterruptedException ex) {

                }
            }
        }
    }

    public static void main(String[] args) {
        //Path startDirectory = initStartDirectoryPath();
        Monitor monitor = new Monitor();
        for (int i = 0; i < THREADS_COUNT; i++) {
            SearchThread searchThread = new SearchThread("Thread-" + i);
            searchThread.start();
            monitor.addThread(searchThread);
        }
        monitor.start();
    }
}
*/
