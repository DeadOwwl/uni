package edu.bsu.sn.client.notepad.model;

import lombok.Data;
import lombok.experimental.Accessors;

/**
 * @author svku0919
 * @version 27.09.2020
 */

@Data
@Accessors(chain = true)
public class UserFilesResponse {
    private String userFiles;
}
