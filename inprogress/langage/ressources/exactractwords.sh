#Extrait les mots qui commencent par aux et recupere leur phonetique
awk '$1~"aux"'  Lexique381.txt | cut -f1,2 > test.txt
