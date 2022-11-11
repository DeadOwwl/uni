import javax.swing.*;
import java.nio.file.Path;

public class Main {

    private static final int THREADS_COUNT = 2;

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

    public static void main(String[] args) {
        //Path startDirectory = initStartDirectoryPath();
        for (int i = 0; i < THREADS_COUNT; i++) {
            new SearchThread("Thread-" + i).start();
        }
    }
}
