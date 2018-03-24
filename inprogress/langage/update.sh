#Recompile tout le projet
#Il faut faire un script qui recompile que ce qui a ete modifie a l'avenir pour gagner du temps

#clen lib
#rm lib/*.o

#Compile les sources:
echo "source"
cd src
#make clean
make

cd ../
cd exec
echo "app"
#make clean
make

cd ..

#Copie executable dans un dossier d'essai
mkdir -p test
cp exec/bibliotheque test/bibliotheque

#La librairie est pour l'instant dans son dossier propre
#Update library si mise a jour

echo "Compilation terminee."
