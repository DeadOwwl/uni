package edu.bsu.sn.client.utils;

import lombok.Data;

/**
 * @author svku0919
 * @version 26.09.2020
 */

@Data
public class Holder<T> {
    private T value;
}
