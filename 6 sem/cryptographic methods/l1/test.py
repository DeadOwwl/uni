import rsa
import math


def RSA(bytes_len: int, message: str):
    print(f'l: {bytes_len}')
    print(f'char message: {message}')

    n_main, e_main, d_main, p_main, q_main = rsa.gen(bytes_len)
    print(f'n: {n_main},\ne: {e_main},\nd: {d_main},\np: {p_main},\nq: {q_main}')

    unicode_message = [ord(letter) for letter in message]
    print(f'unicode message: {unicode_message}')

    encr_result = [rsa.encr(elem, e_main, n_main) for elem in unicode_message]
    print(f'encrypted message: {encr_result}')

    decr_result = [rsa.decr(elem, d_main, p_main, q_main) for elem in encr_result]
    print(f'decrypted message: {decr_result}')

    char_message = [chr(letter) for letter in decr_result]
    char_message_joined = ''.join(char_message)
    print(f'decrypted char message: {char_message_joined}')


def main():
    print('-Viability RSA test-')
    RSA(bytes_len=8,
        message=''' Fumareta hana no namae mo shirazu ni
                    Chi ni ochita tori wa kaze o machiwabiru
                    Inotta tokoro de nani mo kawaranai
                    Ima o kaeru no wa tatakau kakugo da''')

    print('\n-Extended Euclidean algorithm test-')
    ex_eu_test = (10, 17)
    print(f'a, m: {ex_eu_test}\n'
          f'a^(-1):'
          f' {rsa.ex_Eu(ex_eu_test[0], ex_eu_test[1])}')

    print('\n-Modular pow by Montgomery test-')
    mod_pow_test = (2, 3, 7)
    print(f'x, y, m: {mod_pow_test}\n'
          f'x^y mod m: {rsa.mod_pow(mod_pow_test[0], mod_pow_test[1], mod_pow_test[2])}')

    print('\n-PRIMES generating test-')
    len_bytes = 8
    print(f'l: {len_bytes}\n'
          f'PRIMES number: {rsa.gen_prime(len_bytes)}')

    print('\n-PRIMES checker test-')
    primes_number = 137
    not_primes_number = 138
    print(f'Fermat test for {primes_number}: {rsa.is_prime(primes_number, "F")}\n'
          f'Fermat test for {not_primes_number}: {rsa.is_prime(not_primes_number, "F")}\n'
          f'Rabin-Miller test for {primes_number}: {rsa.is_prime(primes_number, "RM")}\n'
          f'Rabin-Miller test for {not_primes_number}: {rsa.is_prime(not_primes_number, "RM")}\n'
          f'Solovay-Strassen test for {primes_number}: {rsa.is_prime(primes_number, "SS")}\n'
          f'Solovay-Strassen test for {not_primes_number}: {rsa.is_prime(not_primes_number, "SS")}\n')

    print('\n-Gen test-')
    len_bytes = 8
    n, e, d, p, q = rsa.gen(len_bytes)
    print(f'l: {len_bytes}\n'
          f'n: {n},\ne: {e},\nd: {d},\np: {p},\nq: {q}\n'
          f'Check if p and q are PRIMES: {rsa.is_prime(p), rsa.is_prime(q)}\n'
          f'n = p * q; due to test: {p} * {q} = {p * q} = n\n'
          f'Carmichael function: f_n = (p - 1) * (q - 1); '
          f'due to test: {p - 1} * {q - 1} = {(p - 1) * (q - 1)}\n'
          f'Greatest Common Divisor e: {e}'
          f' and {(p - 1) * (q - 1)} is {math.gcd(e, (p - 1) * (q - 1))}\n'
          f'e^(-1) mod (p - 1)(q - 1): '
          f'{rsa.ex_Eu(e, (p - 1) * (q - 1))} = d')

    print('\n-Encryption/Decryption test-')
    message = 'Ima o kaeru no wa tatakau kakugo da'
    unicode_message = [ord(letter) for letter in message]
    encr_result = [rsa.encr(elem, e, n) for elem in unicode_message]
    list_encr_result = [str(x) for x in encr_result]
    line_enc_result = ''.join(list_encr_result)
    decr_result = [rsa.decr(elem, d, p, q) for elem in encr_result]
    char_message = [chr(letter) for letter in decr_result]
    char_message_joined = ''.join(char_message)
    print(f'decrypted char message: {char_message_joined}')
    print(f'Message: {message}\n'
          f'n, e, d, p, q: higher\n'
          f'Encrypted message: {line_enc_result}\n'
          f'Decrypted message: {char_message_joined}')


if __name__ == '__main__':
    main()
