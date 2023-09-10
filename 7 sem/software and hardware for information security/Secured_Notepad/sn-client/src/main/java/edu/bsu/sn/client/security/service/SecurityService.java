package edu.bsu.sn.client.security.service;

import edu.bsu.sn.client.security.ks.CustomKeyStore;
import edu.bsu.sn.client.security.model.LogInUser;
import edu.bsu.sn.client.security.model.SessionKeyAndUser;
import edu.bsu.sn.client.security.model.SessionKeyRequest;
import edu.bsu.sn.client.web.client.SecuredNotepadClient;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;
import org.springframework.stereotype.Service;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;
import java.util.Objects;

/**
 * @author svku0919
 * @version 26.09.2020
 */

@Service
@RequiredArgsConstructor
public class SecurityService {
    private final CustomKeyStore keyStore;
    private final SecuredNotepadClient securedNotepadClient;

    @SneakyThrows
    public String decryptText(String fileContent) {
        byte[] decrypted = keyStore.getCipherAESDecryption()
                .doFinal(Base64.getDecoder().decode(fileContent.getBytes()));
        return new String(decrypted);
    }

    @SneakyThrows
    public LogInUser getSessionKey(String username) {
        SessionKeyAndUser sessionKeyAndUser = securedNotepadClient.getSessionKey(new SessionKeyRequest()
                .setUsername(username)
                .setPublicKey(keyStore.getPublicKey().getEncoded()));

        byte[] aesKey = keyStore.getCipherRSA().doFinal(sessionKeyAndUser.getAesKey());

        final SecretKeySpec secretKeySpec = new SecretKeySpec(aesKey, "AES");
        final IvParameterSpec ivParameterSpec = new IvParameterSpec(sessionKeyAndUser.getIvSpec());

        keyStore.getCipherAESDecryption().init(Cipher.DECRYPT_MODE, secretKeySpec,
                ivParameterSpec);
        keyStore.getCipherAESEncryption().init(Cipher.ENCRYPT_MODE, secretKeySpec,
                ivParameterSpec);

        if (Objects.nonNull(sessionKeyAndUser.getPassword())) {
            return new LogInUser()
                    .setPassword(keyStore.getCipherAESDecryption().doFinal(sessionKeyAndUser.getPassword()))
                    .setUsername(username);
        }
        return new LogInUser().setUsername(username);
    }

    @SneakyThrows
    public boolean logIn(LogInUser logInUser) {
        logInUser.setPassword(keyStore.getCipherAESEncryption().doFinal(logInUser.getPassword()));
        return securedNotepadClient.logIn(logInUser);
    }

    @SneakyThrows
    public String encryptText(String fileContent) {
        byte[] decrypted = keyStore.getCipherAESEncryption()
                .doFinal(fileContent.getBytes());
        return Base64.getEncoder().encodeToString(decrypted);
    }
}
