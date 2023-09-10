package edu.bsu.sn.client.security.model;

import lombok.Data;
import lombok.experimental.Accessors;

import java.time.Instant;

/**
 * @author svku0919
 * @version 27.09.2020
 */
@Data
@Accessors(chain = true)
public class SessionKeyAndUser {
    private byte[] aesKey;
    private byte[] ivSpec;
    private byte[] password;
    private Instant expiresIn;
}
