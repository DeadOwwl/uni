package Model;

import java.awt.*;
import javax.swing.*;

public class FontFrame extends JDialog {
    String family;
    int style;
    int size;
    Font selectedFont;

    String[] fontFamilies;

    ItemFrame families, styles, sizes;
    JTextArea preview;
    JButton okay, cancel;

    static final String[] styleNames = new String[] {"Plain", "Italic", "Bold", "BoldItalic"};

    static final Integer[] styleValues = new Integer[] {Font.PLAIN, Font.ITALIC, Font.BOLD, Font.BOLD + Font.ITALIC};

    static final String[] sizeNames = new String[] {"8", "10", "12", "14", "18", "20", "24", "28", "32", "40", "48", "56", "64", "72"};

    static final String defaultPreviewString =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n" + "abcdefghijklmnopqrstuvwxyz\n" + "1234567890!@#$%^&*()_-=+[]{}<,.>\n" +
                    "The quick brown fox jumps over the lazy dog";

    public FontFrame(GFrame owner) {
        super(owner, "Choose a Font");
        setModal(true);
        GraphicsEnvironment env = GraphicsEnvironment.getLocalGraphicsEnvironment();
        fontFamilies = env.getAvailableFontFamilyNames();
        family = fontFamilies[0];
        style = Font.PLAIN;
        size = 20;
        selectedFont = new Font(family, style, size);
        families = new ItemFrame("Family", fontFamilies, null, 0, ItemFrame.COMBOBOX);
        styles = new ItemFrame("Style", styleNames, styleValues, 0, ItemFrame.COMBOBOX);
        sizes = new ItemFrame("Size", sizeNames,null,4,ItemFrame.COMBOBOX);
        families.addItemChooserListener(e -> setFontFamily((String)e.getSelectedValue()));
        styles.addItemChooserListener(e -> setFontStyle((Integer) e.getSelectedValue()));
        sizes.addItemChooserListener(e -> setFontSize(Integer.parseInt((String)e.getSelectedValue())));
        preview = new JTextArea(defaultPreviewString, 5, 40);
        preview.setFont(selectedFont);
        okay = new JButton("Okay");
        cancel = new JButton("Cancel");
        okay.addActionListener(e -> setVisible(false));
        cancel.addActionListener(e -> {
            selectedFont = null;
            setVisible(false);
        });

        Box choosersBox = Box.createHorizontalBox();
        choosersBox.add(Box.createHorizontalStrut(15));
        choosersBox.add(families);
        choosersBox.add(Box.createHorizontalStrut(15));
        choosersBox.add(styles);
        choosersBox.add(Box.createHorizontalStrut(15));
        choosersBox.add(sizes);
        choosersBox.add(Box.createHorizontalStrut(15));
        choosersBox.add(Box.createGlue());

        Box buttonBox = Box.createHorizontalBox();
        buttonBox.add(Box.createGlue());
        buttonBox.add(okay);
        buttonBox.add(Box.createGlue());
        buttonBox.add(cancel);
        buttonBox.add(Box.createGlue());

        Container contentPane = getContentPane();
        contentPane.add(new JScrollPane(preview), BorderLayout.CENTER);
        contentPane.add(choosersBox, BorderLayout.NORTH);
        contentPane.add(buttonBox, BorderLayout.SOUTH);

        pack();
    }
    public Font getSelectedFont() { return selectedFont; }

    public void setFontFamily(String name) {
        family = name;
        changeFont();
    }
    public void setFontStyle(int style) {
        this.style = style;
        changeFont();
    }
    public void setFontSize(int size) {
        this.size = size;
        changeFont();
    }

    protected void changeFont() {
        selectedFont = new Font(family, style, size);
        preview.setFont(selectedFont);
    }

    public boolean isModal() { return true; }
}

