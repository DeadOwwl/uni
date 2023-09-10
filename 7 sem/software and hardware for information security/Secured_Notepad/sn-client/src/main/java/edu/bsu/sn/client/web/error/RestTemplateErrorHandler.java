package edu.bsu.sn.client.web.error;

import org.springframework.http.client.ClientHttpResponse;
import org.springframework.stereotype.Component;
import org.springframework.web.client.ResponseErrorHandler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.stream.Collectors;

/**
 * @author svku0919
 * @version 27.09.2020
 */

@Component
public class RestTemplateErrorHandler implements ResponseErrorHandler {
    @Override
    public void handleError(ClientHttpResponse response) throws IOException {
        String theString = new BufferedReader(new InputStreamReader(response.getBody(), StandardCharsets.UTF_8.name()))
                .lines()
                .collect(Collectors.joining("\n"));
        throw new RuntimeException(theString);
    }

    @Override
    public boolean hasError(ClientHttpResponse clienthttpresponse) throws IOException {
        return !clienthttpresponse.getStatusCode().is2xxSuccessful();
    }

}
