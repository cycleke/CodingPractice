# -*- coding: utf-8 -*-

from cyaron import *

MAXN = 10 ** 5
MAXQ = 10 ** 5

n = randint(4, MAXN)
tree = Graph.tree(n)
for edge in tree.iterate_edges():
    edge.weight = randint(1, 10 ** 9)
io = IO(file_prefix="a")
io.input_writeln(n)
io.input_writeln(tree)

q = randint(1, MAXQ)
io.input_writeln(q)
for i in range(q):
    op = randint(1, 2)
    if op == 1:
        io.input_writeln('C', randint(1, n - 1), randint(1, 10 ** 9))
    else:
        io.input_writeln('Q', randint(1, n))
