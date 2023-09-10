package edu.bsu.sn.client.notepad.model;

import lombok.Data;
import lombok.experimental.Accessors;

/**
 * @author svku0919
 * @version 26.09.2020
 */

@Data
@Accessors(chain = true)
public class FileContent {
    private String fileContent;
    private String fileName;
    private String username;
}
