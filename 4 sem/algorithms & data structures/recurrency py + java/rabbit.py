# def rabbit_jumping(n, w):
#     if n == 0 or n == 1:
#         w.write('1')
#     elif n == 2:
#         w.write('2')
#     else:
#         first = 1
#         second = 2
#         third = 0
#         i = 2
#         while i != n:
#             third = (first + second) % 1000000007
#             first = second % 1000000007
#             second = third % 1000000007
#             i = i + 1
#         w.write(str(third))
#
#
# f = open('input.txt')
# m = int(f.readline())
# w = open('output.txt', 'w')
# rabbit_jumping(m, w)


if __name__ == '__main__':
    mod = 1000000007
    input_name = 'input.txt'
    output_name = 'output.txt'

    file = open(input_name)
    m = int(file.readline())
    w = open(output_name, 'w')

    if m == 0:
        w.write('1')
    elif m == 1:
        w.write('1')
    elif m == 2:
        w.write('2')
    else:
        first, second, third, step = 1, 2, 0, 2

        while step != m:
            third = (first + second) % mod
            first = second % mod
            second = third % mod
            step += 1
        w.write(str(third))
