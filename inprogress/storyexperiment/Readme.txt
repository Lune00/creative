Dans Loup.cpp on teste une generation d'histoire a partir d'une timeline de successions d evenements et d etats. Il faut faire attention a ce que ca reste general et pas trop specialise. Acteur, etats(varibles d'etat), evenements.

Il faudra necessairement mettre au point un generateur de phrases procedurales qui sera appele par le constructeur d'histoire.
Ex: Pour dire que le loup n'avait pas mange depuis plusieurs jours :  <Pronom> <action> <circonstiel temps>, %etat. La fonction prend en argument la categorie de verbe (se nourrir), le pronom, le temps, et une variable d'etat/seuil. Si au dessus, rajouter une phrase.

Je sais pas c'est complique...


Il faut re ecrire datalist.cpp et la structure de donnees essayee y'a un an. C'est quand meme pas mal du tout. Ca offre une grande souplesse pour generer des phrases creatives. On a la une base de donnees chainee, ou un mot appel un autre etc de maniere parfaitement coherente puisque c'est nous qui ecrivons la chainepar des appels recursifs a l'aide des balises. GG d'avoir codé ca, je me souviens de rien!
