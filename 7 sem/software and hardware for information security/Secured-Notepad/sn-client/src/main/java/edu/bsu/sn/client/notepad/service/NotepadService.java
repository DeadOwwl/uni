package edu.bsu.sn.client.notepad.service;

import edu.bsu.sn.client.notepad.model.FileContent;
import edu.bsu.sn.client.notepad.model.UserFiles;
import edu.bsu.sn.client.notepad.model.UserFilesResponse;
import edu.bsu.sn.client.security.model.LogInUser;
import edu.bsu.sn.client.security.service.SecurityService;
import edu.bsu.sn.client.web.client.SecuredNotepadClient;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

/**
 * @author svku0919
 * @version 26.09.2020
 */

@Service
@RequiredArgsConstructor
public class NotepadService {
    private final SecurityService securityService;
    private final SecuredNotepadClient securedNotepadClient;

    public FileContent getFileContent(String fileName, String username) {
        FileContent fileContent = securedNotepadClient.getFileContent(fileName, username);
        String decryptedContent = securityService.decryptText(fileContent.getFileContent());
        return fileContent.setFileContent(decryptedContent);
    }

    public UserFiles getUserFiles(String username) {
        UserFilesResponse userFilesResponse = securedNotepadClient.getUserFiles(username);
        final String decryptedFilesList = securityService.decryptText(userFilesResponse.getUserFiles());
        final List<String> filesList = Arrays.stream(decryptedFilesList.split(",")).collect(Collectors.toList());
        return new UserFiles().setFileNames(filesList);
    }

    public boolean deleteUserFile(String fileName, String username) {
        return securedNotepadClient.deleteUserFile(fileName, username);
    }

    public FileContent updateUserFile(FileContent fileContent) {
        String encryptedContent = securityService.encryptText(fileContent.getFileContent());
        fileContent.setFileContent(encryptedContent);
        final FileContent updatedUserFile = securedNotepadClient.updateUserFile(fileContent);
        updatedUserFile.setFileContent(securityService.decryptText(updatedUserFile.getFileContent()));
        return updatedUserFile;
    }

    public FileContent addUserFile(String fileName, String username) {
        return securedNotepadClient.addUserFile(fileName, username);
    }

    public LogInUser getSessionKey(String username) {
        return securityService.getSessionKey(username);
    }

    public boolean logIn(LogInUser logInUser) {
        return securityService.logIn(logInUser);
    }
}
