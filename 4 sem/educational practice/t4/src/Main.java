import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.standard.OrientationRequested;
import javax.print.attribute.standard.Sides;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import java.io.*;
import java.util.ArrayList;

public class Main extends JFrame implements Printable {

    private Main() {
        initComponents();
        this.setTitle("Witch Of Agnesi");
        this.setSize(600, 600);
        File f = new File("src");
        /*if (f.exists()) {
            System.out.println(f.getAbsolutePath());
        }*/
        textLines = creatingTextLines(new File("C:\\Users\\aowl2\\OneDrive\\Рабочий стол\\bsu\\4 s\\ep\\t4\\src\\qua.txt"));
    }

    private void initComponents() {
        JPanel jPanel1 = new JPanel() {
            @Override
            public void paintComponent(Graphics g) {
                Graphics2D graphics2D = (Graphics2D) g;
                graphics2D.setColor(Color.BLACK);
                graphics2D.fillRect(0, 0, this.getWidth(), this.getHeight());
                graphics2D.setColor(new Color(0, 120, 95));
                graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                graphics2D.setStroke(new MyStroke(2f));
                graphics2D.draw(new WitchOfAgnesi(150, getWidth() / 2, getHeight() / 2));

            }
        };
        JMenuBar jMenuBar1 = new JMenuBar();
        JMenu jMenu2 = new JMenu();
        JMenuItem jMenuItem1 = new JMenuItem();

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        jPanel1.setBackground(Color.BLACK);

        GroupLayout jPanel1Layout = new GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
                jPanel1Layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGap(0, 400, Short.MAX_VALUE)
        );
        jPanel1Layout.setVerticalGroup(
                jPanel1Layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGap(0, 279, Short.MAX_VALUE)
        );

        jMenu2.setText("Menu");

        jMenuItem1.setText("Print");
        jMenuItem1.addActionListener(this::jMenuItem1ActionPerformed);
        jMenu2.add(jMenuItem1);

        jMenuBar1.add(jMenu2);

        setJMenuBar(jMenuBar1);

        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(jPanel1, GroupLayout.DEFAULT_SIZE,
                                GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(jPanel1, GroupLayout.DEFAULT_SIZE,
                                GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }

    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {
        PrinterJob job = PrinterJob.getPrinterJob();
        PrintRequestAttributeSet printRequestAttributeSet = new HashPrintRequestAttributeSet();
        printRequestAttributeSet.add(Sides.DUPLEX);
        printRequestAttributeSet.add(OrientationRequested.LANDSCAPE);

        job.setPrintable(this);
        boolean ok = job.printDialog(printRequestAttributeSet);
        if (ok) {
            try {
                job.print(printRequestAttributeSet);
            } catch (PrinterException ex) {
                System.err.print(ex);
            }
        }

    }

    public static void main(String args[]) throws ClassNotFoundException, UnsupportedLookAndFeelException, InstantiationException, IllegalAccessException {
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        EventQueue.invokeLater(() -> new Main().setVisible(true));
    }

    private String[] textLines;
    private int[] pageBreaks;
    @Override
    public int print(Graphics graphics, PageFormat pageFormat, int pageIndex) throws PrinterException {
        int y = 0;
        Font font = new Font("Times New Roman", Font.PLAIN, 14);
        FontMetrics metrics = graphics.getFontMetrics(font);
        int lineHeight = metrics.getHeight();
        //int symbolWidth = metrics.get
        //int lineHeight = 8;
        if (pageIndex == 0) {
            BufferedImage bufferedImageAll = new BufferedImage(this.getWidth(), this.getHeight(),
                    BufferedImage.TYPE_INT_RGB);
            Graphics2D graphics2DForImage = bufferedImageAll.createGraphics();
            this.printAll(graphics2DForImage);

            double scale = pageFormat.getWidth() / this.getWidth();
            int newWidth = (int) (this.getWidth() * scale / 3);
            int newHeight = (int) (this.getHeight() * scale / 3);
            graphics.drawString("Рис. 1 - Witch of Agnesi", getX() + getWidth() / 2 + 75, getY() + getHeight() / 2 + 80);
//            b = bufferedImageAll;
            Image scaledImage = bufferedImageAll.getScaledInstance(newWidth, newHeight, Image.SCALE_SMOOTH);
            graphics.drawImage(scaledImage,
                    (int) (pageFormat.getImageableWidth() / 2 - 75), //подгод для центрирования по горизонтали
                    (int) (pageFormat.getImageableHeight() / 60), null);

            return PAGE_EXISTS;
        }

        //int symbolNums;
        if (pageBreaks == null) {
            //System.out.println(textLines.length);
            int linesPerPage = (int) (pageFormat.getImageableHeight() / lineHeight);
            int numBreaks = (textLines.length - 1) / linesPerPage + 1;
            //System.out.println(numBreaks);
            pageBreaks = new int[numBreaks];
            //symbolNums = pageFormat.getImageableWidth() / metrics.getWidth();
            for (int b = 0; b < numBreaks; b++) {
                pageBreaks[b] = b * linesPerPage;
            }
        }

        if (pageIndex > pageBreaks.length) {
            return NO_SUCH_PAGE;
        }

        Graphics2D g2D = (Graphics2D) graphics;
        g2D.translate(pageFormat.getImageableX(), pageFormat.getImageableY());
        //int start = (pageIndex == 1) ? 0 : pageBreaks[pageIndex - 1];
        int start = pageBreaks[pageIndex - 1];
        int end = (pageIndex == pageBreaks.length) ? textLines.length : pageBreaks[pageIndex];
        for (int line = start; line < end; line++) {
            y += lineHeight;
            //System.out.println(y);
            graphics.drawString(textLines[line], 0, y);
        }
        return PAGE_EXISTS;
    }

    private String[] creatingTextLines(File file) {
        ArrayList<String> result = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                result.add(line);
            }
        } catch (FileNotFoundException ex) {
            //System.out.println("file not found");
            return null;
        } catch (IOException e) {
            //System.err.println(e.getMessage());
        }
        return result.toArray(new String[result.size()]);
    }
}