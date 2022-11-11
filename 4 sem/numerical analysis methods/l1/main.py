import numpy as np
import matplotlib.pyplot as plt
import math
import functools


a = -3
b = 0
h = 0.25
n = int((b - a) / h - 1)
fun = lambda x_for_fun: 2 ** (x_for_fun - 1)
x = [i for i in np.arange(a, b + h, h)]
y = [fun(i) for i in [i for i in np.arange(a, b + h, h)]]
interpolate_fun = lambda value:sum([y[j] * functools.reduce(lambda _x, _y: _x * _y, [(value - x[i]) / (x[j] - x[i]) if i != j else 1 for i in range(len(x))]) for j in range(len(x))])
norm1 = max([abs(fun(i) - interpolate_fun(i)) for i in np.arange(a, b, 0.001)])
norm2 = 1 / 4 * h ** (n + 1) * math.factorial(n)

sp = plt.subplot()
sp.plot(np.linspace(-4, 20, 100), np.vectorize(fun)(np.linspace(-4, 20, 100)), label="f(x)", color="blue")
sp.plot(np.linspace(-4, 20, 100), np.vectorize(interpolate_fun)(np.linspace(-4, 20, 100)), label="Ln(x)", color="purple")
sp.plot([i for i in np.arange(a, b + h, h)], np.vectorize(fun)([i for i in np.arange(a, b + h, h)]), 'go', label="Узлы сетки")
plt.title("f(x)=2^(x-1)\nПогрешность оценки: " + str(norm2) + "\nПогрешность на [-3,0]:" + str(norm1))
plt.grid()
sp.legend()
plt.show()
