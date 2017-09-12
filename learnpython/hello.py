#!/Users/paul/anaconda/bin/python

#Interactive plot avec Bokeh - interessant pour les maps et tester les algos !
from bokeh.plotting import figure 
from bokeh.io import output_notebook, show , export_png
from bokeh.models import Range1d
from numpy import cos, linspace, sinh

x=linspace(-6,6,100)
y=sinh(x)
y2=sinh(x/2)

p = figure(width=500, height=500)
p.circle(x, y, size=7, color="firebrick", alpha=0.5)
p.circle(x, y2, size=7, color="blue", alpha=0.5)
p.y_range = Range1d(-10,10)

export_png(p, filename="plot.png")
show(p)
