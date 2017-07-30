unset border
unset label
unset tic
unset grid
plot 'paths.txt' u 1:2:3:4 w vectors lw 2 lc rgb 'black', 'grid.txt' u 1:2 w p pt 7 ps 0.2 lc rgb 'blue', 'chemin.txt' u 1:2 w p lc rgb 'red' ps 2 pt 7
