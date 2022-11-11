import javax.swing.*;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class SearchThread extends Thread {

    private static final int DELAY = 1000 / 3;

    private String title;

    private SearchUI searchUI;

    private List<String> results = new LinkedList<>();
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

    public String getTitle() {
        return title;
    }

    private boolean processed = false;

    public boolean isProcessed() {
        return processed;
    }

    public void update() {
        processed = false;
    }

    private DirectoryWalker lastDirectoryWalker;

    @Override
    public void run() {
        super.run();
        while (alive) {
            while (processed && alive) {
                if (lastDirectoryWalker.isfDirs() != searchUI.findDirs())
                    processed = false;
                if (lastDirectoryWalker.isfFiles() != searchUI.findFiles())
                    processed = false;
                if (lastDirectoryWalker.isUseSubDirs() != searchUI.useSubDirs())
                    processed = false;
                if (lastDirectoryWalker.getMaxDepth() != searchUI.getMaxDpth())
                    processed = false;
                if (!lastDirectoryWalker.getRegex().equals(searchUI.getFormat()))
                    processed = false;
                System.err.println("stay");
            }
            while(waitForStartDir && alive){
                System.err.println("wait");
            }
            if (!alive)
                break;
            try {
                while(copying_result) {

                }
                result_locked = true;
                results.clear();
                lastDirectoryWalker = DirectoryWalker.getInstance(results, startDir, searchUI.getFormat(), searchUI.useSubDirs(), searchUI.findDirs(), searchUI.findFiles(), searchUI.getMaxDpth());
                searchUI.updateCorrectFiles(results);
                result_locked = false;
                Thread.sleep(DELAY);
            } catch (Exception ex) {
                System.err.println(ex);
            }
            processed = true;
        }
        processed = true;
        JOptionPane.showMessageDialog(null, "Поток " + title + " завершился.", title, JOptionPane.INFORMATION_MESSAGE);
    }

    List<String> getResult() {
        while (result_locked) {

        }
        copying_result = true;
        List<String> paths = new ArrayList<>();
        paths.addAll(results);
        copying_result = false;
        return paths;
    }

}
