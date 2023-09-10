import math
import random
import numpy as np


def is_coprime(x, y):
    k = math.gcd(x, y)
    if math.gcd(x, y) == 1:
        return True
    else:
        return False


def contains_all(string, substring):
    return set(substring) <= set(string)


def egcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        g, y, x = egcd(b % a, a)
        return g, x - (b // a)


def modular_inverse(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        return -1
    else:
        return x % m


# ciphers


def shift_cipher(alphabet, ciphertext, key, operation):
    ans = ''
    int_key = alphabet.index(key)
    m = len(alphabet)
    if operation == 'ENCRYPT':
        for i in ciphertext:
            place = alphabet.index(i)
            new_place = (place + int_key) % m
            ans += alphabet[new_place]
    elif operation == 'DECRYPT':
        for i in ciphertext:
            place = alphabet.index(i)
            new_place = (place - int_key + m) % m
            ans += alphabet[new_place]
    return ans


def affine_cipher(alphabet, ciphertext, key, operation):
    ans = ''
    a = alphabet.index(key[0])
    b = alphabet.index(key[1])
    if is_coprime(a, b) is False:
        return 'ERROR: KEY CODES FOR AFFINE CIPHER ARE NOT COPRIME NUMBERS'
    m = len(alphabet)
    if operation == 'ENCRYPT':
        for i in ciphertext:
            x = alphabet.index(i)
            ex = (a * x + b) % m
            ans += alphabet[ex]
    elif operation == 'DECRYPT':
        a_inverse = modular_inverse(a, m)
        if a_inverse == -1:
            return 'ERROR: MODULAR INVERSE FIRST KEY FOR AFFINE CIPHER DOES NOT EXISTS'
        else:
            for i in ciphertext:
                x = alphabet.index(i)
                dx = a_inverse * (x - b) % m
                ans += alphabet[dx]
    return ans


def simple_substitution_cipher(alphabet, ciphertext, key, operation):
    ans = ''
    if operation == 'ENCRYPT':
        for i in ciphertext:
            ans += key[alphabet.index(i)]
    elif operation == 'DECRYPT':
        for i in ciphertext:
            ans += alphabet[key.index(i)]
    return ans


# key: бвгж
def hill_cipher(alphabet, ciphertext, key, operation):
    ans = ''
    key_matrix = np.array([[alphabet.index(key[0]), alphabet.index(key[1])],
                          [alphabet.index(key[2]), alphabet.index(key[3])]], dtype=np.int64)
    m = len(alphabet)
    det = round(np.linalg.det(key_matrix))
    if det == 0:
        return 'ERROR: DETERMINANT OF THE KEY MATRIX FOR HILL CIPHER EQUALS 0'
    if det < 0:
        while det < 0:
            det += m
        det %= m
    if is_coprime(det, m) is False:
        return 'ERROR: DETERMINANT OF THE KEY MATRIX AND ALPHABET LENGTH FOR HILL CIPHER ARE NOT COPRIME NUMBERS'
    # if modular_inverse(det, m) == -1:
    #     return 'ERROR: DETERMINANT OF THE KEY MATRIX HAS NOT MODULAR INVERSE'
    if len(ciphertext) % 2 == 1:
        ciphertext += alphabet[random.randint(0, m)]
        m += 1

    block_nums = len(ciphertext) // 2
    j = 0
    text_matrix = [[0] * 2] * block_nums
    if operation == 'ENCRYPT':
        for i in range(block_nums):
            open_vector = np.array([alphabet.index(ciphertext[j]), alphabet.index(ciphertext[j + 1])])
            vector_after = np.dot(open_vector, key_matrix) % m
            text_matrix[i] = vector_after
            j += 2
        for i in range(block_nums):
            for k in range(2):
                ans += alphabet[text_matrix[i][k]]
    elif operation == 'DECRYPT':
        inverse_matrix_by_mod = np.array([[key_matrix[1][1], -key_matrix[0][1]],
                                         [-key_matrix[1][0], key_matrix[0][0]]])
        for i in range(2):
            for j in range(2):
                if inverse_matrix_by_mod[i][j] < 0:
                    while inverse_matrix_by_mod[i][j] < 0:
                        inverse_matrix_by_mod[i][j] += m
        # t_inverse_matrix_by_mod = inverse_matrix_by_mod.transpose()
        j = 0
        for i in range(block_nums):
            open_vector = np.array([alphabet.index(ciphertext[j]), alphabet.index(ciphertext[j + 1])])
            vector_after = np.dot(open_vector, inverse_matrix_by_mod) % m
            text_matrix[i] = vector_after
            j += 2
        for i in range(block_nums):
            for k in range(2):
                ans += alphabet[text_matrix[i][k]]
    return ans


def switch_cipher(alphabet, ciphertext, key, operation):
    ans = ''
    if operation == 'ENCRYPT':
        alphabet_len = len(alphabet)
        text_len = len(ciphertext)
        key_len = len(key)
        if text_len % key_len != 0:
            symbol = alphabet[random.randint(0, alphabet_len)]
            difference = key_len - text_len % key_len
            ciphertext += symbol * difference
            text_len = len(ciphertext)
        permutations = [0] * len(key)
        k = 0
        for i in range(len(alphabet)):
            for j in range(len(key)):
                if alphabet[i] == key[j]:
                    permutations[j] = k
                    k += 1
                if k == len(key):
                    break
            if k == len(key):
                break
        blocks_num = text_len // key_len
        j = 0
        ans_array = [' '] * len(ciphertext)
        for t in range(blocks_num):
            for i in range(len(key)):
                ans_array[permutations[i] + j * key_len] = ciphertext[j * key_len + i]
            j += 1
        ans = ans.join(ans_array)
    elif operation == 'DECRYPT':
        alphabet_len = len(alphabet)
        text_len = len(ciphertext)
        key_len = len(key)
        permutations = [0] * key_len
        k = 0
        for i in range(len(alphabet)):
            for j in range(len(key)):
                if alphabet[i] == key[j]:
                    permutations[j] = k
                    k += 1
                if k == len(key):
                    break
            if k == len(key):
                break
        blocks_num = text_len // key_len
        j = 0
        ans_array = [' '] * len(ciphertext)
        for t in range(blocks_num):
            for i in range(len(key)):
                ans_array[j * key_len + i] = ciphertext[permutations[i] + j * key_len]
            j += 1
        ans = ans.join(ans_array)
    return ans


def vigenere_cipher(alphabet, ciphertext, key, operation):
    ans = ''
    m = len(alphabet)
    text_len = len(ciphertext)
    while len(key) < text_len:
        if text_len - len(key) >= len(key):
            key += key
        else:
            for i in range(text_len - len(key)):
                key += key[i]

    if operation == 'ENCRYPT':
        for i in range(text_len):
            ans += alphabet[(alphabet.index(ciphertext[i]) + alphabet.index(key[i])) % m]
    elif operation == 'DECRYPT':
        for i in range(text_len):
            k2 = alphabet.index(key[i])
            ans += alphabet[(alphabet.index(ciphertext[i]) - alphabet.index(key[i]) + m) % m]
    return ans


if __name__ == '__main__':
    alphabet_main = open("C://Users//aowl2//OneDrive//Рабочий стол//bsu//5 s//ct//l1//input data//alphabet.txt", "r",
                         encoding="utf-8").read().upper()
    if alphabet_main == '':
        alphabet_main = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ '
    #if alphabet_main.find(' ', 0, len(alphabet_main)) is not True:
    #    alphabet_main += ' '
    ciphertext_main = open('C://Users//aowl2//OneDrive//Рабочий стол//bsu//5 s//ct//l1//input data//in.txt',
                           'r', encoding="utf-8").read().upper()
    key_main = open('C://Users//aowl2//OneDrive//Рабочий стол//bsu//5 s//ct//l1//input data//key.txt',
                    'r', encoding="utf-8").read().upper()
    op_sys = open('C://Users//aowl2//OneDrive//Рабочий стол//bsu//5 s//ct//l1//input data//operation_and_system.txt', 'r',
                  encoding="utf-8")
    operation_main = op_sys.readline().upper().strip()
    system_main = op_sys.read().upper().strip()
    op_sys.close()

    answer = ''
    if ciphertext_main == '':
        answer = 'ERROR: CIPHER TEXT IS EMPTY STRING'
    elif key_main == '':
        answer = 'ERROR: KEY IS EMPTY STRING'
    elif system_main != 'SHIFT CIPHER' and system_main != 'AFFINE CIPHER' and system_main != 'SIMPLE SUBSTITUTION CIPHER' \
            and system_main != 'HILL CIPHER' and system_main != 'SWITCH CIPHER' and system_main != 'VIGENERE CIPHER':
        answer = 'ERROR: SYSTEM IN NOT AVAILABLE'
    elif contains_all(alphabet_main, key_main) is False:
        answer = 'ERROR: KEY CONTAINS FROM NOT ALPHABET SYMBOLS'
    elif system_main == 'SHIFT CIPHER' and len(key_main) != 1:
        answer = 'ERROR: KEY FOR SHIFT CIPHER SHOULD HAVE LENGTH EQUALS 1'
    elif system_main == 'AFFINE CIPHER' and len(key_main) != 2:
        answer = 'ERROR: KEY FOR AFFINE CIPHER SHOULD HAVE LENGTH EQUALS 2 AND BE THE PAIR OF ALPHABET SYMBOLS'
    elif system_main == 'SIMPLE SUBSTITUTION CIPHER' and set(alphabet_main) != set(key_main):
        answer = 'ERROR: KEY FOR SIMPLE SUBSTITUTION CIPHER SHOULD BE REARRANGEMENT OF ALPHABET'
    elif system_main == 'HILL CIPHER' and len(key_main) != 4:
        answer = 'ERROR: KEY FOR HILL CIPHER SHOULD HAVE LENGTH EQUALS 4 AND CONTAINS OF 4 ALPHABET SYMBOLS'
    elif system_main == 'SWITCH CIPHER' and (len(key_main) != len(set(key_main)) or len(key_main) > len(alphabet_main)):
        answer = 'ERROR: KEY FOR SWITCH CIPHER SHOULD HAVE LENGTH LESS THAN LENGTH OF THE ALPHABET AND CONTAINS OF UNIQUE ALPHABET SYMBOLS'
    elif operation_main != 'ENCRYPT' and operation_main != 'DECRYPT':
        answer = 'ERROR: OPERATION SHOULD HAVE VALUES "ENCRYPT" OR "DECRYPT"'

    if answer == '':
        if system_main == 'SHIFT CIPHER':
            answer = shift_cipher(alphabet_main, ciphertext_main, key_main, operation_main)
        elif system_main == 'AFFINE CIPHER':
            answer = affine_cipher(alphabet_main, ciphertext_main, key_main, operation_main)
        elif system_main == 'SIMPLE SUBSTITUTION CIPHER':
            answer = simple_substitution_cipher(alphabet_main, ciphertext_main, key_main, operation_main)
        elif system_main == 'HILL CIPHER':
            answer = hill_cipher(alphabet_main, ciphertext_main, key_main, operation_main)
        elif system_main == 'SWITCH CIPHER':  # HERE
            answer = switch_cipher(alphabet_main, ciphertext_main, key_main, operation_main)
        elif system_main == 'VIGENERE CIPHER':
            answer = vigenere_cipher(alphabet_main, ciphertext_main, key_main, operation_main)
        if answer.find('ERROR: ') != -1:
            answer = 'SUCCESS: ' + answer
    if operation_main == 'ENCRYPT':
        open('C://Users//aowl2//OneDrive//Рабочий стол//bsu//5 s//ct//l1//output data//encrypt.txt', 'w').write(answer)
    else:
        open('C://Users//aowl2//OneDrive//Рабочий стол//bsu//5 s//ct//l1//output data//decrypt.txt', 'w').write(answer)
