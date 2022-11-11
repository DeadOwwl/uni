import random
import math


def ex_Eu(a: int, b: int) -> int:
    """
    Extended Euclidean algorithm for reversal element a by modulus b.
    :param a: number for reversal;
    :param b: modulus;
    :return: reversal element a bu modulus b.
    """

    g, r0, r1 = 0, b, a
    x0, x1 = 1, 0
    y0, y1 = 0, 1
    while r1 != 0:
        g = r0 // r1
        r0, r1 = r1, r0 - g * r1
        x0, x1 = x1, x0 - g * x1
        y0, y1 = y1, y0 - g * y1
    if y0 < 0:
        y0 = (y0 + b) % b
    return y0


def mod_pow(x_mp: int, y_mp: int, modulus: int) -> int:
    """
    Modular exponential by Montgomery algorithm.
    :param x_mp: number to exponentiate;
    :param y_mp: degree of exponentiation;
    :param modulus: modulus by which exponentiation should be done;
    :return: result of Montgomery algorithm.
    """

    def convert_in(x_f, reducer_bits_f, mod):
        return (x_f << reducer_bits_f) % mod

    def convert_out(x_f, reciprocal_f, mod):
        return (x_f * reciprocal_f) % mod

    def multiply(x_f, y_f, mod, reducer_bits_f, mask_f, factor_f, ):
        product = x_f * y_f
        temp = ((product & mask_f) * factor_f) & mask_f
        reduced = (product + temp * mod) >> reducer_bits_f
        result = reduced if (reduced < mod) else (reduced - mod)
        return result

    reducer_bits = (modulus.bit_length() // 8 + 1) * 8
    reducer = 1 << reducer_bits
    mask = reducer - 1
    reciprocal = ex_Eu(reducer % modulus, modulus)
    factor = (reducer * reciprocal - 1) // modulus
    convertedone = reducer % modulus

    x_mp = convert_in(x_mp, reducer_bits, modulus)
    z = convertedone
    while y_mp != 0:
        if y_mp & 1 != 0:
            z = multiply(z, x_mp, modulus, reducer_bits, mask, factor)
        x_mp = multiply(x_mp, x_mp, modulus, reducer_bits, mask, factor)
        y_mp >>= 1

    return convert_out(z, reciprocal, modulus)


def gen_prime(n_low: int) -> int:
    """
    Generating PRIMES number verified by Rabin-Miller test.
    :param n_low: bits' number;
    :return: one of PRIMES number required bits' length.
    """

    def n_bit_random(n_random: int):
        return random.randrange(2 ** (n_random - 1) + 1, 2 ** n_random - 1)

    while True:
        pc: int = n_bit_random(n_low)

        if pc % 2 == 0 or pc % 3 == 0:
            continue
        if is_prime(pc):
            return pc


def is_prime(mrc: int, test: str = 'RM') -> bool:
    """
    Test for PRIMES number detecting. Standard usage is Rabin-Miller's test.
    :param mrc: number for testing;
    :param test: choosing a way for number testing, available:
        Fermat's test ('F'),
        Rabin-Miller's test ('RM'),
        Solovay-Strassen's test ('SS');
    :return: bool result of testing.
    """

    assert (test == 'F' or test == 'RM' or test == 'SS')

    if test == 'F':
        for _ in range(100):
            a_fermat = random.randint(1, mrc - 1)
            if math.gcd(a_fermat, mrc) != 1:
                return False
            if mod_pow(a_fermat, mrc - 1, mrc) != 1:
                return False
        return True

    elif test == 'RM':
        max_divisions_by_two = 0
        ec = mrc - 1
        while ec % 2 == 0:
            ec >>= 1
            max_divisions_by_two += 1
        assert (2 ** max_divisions_by_two * ec == mrc - 1)

        def trial_composite(round_tester_gen: int, ec_tc: int, mrc_tc: int, max_divisions_by_two_tc: int):
            if mod_pow(round_tester_gen, ec_tc, mrc_tc) == 1:
                return False
            for i_gen in range(max_divisions_by_two_tc):
                if mod_pow(round_tester_gen, 2 ** i_gen * ec_tc, mrc_tc) == mrc_tc - 1:
                    return False
            return True

        for _ in range(100):
            round_tester = random.randrange(2, mrc)
            if trial_composite(round_tester, ec, mrc, max_divisions_by_two):
                return False
        return True

    elif test == 'SS':

        def jacobi_symbol(a_js: int, b_js: int):
            r_js = 1
            if a_js < 0:
                a_js = -a_js
                if b_js % 4 == 3:
                    r_js = -r_js
            while True:
                t_js = 0
                while a_js % 2 == 0:
                    t_js += 1
                    a_js //= 2
                if t_js % 2 == 1:
                    if b_js % 8 == 3 or b_js % 8 == 5:
                        r_js = -r_js
                if a_js % 4 == b_js % 4 == 3:
                    r_js = -r_js
                a_js, b_js = b_js % a_js, a_js
                if a_js == 0:
                    return r_js

        for _ in range(100):
            a_ss = random.randint(1, mrc - 1)
            if math.gcd(a_ss, mrc) != 1:
                return False
            if mod_pow(a_ss, (mrc - 1) // 2, mrc) == jacobi_symbol(a_ss, mrc):
                return True
        return False


def gen(l: int) -> tuple[int, int, int, int, int]:
    """
    :param l: bits' number;
    :return: modulus n (public key), open exhibitor e, secret exhibitor d, PRIMES p & q
    """
    p, q = gen_prime(l), gen_prime(l)
    n = p * q
    # Carmichael function
    f_n = (p - 1) * (q - 1)
    if n % 8 == 0:
        f_n = int(0.5 * f_n)

    while True:
        e = random.randrange(3, f_n - 1, 2)
        if math.gcd(e, (p - 1) * (q - 1)) == 1:
            break

    d = ex_Eu(e, f_n)
    return n, e, d, p, q


def encr(text: int, e_encr: int, n_encr: int) -> int:
    """
    Encryption RSA method.
    :param text: message should be encrypted;
    :param e_encr: open exhibitor;
    :param n_encr: public key;
    :return: encrypted message.
    """
    return mod_pow(text, e_encr, n_encr)


def decr(text, d_decr, p_decr, q_decr):
    """

    :param text: message should be decrypted;
    :param d_decr: secret exhibitor;
    :param p_decr: PRIMES number p;
    :param q_decr: PRIMES number q;
    :return: decrypted message.
    """
    d_p = mod_pow(text % p_decr, d_decr % (p_decr - 1), p_decr)
    d_q = mod_pow(text % q_decr, d_decr % (q_decr - 1), q_decr)
    d_text = int((q_decr * d_p - p_decr * d_q) // (q_decr - p_decr))
    return d_text
