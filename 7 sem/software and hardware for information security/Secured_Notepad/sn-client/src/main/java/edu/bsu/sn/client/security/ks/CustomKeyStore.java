package edu.bsu.sn.client.security.ks;

import lombok.Getter;
import lombok.SneakyThrows;
import org.springframework.stereotype.Component;

import javax.crypto.Cipher;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.PublicKey;

@Getter
@Component
public class CustomKeyStore {
    private final Cipher cipherAESDecryption;
    private final Cipher cipherAESEncryption;
    private final Cipher cipherRSA;
    private final PublicKey publicKey;

    @SneakyThrows
    public CustomKeyStore() {
        KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
        keyPairGenerator.initialize(4096);
        KeyPair keyPair = keyPairGenerator.generateKeyPair();

        cipherRSA = Cipher.getInstance("RSA/ECB/PKCS1Padding");
        cipherRSA.init(Cipher.DECRYPT_MODE, keyPair.getPrivate());

        cipherAESDecryption = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipherAESEncryption = Cipher.getInstance("AES/CBC/PKCS5Padding");

        publicKey = keyPair.getPublic();
    }
}
