package edu.bsu.sn.client.security.model;

import lombok.Data;
import lombok.experimental.Accessors;

/**
 * @author svku0919
 * @version 30.09.2020
 */
@Data
@Accessors(chain = true)
public class LogInUser {
    private String username;
    private byte[] password;
}
