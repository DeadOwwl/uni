class polynomial_char_2:

    def __init__(self, coefficients: list):
        set_coefficients = set(coefficients)
        len_set = len(set_coefficients)
        if ('0' in set_coefficients and len_set == 1) or \
            ('1' in set_coefficients and len_set == 1) or \
            ('0' and '1' in set_coefficients and len_set == 2):
            self.degree = len(coefficients)
            self.coefficients = coefficients
        else:
            raise Exception('Polynomial representation should contains only "0" & "1".')


    def __add__(self, other):
        answer = []
        min_len = min(len(self.coefficients), len(other.coefficients))
        arg_max = self.coefficients if max(len(self.coefficients), len(other.coefficients))\
                                       == len(self.coefficients) else other.coefficients
        max_len = max(len(self.coefficients), len(other.coefficients))
        for i in range(min_len):
            answer.append(int(self.coefficients[i]) ^ int(other.coefficients[i]))
        for i in range(max_len - min_len):
            answer.append(arg_max[min_len + i])
        return str(answer)


    def __sub__(self, other):


    def __mul__(self, other):


    def __truediv__(self, other):


    def __pow__(self, other, modulo):


def row_counts(file):
    with open(file, 'r') as f:
        lines = f.readlines()
        num_lines = len([l for l in lines if l.strip(' \n') != ''])
    return num_lines


if __name__ == "__main__":
    polynom = open("polynom.txt", 'r').readline()
    num_rows = row_counts("input.txt")
    input_line = open("input.txt", 'r')
    answer = []
    for i in range(num_rows):
        string = input_line.readline()

        if '+' in string:
            operation_position = string.find('+', 0)
            answer.append(polynomial_char_2(string[0:operation_position]) +
                          polynomial_char_2(string[operation_position + 1 : len(string) - 1]))

        elif '*' in string:

        elif '/' in string:

        elif '^-1' in string:

        elif '^' in string:

