#!/Users/paul/anaconda/bin/python

from numpy import random

from lightning import Lightning
lgn = Lightning(local=True)

lgn = Lightning(ipython=True, local=True)
series = random.randn(5, 50)
lgn.line(series)
