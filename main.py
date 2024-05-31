from HelloModule import Hello

h = Hello()
print(h.getValue())
h.addOne()
print(h.getValue())
h.setValue(42)
print(h.getValue())

