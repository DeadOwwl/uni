import javax.swing.*;
import javax.swing.border.BevelBorder;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.dnd.*;
import java.awt.event.*;
import java.util.ArrayList;

public class DecDragAndDrop extends JComponent implements
        DragGestureListener,
        DragSourceListener,
        DropTargetListener,
        MouseListener,
        MouseMotionListener
{

    private static final long serialVersionUID = 1L;
    private final ArrayList<WitchOfAgnesi> witches = new ArrayList<>();
    private WitchOfAgnesi beingDragged;
    private boolean dragMode;
    private static final int LINE_WIDTH = 2;
    private static final BasicStroke LINE_STYLE = new BasicStroke(LINE_WIDTH);
    private static final Border NORMAL_BORDER = new BevelBorder(BevelBorder.LOWERED);
    private static final Border DROP_BORDER = new BevelBorder(BevelBorder.RAISED);

    private DecDragAndDrop() {
        setBorder(NORMAL_BORDER);
        addMouseListener(this);
        addMouseMotionListener(this);
        DragSource dragSource = DragSource.getDefaultDragSource();
        dragSource.createDefaultDragGestureRecognizer(this,
                DnDConstants.ACTION_COPY_OR_MOVE,
                this);
        DropTarget dropTarget = new DropTarget(this,
                this);
        this.setDropTarget(dropTarget);
    }

    public void paintComponent(Graphics g) {
        Graphics2D g1 = (Graphics2D) g;
        g.setColor(Color.black);
        g.fillRect(0, 0, getWidth(), getHeight());
        g1.setColor(new Color(0, 120, 95));
        g1.setStroke(new MyStroke(2f));
        for (WitchOfAgnesi witch : witches) g1.draw(witch);
        g1.setStroke(LINE_STYLE);
    }

    private void setDragMode(boolean dragMode) {
        this.dragMode = dragMode;
    }

    public void mousePressed(MouseEvent e) {
        if (dragMode) return;
        int param = 100;
        WitchOfAgnesi currentScribble = new WitchOfAgnesi(param, e.getX(), e.getY());
        witches.add(currentScribble);
        repaint();
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }

    public void mouseDragged(MouseEvent e) {
    }

    public void mouseMoved(MouseEvent e) {
    }

    public void dragGestureRecognized(DragGestureEvent e) {
        if (!dragMode) return;
        MouseEvent inputEvent = (MouseEvent) e.getTriggerEvent();
        int x = inputEvent.getX();
        int y = inputEvent.getY();
        Rectangle rectangle = new Rectangle(x - LINE_WIDTH, y - LINE_WIDTH, LINE_WIDTH * 2, LINE_WIDTH * 2);
        for (WitchOfAgnesi witch : witches) {
            if (witch.intersects(rectangle)) {
                beingDragged = witch;
                WitchOfAgnesi dragScribble = (WitchOfAgnesi) witch.clone();
                dragScribble.translate(-x, -y);
                Cursor cursor;
                switch (e.getDragAction()) {
                    case DnDConstants.ACTION_COPY:
                        cursor = DragSource.DefaultCopyDrop;
                        break;
                    case DnDConstants.ACTION_MOVE:
                        cursor = DragSource.DefaultMoveDrop;
                        break;
                    default:
                        return;
                }
                e.startDrag(cursor, dragScribble, this);
                return;
            }
        }
    }

    public void dragDropEnd(DragSourceDropEvent e) {
        if (!e.getDropSuccess()) return;
        int action = e.getDropAction();
        if (action == DnDConstants.ACTION_MOVE) {
            witches.remove(beingDragged);
            beingDragged = null;
            repaint();
        }
    }

    public void dragEnter(DragSourceDragEvent e) {
    }

    public void dragExit(DragSourceEvent e) {
    }

    public void dropActionChanged(DragSourceDragEvent e) {
    }

    public void dragOver(DragSourceDragEvent e) {
    }

    public void dragEnter(DropTargetDragEvent e) {
        //
        if (e.isDataFlavorSupported(WitchOfAgnesi.decDataFlavor) || e.isDataFlavorSupported(DataFlavor.stringFlavor)) {
            e.acceptDrag(DnDConstants.ACTION_COPY_OR_MOVE);
            this.setBorder(DROP_BORDER);
        }
    }

    public void dragExit(DropTargetEvent e) {
        //
        this.setBorder(NORMAL_BORDER);
    }

    public void drop(DropTargetDropEvent e) {
        this.setBorder(NORMAL_BORDER);
        if (e.isDataFlavorSupported(WitchOfAgnesi.decDataFlavor) || e.isDataFlavorSupported(DataFlavor.stringFlavor)) {
            e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
        } else {
            e.rejectDrop();
            return;
        }
        Transferable t = e.getTransferable();
        WitchOfAgnesi droppedScribble;
        try {
            droppedScribble = (WitchOfAgnesi) t.getTransferData(WitchOfAgnesi.decDataFlavor);
        } catch (Exception ex) {
            try {
                String s = (String) t.getTransferData(DataFlavor.stringFlavor);
                droppedScribble = WitchOfAgnesi.getFromString(s);
            } catch (Exception ex2) {
                e.dropComplete(false);
                return;
            }
        }
        Point p = e.getLocation();
        droppedScribble.translate((int) p.getX(), (int) p.getY());
        witches.add(droppedScribble);
        repaint();
        e.dropComplete(true);
    }

    public void dragOver(DropTargetDragEvent e) {
    }

    public void dropActionChanged(DropTargetDragEvent e) {
    }

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | UnsupportedLookAndFeelException | IllegalAccessException | InstantiationException e) {
            System.err.println(e.getMessage());
        }
        JFrame frame = new JFrame("Task #6 by dead.owwl");
        frame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        final DecDragAndDrop scribblePane = new DecDragAndDrop();
        frame.getContentPane().add(scribblePane, BorderLayout.CENTER);
        JToolBar toolbar = new JToolBar();
        ButtonGroup group = new ButtonGroup();
        JToggleButton draw = new JToggleButton("Draw");
        JToggleButton drag = new JToggleButton("Drag");
        draw.addActionListener(e -> scribblePane.setDragMode(false));
        drag.addActionListener(e -> scribblePane.setDragMode(true));
        group.add(draw);
        group.add(drag);
        toolbar.add(draw);
        toolbar.add(drag);
        frame.getContentPane().add(toolbar, BorderLayout.NORTH);
        draw.setSelected(true);
        scribblePane.setDragMode(false);
        frame.setSize(640, 720);
        frame.setVisible(true);
    }
}