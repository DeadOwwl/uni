def palindrome(string):
    palindrome_length = 0
    the_palindrome = ""
    string_length = len(string)
    if string_length == 1:
        palindrome_length = 1
        the_palindrome = string
    elif string_length == 2:
        if string[0] == string[1]:
            palindrome_length = 2
            the_palindrome = string
        else:
            palindrome_length = 1
            the_palindrome = string[0]
    else:
        reversed_string = string[::-1]
        substring_length_matrix = [[0 for i in range(string_length + 1)] for j in range(string_length + 1)]
        for i in range(1, string_length + 1):
            for j in range(1, string_length + 1):
                if string[i - 1] == reversed_string[j - 1]:
                    substring_length_matrix[i][j] = substring_length_matrix[i - 1][j - 1] + 1
                else:
                    substring_length_matrix[i][j] = max(substring_length_matrix[i - 1][j], substring_length_matrix[i][j - 1])
        palindrome_length = substring_length_matrix[string_length][string_length]

        i = string_length
        j = string_length
        while substring_length_matrix[i][j] > 0:
            while substring_length_matrix[i][j] == substring_length_matrix[i][j - 1]:
                j -= 1
            if string[i - 1] == reversed_string[j - 1]:
                the_palindrome = ''.join((the_palindrome, string[i - 1]))
                j -= 1
            i -= 1
    return palindrome_length, the_palindrome


answer_length, answer_palindrome = palindrome(open('input.txt').readline().strip())
w = open('output.txt', 'w')
if answer_length != 0:
    w.write(str(answer_length) + '\n' + answer_palindrome)
else:
    w.write(str(answer_length))
