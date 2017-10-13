#usr/local/bin/bash

#Chemin relatif au script
R=250
rpath="$R/Analyse/gnuplot/"
#Template
gnu_unformated="plotsample_u.gnu"
#Formate (exectute)
gnu_formated="plotsample_f.gnu"
#Output png file
ofolder="gnuplotPNG_${R}"
mkdir -p "$ofolder"

for ((i=0;i<=20;i++))
do

  #Recupere les fichiers
  id=$(printf "%05d" "$i")
  file_wall="${rpath}wall${id}.txt"
  file_band="${rpath}bands${id}.txt"
  file_sample="${rpath}sample${id}.txt"

  #On formate le template gnuplot
  sed "s|^\<SAMPLE\>|sample=\"${filesample}\"|g" "$gnu_unformated" 
  sed -e "s|^\<SAMPLE\>|sample=\"$file_sample\"|g ; s|^\<WALLS\>|walls=\"$file_wall\"|g ; s|^\<BANDS\>|bands=\"$file_band\"|g" "$gnu_unformated" > "$gnu_formated"
  #Plot
  #Il faut export -f geps dans le terminal pour que ca marche (sol provisoire)
  geps "$gnu_formated"
  #eps file:
  rootname=$(echo $gnu_formated | cut -f 1 -d '.')
  #Nom final du fichier
  epsfile="$rootname.eps"
  pngfile="$rootname.png"
  #Conversion en png
  convert -density 200 "$epsfile" "$pngfile" 
  #Deplacement et renommer
  file_output="${ofolder}/${id}.png"
  mv "$pngfile" "$file_output"

done
