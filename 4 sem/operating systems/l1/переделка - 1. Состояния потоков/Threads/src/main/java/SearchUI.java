import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class SearchUI extends JFrame {

    private static final int DEFAULT_WIDTH = 800;
    private static final int DEFAULT_HEIGHT = 600;

    private final JBeginPanel beginPanel;
    private final JUIPanel uiPanel;

    private SearchThread parentThread;

    private List<String> filesStrings = new ArrayList<>();

    public SearchUI(String title, SearchThread parentThread) {
        this(title, DEFAULT_WIDTH, DEFAULT_HEIGHT, parentThread);
    }

    public SearchUI(String title, int w, int h, SearchThread parentThread) {
        super(title);
        this.beginPanel = new JBeginPanel(parentThread);
        this.uiPanel = new JUIPanel(parentThread);
        this.parentThread = parentThread;
        setSize(w, h);
        add(this.beginPanel);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setVisible(true);
    }

    public void setup() {
        add(this.beginPanel);
        revalidate();
        repaint();
    }

    public void showStatus() {
        remove(this.beginPanel);
        add(this.uiPanel);
        revalidate();
        repaint();
    }

    public void updateCorrectFiles(List<String> results) {
        filesStrings.clear();
        filesStrings.addAll(results);
        uiPanel.updateText(filesStrings);
    }

    @Override
    public void dispose() {
        super.dispose();
        parentThread.kill();
    }

    public String getFormat() {
        return uiPanel.getFormat();
    }

    public boolean useSubDirs() {
        return uiPanel.useSubDirs();
    }

    public boolean findFiles() {
        return uiPanel.findFiles();
    }

    public boolean findDirs() {
        return uiPanel.findDirs();
    }

    public int getMaxDpth() {
        return uiPanel.getMaxDpth();
    }
}
