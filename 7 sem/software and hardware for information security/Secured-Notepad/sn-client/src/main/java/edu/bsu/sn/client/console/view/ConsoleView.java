package edu.bsu.sn.client.console.view;

import edu.bsu.sn.client.notepad.model.FileContent;
import edu.bsu.sn.client.notepad.model.UserFiles;
import edu.bsu.sn.client.security.model.LogInUser;
import org.springframework.stereotype.Component;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import java.awt.Dimension;
import java.nio.charset.StandardCharsets;
import java.util.Objects;
import java.util.Scanner;

@Component
public class ConsoleView {
    public static final String LOGIN = "login";
    public static final String GET_FILE = "read";
    public static final String GET_FILES = "list";
    public static final String DELETE_FILE = "delete";
    public static final String UPDATE_FILE = "edit";
    public static final String ADD_FILE = "create";
    public static final String LOGOUT = "logout";
    public static final String HELP = "help";
    public static final String EXIT = "exit";

    private final JFrame jFrame;

    public ConsoleView() {
        jFrame = new JFrame();
        jFrame.setVisible(false);
        jFrame.setAlwaysOnTop(true);
    }

    public void printHelp() {
        System.out.println(
                "Your commands: \n" +
                            "\t"+LOGIN+"          --- войти;\n"+
                            "\t"+ GET_FILE+"       --- содержимое файла;\n"+
                            "\t"+ GET_FILES+"      --- список файлов;\n" +
                            "\t"+DELETE_FILE+"    --- удалить файл;\n" +
                            "\t"+ UPDATE_FILE+"    --- редактировать файл;\n" +
                            "\t"+ ADD_FILE+"       --- создать файл;\n"+
                            "\t"+ LOGOUT+"         --- выйти;\n"+
                            "\t"+ HELP+"           --- помощь\n"+
                            "\t"+ EXIT+"           --- закрыть программу;\n"
        );
    }

    public String askForUsername() {
        System.out.println("Enter username:");
        return new Scanner(System.in).nextLine();
    }

    public String askForFileName() {
        System.out.println("Enter name:");
        return new Scanner(System.in).nextLine();
    }

    public void printError(Exception ignored) {
        System.out.println("Exception are caught with message: " + ignored.getMessage());
    }

    public void viewFile(FileContent fileContent) {
        printStr(fileContent.getFileContent());
    }

    public void viewFiles(UserFiles userFiles) {
        printStr("Files:");
        userFiles.getFileNames().forEach(this::printStr);
    }

    public void viewFileForUpdate(FileContent fileContent) {
        JTextArea textArea = new JTextArea(fileContent.getFileContent());
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);
        textArea.setPreferredSize(new Dimension(500, 500));

        JOptionPane.showMessageDialog(jFrame, new JScrollPane(textArea), fileContent.getFileName(),
                JOptionPane.INFORMATION_MESSAGE);

        fileContent.setFileContent(textArea.getText());
    }

    public void viewUserData(LogInUser logInUser) {
        printStr("Username: "  + logInUser.getUsername());
        printStr("Password: "  + new String(logInUser.getPassword(), StandardCharsets.UTF_8));

    }

    public byte[] askForPassword() {
        printStr("Enter password");
        return new Scanner(System.in).nextLine().getBytes();
    }

    public void printStr(String s) {
        System.out.println(s);
    }
}
