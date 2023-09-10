package edu.bsu.sn.client.console.processor;

import edu.bsu.sn.client.console.view.ConsoleView;
import edu.bsu.sn.client.notepad.model.FileContent;
import edu.bsu.sn.client.notepad.model.UserFiles;
import edu.bsu.sn.client.notepad.service.NotepadService;
import edu.bsu.sn.client.security.model.LogInUser;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.Objects;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * @author svku0919
 * @version 27.09.2020
 */
@Component
public class ConsoleProcessor {
    private final NotepadService notepadService;
    private final ConsoleView consoleView;
    private final HashMap<String, Runnable> commands;
    private boolean closeConsole;
    private String currentUsername;

    public ConsoleProcessor(NotepadService notepadService, ConsoleView consoleView) {
        this.notepadService = notepadService;
        this.consoleView = consoleView;
        this.commands = new HashMap<>();

        commands.put(ConsoleView.LOGIN, this::login);
        commands.put(ConsoleView.GET_FILE, this::getFile);
        commands.put(ConsoleView.GET_FILES, this::getFiles);
        commands.put(ConsoleView.DELETE_FILE, this::deleteFile);
        commands.put(ConsoleView.UPDATE_FILE, this::updateFile);
        commands.put(ConsoleView.ADD_FILE, this::addFile);
        commands.put(ConsoleView.LOGOUT, this::logout);
        commands.put(ConsoleView.HELP, this::help);
        commands.put(ConsoleView.EXIT, this::exit);

        closeConsole = false;
        currentUsername = "";
    }

    public void runConsole() {
        Scanner input = new Scanner(System.in);

        consoleView.printHelp();

        String line;
        StringTokenizer tokenizer;

        while (!closeConsole) {
            try {
                line = input.nextLine();
                if (!line.equals("")) {
                    tokenizer = new StringTokenizer(line);
                    final String nextToken = tokenizer.nextToken();
                    commands.get(nextToken).run();
                }
            } catch (Exception e) {
                consoleView.printError(e);
            }
        }

        System.exit(0);
    }


    public void login() {
        currentUsername = consoleView.askForUsername();
        LogInUser logInUser = notepadService.getSessionKey(currentUsername);
        if (Objects.isNull(logInUser.getPassword())) {
            byte[] password = consoleView.askForPassword();
            if (!notepadService.logIn(logInUser.setPassword(password))) {
                throw new RuntimeException("Wrong password or something went wrong. Try again later!");
            }
            consoleView.printStr("You successfully logged in!");
            return;
        }
        consoleView.viewUserData(logInUser);
        consoleView.printStr("You successfully logged in!");
    }

    public void getFile() {
        checkLoginStatus();
        String filename = consoleView.askForFileName();
        FileContent fileContent = notepadService.getFileContent(filename, currentUsername);
        consoleView.viewFile(fileContent);
    }

    public void getFiles() {
        checkLoginStatus();
        final UserFiles userFiles = notepadService.getUserFiles(currentUsername);
        consoleView.viewFiles(userFiles);
    }

    public void deleteFile() {
        checkLoginStatus();
        String filename = consoleView.askForFileName();
        notepadService.deleteUserFile(filename, currentUsername);
    }

    public void updateFile() {
        checkLoginStatus();
        String filename = consoleView.askForFileName();
        FileContent fileContent = notepadService.getFileContent(filename, currentUsername);
        consoleView.viewFileForUpdate(fileContent);
        notepadService.updateUserFile(fileContent);
    }

    public void addFile() {
        checkLoginStatus();
        String filename = consoleView.askForFileName();
        notepadService.addUserFile(filename, currentUsername);
    }

    public void logout() {
        checkLoginStatus();
        currentUsername = "";
    }

    public void exit() {
        closeConsole = true;
    }

    public void help() {
        consoleView.printHelp();
    }

    private void checkLoginStatus() {
        if (currentUsername.equals("")) {
            throw new RuntimeException("Please, login into your account.");
        }
    }
}
