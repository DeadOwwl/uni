import javax.swing.*;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class SearchThread extends Thread {

    private static final int DELAY = 1000 / 3;

    private final String title;

    private final SearchUI searchUI;

    private final List<String> results = new LinkedList<>();
    private boolean result_locked = false;
    private boolean copying_result = false;

    private boolean alive = true;

    private Path startDir = null;
    private boolean waitForStartDir;

    public SearchThread(String title, Path startDir) {
        this.title = title;
        this.startDir = startDir;
        waitForStartDir = false;
        searchUI = new SearchUI(title, this);
    }

    public SearchThread(String title) {
        this.title = title;
        waitForStartDir = true;
        searchUI = new SearchUI(title, this);
        searchUI.setup();
    }

    public void setStartDir(Path startDir) {
        waitForStartDir = true;
        this.startDir = startDir;
        waitForStartDir = false;
        searchUI.showStatus();
    }

    public void kill() {
        this.alive = false;
    }

    @Override
    public void run() {
        super.run();
        while (alive) {
            while(waitForStartDir && alive){
                System.err.println("wait");
            }
            if (!alive)
                break;
            try {
                while(copying_result) { }
                result_locked = true;
                results.clear();
                DirectoryWalker.getInstance(results, startDir, searchUI.getFormat(), searchUI.useSubDirs(), searchUI.findDirs(), searchUI.findFiles(), searchUI.getMaxDpth());
                searchUI.updateCorrectFiles(results);
                result_locked = false;
                Thread.sleep(DELAY);
            } catch (Exception ex) {
                System.err.println(ex);
            }
        }
        alive = false;
        JOptionPane.showMessageDialog(null, "Поток " + title + " завершился.", title, JOptionPane.INFORMATION_MESSAGE);
    }

    List<String> getResult() {
        while (result_locked) {}
        copying_result = true;
        List<String> paths = new ArrayList<>();
        paths.addAll(results);
        copying_result = false;
        return paths;
    }
}
