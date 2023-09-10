import numpy as np


def path(n, mosquitoes):
    if n == 2:
        print(-1)
        return
    if n == 1:
        print(mosquitoes[0])
        print('1')
        return
    ways_m = np.zeros(n, dtype=np.int64)
    ways_m[0] = mosquitoes[0]
    ways_m[1] = -1
    ways_m[2] = ways_m[0] + mosquitoes[2]
    ways = np.zeros(n, dtype=np.int64)
    ways[0] = 1
    ways[1] = 2
    for i in range(3, n):
        if ways_m[i - 3] > ways_m[i - 2] + mosquitoes[i]:
            ways_m[i] = ways_m[i - 3]
            ways[i - 1] = i - 3
        else:
            ways_m[i] = ways_m[i - 2] + mosquitoes[i]
            ways[i - 1] = i
    print(ways_m[n - 1])
    for i in ways:
        print(i, end=' ')


n_condition = int(input())
mosquitoes_condition = [int(i) for i in input().split()]
path(n_condition, mosquitoes_condition)
# public class Main {
#     public static void main(String[] args) throws Exception {
#         Scanner sc = new Scanner(new File("input.txt"));
#         PrintWriter pr = new PrintWriter(new File("output.txt"));
#             int T = sc.nextInt();
#             int path;
#             int step;
#             int[] massive;
#             for (int i = 0; i < T; i++) {
#                 path = sc.nextInt();
#                 step = sc.nextInt();
#                 massive = new int[path];
#                 massive[0] = massive[1] = 1;
#                 for (int j = 2; j < path; j++) {
#                     massive[j] = massive[j - 1]*2;
#                     if (j - step - 1 >= 0) {
#                         massive[j] = massive[j] - massive[j - step - 1];
#                     }
#                 }
#                 pr.print(massive[path - 1]);
#                 pr.println();
#             }
#             pr.close();
#         }
#     }

#_______________________________________
#