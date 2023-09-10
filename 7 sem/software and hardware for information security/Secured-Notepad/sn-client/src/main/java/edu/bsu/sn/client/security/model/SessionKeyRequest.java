package edu.bsu.sn.client.security.model;

import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class SessionKeyRequest {
    private byte[] publicKey;
    private String username;
}
